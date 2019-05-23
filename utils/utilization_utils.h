#ifndef UTILIZATION_UTILS_H
#define UTILIZATION_UTILS_H

#include <math.h>

#include "../data_structures/task.h"

double computeUtilization(task *tasks, int count);
double computeUpperBound(int count);

#endif