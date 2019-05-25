#ifndef ALGO_RESULTS_H
#define ALGO_RESULTS_H

#include "task.h"

typedef struct 
{
    int schedulable;
    int **matrix;
    int selected;
    double u;
    double U;
    task *tasks_set;
} algo_results;


#endif