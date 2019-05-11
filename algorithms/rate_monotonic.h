#ifndef RATE_MONOTONIC_H
#define RATE_MONOTONIC_H

#include <math.h>

#include "../data_structures/settings.h"
#include "../data_structures/algo_results.h"
#include "../data_structures/priority_queue.h"
#include "../data_structures/task.h"
#include "../data_structures/deadline.h"

double computeUtilization(task *tasks, int count);
double computeUpperBound(int count);
int getDeadlinesPresentInColumn(int col, deadline *deadlines, int dcount);
deadline *getDeadlines(int k, deadline *deadlines, int dcount);
int computeDealinesCount(task *tasks, int lcm, int count);

void simulateRM(task *tasks, int count, int lcm, algo_results *results);

algo_results runRM(int *c, int *p, int count, int lcm);

#endif