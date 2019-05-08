#include "rate_monotonic.h"

double computeUtilization(task *tasks, int count);
double computeUpperBound(int count);
void simulateRM(task *tasks, int count, int lcm, algo_results* results);

algo_results runRM(int *c, int *p, int count, int lcm)
{
    task *tasks_set = malloc(sizeof(task)*count);
    algo_results results;

    int i, j = 0;
    for (i = 0; i < count; i++)
    {
        tasks_set[i].execTime = c[i];
        tasks_set[i].period = p[i];
        j++;
    }

    //compute utilization (u)
    double u = computeUtilization(tasks_set, j); 

    //compute upper bound (U)
    double U = computeUpperBound(j);

    //check schedulability
    if (u <= U)
    {
        results.schedulable = 1;
    }
    else
    {
        results.schedulable = 0;
    }

    //run simulation
    simulateRM(tasks_set, j, lcm, &results);    

    return results;
}

double computeUtilization(task *tasks, int count)
{
    double result;

    int i;
    for (i = 0; i < count; i++)
    {
        result += (double)tasks[i].execTime/(double)tasks[i].period;
    }

    return result;
}

double computeUpperBound(int count)
{
    double n = (double)count;
    return n*((pow(2.0,1/n))-1);;
}

void simulateRM(task *tasks, int count, int lcm, algo_results* results)
{
    int resultMatrix[count][lcm];

    //add tasks to priority queue
    Node *p_queue = newNode(tasks[0], tasks[0].period);

    int i;
    for (i = 1; i < count; i++)
    {
        push(&p_queue, tasks[i], tasks[i].period);
    }    
    
    

}