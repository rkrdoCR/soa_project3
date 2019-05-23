#include "algorithms.h"

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
    if (computeUtilization(tasks_set, j) <= 1)
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

    return results;
}

void simulateLLF(task *tasks, int count, int lcm, algo_results *results)
{
}