#include "algorithms.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int period_LCM;

float f;

int WCET[6];
int deadlines[6];
int period[6];

/* int WCET[3] = {1,2,6}; // execution times
    int deadlines[3] = {5,8,19}; // deadliness
    int period[3] = {5,8,19}; // periods (equal to deadliness)*/

algo_results runEDF(int *c, int *p, int count, int lcm)
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
    results.u = u;
    results.U = MAX_U_EDF;

    //check schedulability and store it to results
    if (u <= MAX_U_EDF)
    {
        results.schedulable = 1;
    }
    else
    {
        results.schedulable = 0;
    }

    //run simulation
    simulateEDF(tasks_set, j, lcm, &results);

    free(tasks_set);
    results.selected = 1; 
    return results;
}

//--------------------------------------
void get_period_LCM(int no_of_tasks) // computes LCM of periods
{
    int lcm[no_of_tasks];
    for (int i = 0; i < no_of_tasks; i++)
    {
        lcm[i] = period[i]; // initialize lcm array
    }
    int h = 0;
    int lowest_value;
    int lowest_value_index;
    while (h == 0)
    {
        h = 1;
        lowest_value = lcm[0];
        lowest_value_index = 0;
        for (int i = 0; i < no_of_tasks; i++)
        {
            if (lowest_value != lcm[i])
            {
                h = 0;
                if (lowest_value > lcm[i]) // if current global LCM greater than LCM of task
                {
                    lowest_value = lcm[i];
                    lowest_value_index = i; // update task index whose period was used
                }
            }
        }
        if (h == 0) // LCM changed; update it
        {
            lcm[lowest_value_index] = lowest_value + period[lowest_value_index];
        }
    }
    period_LCM = 760; //lcm[0];
                      // printf("\nSchedulability will be evaluated over the LCM of periods which is %d\n", period_LCM);
}

float schedulability(int no_of_tasks)
{
    float utilization = 0;
    float x, y;
    printf("The CPU utilization is: ");
    for (int i = 0; i < no_of_tasks; i++) // compute utilization as sum of individual task utilizations (Ci/Ti)
    {
        x = WCET[i];
        y = period[i];
        utilization = utilization + x / y;
        printf("(%d/%d) ", WCET[i], period[i]);
        if (i == no_of_tasks - 1)
            break;
        else
            printf("+ ");
    }
    printf(" = %f", utilization);
    return utilization;
}

void schedule(int no_of_tasks, algo_results *results, int EXE_LEN, int lcm)
{ // computes EDF schedule
    int earliest_deadlines;
    int earliest_deadlines_index;
    period_LCM = lcm;
    int edf_schedule[period_LCM];
    int cycles_left[no_of_tasks];
    int next_deadlines[no_of_tasks];
    int cycles_completed[no_of_tasks];
    printf("\n");
    for (int i = 0; i < no_of_tasks; i++)
    {
        next_deadlines[i] = deadlines[i]; // next deadlines of task
        cycles_left[i] = WCET[i];         // time steps remaining for task execution
        cycles_completed[i] = 0;          // time steps completed
    }
    for (int i = 0; i < period_LCM; i++)
    // for (int i = 0; i < EXE_LEN; i++)
    {
        //printf("(%d,%d) : ", i, i + 1); // print current time slot
        earliest_deadlines = period_LCM;
        earliest_deadlines_index = -1;
        for (int j = 0; j < no_of_tasks; j++) // check all tasks
        {
            if (cycles_left[j] > 0) // if task has not executed completely
            {
                if (earliest_deadlines > next_deadlines[j]) // if earliest deadlines beyond current task deadlines
                {
                    earliest_deadlines = next_deadlines[j]; // schedule current task
                    earliest_deadlines_index = j;
                }
            }
        }
        //  printf("     [Task executed = %d]\n",earliest_deadlines_index); // current task assigned to time slot
        //printf("     [Task executed = %d]\n", (earliest_deadlines_index + 1)); // current task assigned to time slot
        if (earliest_deadlines_index >= 0)
        {
            results->matrix[earliest_deadlines_index][i] = (earliest_deadlines_index + 1);
        }
        /* else {
            printf("     [Task executed = %d]\n",earliest_deadlines_index); // current task assigned to time slot
        }*/

        cycles_left[earliest_deadlines_index]--; // decrement task's execution cycles left

        for (int j = 0; j < no_of_tasks; j++)
        {
            if (cycles_completed[j] == (period[j] - 1)) // if task is approaching period
            {
                next_deadlines[j] = deadlines[j]; // set deadlines for it
                cycles_left[j] = WCET[j];         // load cycles left for execution with WCET
                cycles_completed[j] = 0;          // reset cycles completed
            }
            else
            {
                if (next_deadlines[j] > 0) // if time remaining until next deadlines
                {
                    next_deadlines[j]--; // decrement it by one time slot
                }
                else
                {
                    if (cycles_left[j] > 0) // if deadlines arrived && non-zero cycles left to be executed
                    {
                        printf("\n the process %d cannot be completed to capacity", j); // cannot complete task
                    }
                }
                cycles_completed[j]++; // increment cycles completed
            }
        }
    }
}

///---------------------------------

void simulateEDF(task *task_raw, int count, int lcm, algo_results *results)
{
    printf("\n Earliest Deadline First");
#define no_of_tasks (count)

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

    for (int i = 0; i < count; i++)
    {
        WCET[i] = task_raw[i].execTime;
        deadlines[i] = task_raw[i].period;
        period[i] = task_raw[i].period;
    }

    printf("Task parameters:\n"); // print task parameters
    printf("Task_i | Ci, Di, Ti\n");
    printf("-------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("Task_%d | %d,  %d,  %d\n", i, WCET[i], deadlines[i], period[i]);
    }

    int exec_time = 0;
    for (int i = 0; i < count; i++)
    {
        exec_time += period[i];
    }

#define EXE_LEN ((exec_time - 1))

    //----------

    get_period_LCM(count);
    printf("\nSchedulability Test:\n"); // commence schedulability test
    f = schedulability(count);

    if (f <= MAX_U_EDF)
    {
        printf("\nThe system is schedulable because the CPU utilization %f <= 1", f);
         results->schedulable = 1;
        // printf("\n\nEDF Schedule\n");
        // printf("\nTime slice      Task executed\n");
        schedule((count + 1), results, exec_time, lcm);
    }
    else
    {
        printf("\nThe system is not schedulable because the CPU utilization %f > 1\n", f);
        results->schedulable = 0;
        schedule((count + 1), results, exec_time, lcm);
    }
    return 0;
}