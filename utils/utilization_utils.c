#include "utilization_utils.h"

double computeUtilization(task *tasks, int count)
{
    double result = 0;

    int i;
    for (i = 0; i < count; i++)
    {
        result += (double)tasks[i].execTime / (double)tasks[i].period;
    }

    return result;
}

double computeUpperBound(int count)
{
    double n = (double)count;
    return n * ((pow(2.0, 1 / n)) - 1);
}