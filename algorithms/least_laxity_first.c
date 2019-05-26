#include "algorithms.h"
#include <stdio.h>

#define MASK_BIT(x, bit) ((x) & (0x1) << (bit))
#define SET_BIT(x, bit) ((x) |= ((0x1) << (bit)))

typedef struct
{
    unsigned int WCET;
    unsigned int period;
    int deadline;
} task_t;
int time_error = 0;

algo_results runLLF(int *c, int *p, int count, int lcm)
{
    task *tasks_set = malloc(sizeof(task) * count);
    algo_results results;

    //build task set
    int i, j = 0;
    for (i = 0; i < count; i++)
    {
        tasks_set[i].execTime = c[i];
        tasks_set[i].period = p[i];
        j++;
    }

    //compute utilization (u)
    double u = computeUtilization(tasks_set, j);

    //check schedulability and store it to results
    if (u <= 1)
    {
        results.schedulable = 1;
    }
    else
    {
        results.schedulable = 0;
    }

    //run simulation
    simulateLLF(tasks_set, j, lcm, &results);

    free(tasks_set);
    results.selected = 1;

    //error en tiempo de ejecucion
    if (time_error > 0)
    {
        results.schedulable = 0;
    }
    return results;
}

//---------------------------

//Randall
void init_task(task_t *t, unsigned int WCET, unsigned int period, int deadline)
{
    t->WCET = WCET;
    t->period = period;
    t->deadline = deadline;
}

void init_tasks(task_t t[], unsigned int WCET[], unsigned int period[], int deadline[], unsigned int numTasks)
{
    unsigned int i;
    for (i = 0; i < numTasks; i++)
    {
        init_task(&(t[i]), WCET[i], period[i], deadline[i]);
    }
}

void copy_tasks(task_t tasks_to_be_copied[], task_t place_to_copy[], unsigned int numTasks)
{
    unsigned int i;
    for (i = 0; i < numTasks; i++)
    {
        place_to_copy[i].WCET = tasks_to_be_copied[i].WCET;
        place_to_copy[i].period = tasks_to_be_copied[i].period;
        place_to_copy[i].deadline = tasks_to_be_copied[i].deadline;
    }
}

void print_task(task_t t)
{
    printf("exe time: %u period: %u deadline: %u \n", t.WCET, t.period, t.deadline);
}

void print_tasks(task_t t[], unsigned int numTasks)
{
    unsigned int i;
    for (i = 0; i < numTasks; ++i)
    {
        printf("task %u: ", i);
        print_task(t[i]);
    }
}

float utilization(task_t t[], unsigned int numTasks)
{
    float util = 0;

    unsigned int i;
    for (i = 0; i < numTasks; i++)
    {
        util += t[i].WCET / t[i].period;
    }

    return util;
}

typedef unsigned int (*sched_algo_t)(task_t[], unsigned int);

unsigned int llf(task_t t[], unsigned int numTasks)
{
    unsigned int least_index = 0;
    int least_laxity = 0xffff; // max int
    int current_laxity;
    unsigned int i;
    for (i = 0; i < numTasks; i++)
    {
        if (t[i].WCET > 0)
        {
            current_laxity = t[i].deadline - t[i].WCET;
        }

        if (current_laxity < least_laxity)
        {
            least_index = i;
            least_laxity = current_laxity;
        }
    }
    return least_index;
}

void sim_schedule(task_t t[], unsigned int numTasks, unsigned int schedule[], unsigned int schedule_length, sched_algo_t algo)
{
    numTasks++; //add 1 for idle
    task_t placeholder_task[numTasks];
    copy_tasks(t, placeholder_task, numTasks - 1);

    //idle
    init_task(&(placeholder_task[numTasks - 1]), 99, 9999, 9999);

    //index of current task
    unsigned int current_task;
    unsigned int i;
    for (i = 0; i < schedule_length; i++)
    {

        schedule[i] = 0;

        //determine current task
        current_task = algo(placeholder_task, numTasks);
        // printf("-->> i %d, y current_task %d  numTasks %d\n", i, current_task, numTasks);

        //"run" current task for 1 timestep
        placeholder_task[current_task].WCET -= 1;

        //decrement all time
        unsigned int j;
        for (j = 0; j < numTasks; j++)
        {

            placeholder_task[j].period -= 1;
            placeholder_task[j].deadline -= 1;

            //check for missed deadlines
            if (placeholder_task[j].deadline <= 0)
            {
                if (placeholder_task[j].WCET > 0)
                {
                    SET_BIT(schedule[i], j + 16); //***need a define for 16**

                    if (time_error == 0 && placeholder_task[j].WCET > 0)
                    {
                        time_error = i;
                    }
                    else
                    {
                        //printf("error no bandera i %d, y tengo %d  %d\n", i, placeholder_task[j].WCET);
                    }
                }
            }

            //reset tasks
            if (placeholder_task[j].period <= 0)
            {
                placeholder_task[j].WCET = t[j].WCET;
                placeholder_task[j].period = t[j].period;
                placeholder_task[j].deadline = t[j].deadline;
            }
        }
        SET_BIT(schedule[i], current_task);
    }
}

void print_schedule(unsigned int schedule[], unsigned int length)
{
    unsigned int i;
    unsigned int count;
    for (i = 0; i < length; ++i)
    {
        count = 0;
        while (MASK_BIT(schedule[i], count) == 0)
        {
            count++;
        }
        printf("%u ", (count + 1));
    }
    printf("\n");
}

//-----------------------------

void simulateLLF(task *task_raw, int count, int lcm, algo_results *results)
{

    unsigned int WCET[count];
    unsigned int deadline[count];
    int period[count];
    ;

    //build task set
    int i = 0;
    for (i = 0; i < count; i++)
    {
        WCET[i] = task_raw[i].execTime;
        deadline[i] = task_raw[i].period;
        period[i] = task_raw[i].period;
    }

    int exec_time = 0;
    for (int i = 0; i < count; i++)
    {
        exec_time += period[i];
    }

#define EXE_LEN ((exec_time - 1))
#define NUM_TASKS (count)

    //allocate matrix
    results->matrix = (int **)malloc(count * sizeof(int *));
    int a;
    for (a = 0; a < count; a++)
    {
        //allocate rows (arrays) in matrix (2d array)
        results->matrix[a] = (int *)malloc(lcm * sizeof(int *));
    }

    //prebuild matrix
    for (int i = 0; i < count; i++)
    {

        for (int j = 0; j < lcm; j++)
        {
            results->matrix[i][j] = 0;
        }
    }

    task_t tasks[count];
    init_tasks(tasks, WCET, deadline, period, count);

    //print_tasks(tasks, count);
    printf("\n Least Laxity First \n");

    unsigned int schedule[lcm];
    sim_schedule(tasks, count, schedule, lcm, llf);

    int i_matrix;
    int count_tasks;

    for (i_matrix = 0; i_matrix < lcm; ++i_matrix)
    {
        count_tasks = 0;
        while (MASK_BIT(schedule[i_matrix], count_tasks) == 0)
        {
            count_tasks++;
        }

        if (count_tasks < count)
        {
            if (time_error > 0 && time_error == i_matrix)
            {
                results->matrix[count_tasks][i_matrix] = 13;
            }
            else
            {
                results->matrix[count_tasks][i_matrix] = (count_tasks + 1);
            }
        }
        else
        { //descanso cpu
            for (int m = 0; m < count; ++m)
            {
                results->matrix[m][i_matrix] = 7;
            }
        }
    }
    check_cpu_unused_fix(count, lcm, results);
    //print_schedule(schedule, lcm);
    //--------------------------------------------
}

void check_cpu_unused_fix(int count, int lcm, algo_results *results)
{

    int cpu_check = 0;
    int i = 0;
    for (int m = 0; m < lcm; ++m)
    {
        cpu_check = 0;

        for (i = 0; i < count; ++i)
        {
            cpu_check += results->matrix[i][m];
        }
        if (cpu_check == 0)
        {
            for (int j = 0; j < count; ++j)
            {
                results->matrix[j][m] = 7;
            }
        }
    }
    print_matrix_o(count, lcm, results);
}

void print_matrix_o(int count, int lcm, algo_results *results)
{

    for (int i = 0; i < count; ++i)
    {
        printf("\n");
        for (int m = 0; m < lcm; ++m)
        {
            printf("| %d", results->matrix[i][m]);
        }
    }
    printf("\n");
}