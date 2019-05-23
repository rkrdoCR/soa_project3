#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../data_structures/settings.h"
#include "../data_structures/algo_results.h"
#include "../data_structures/priority_queue.h"
#include "../data_structures/task.h"
#include "../data_structures/deadline.h"
#include "../utils/utilization_utils.h"

int getDeadlinesPresentInColumn(int col, deadline *deadlines, int dcount);
deadline *getDeadlines(int k, deadline *deadlines, int dcount);
int computeDealinesCount(task *tasks, int lcm, int count);

void simulateRM(task *tasks, int count, int lcm, algo_results *results);
algo_results runRM(int *c, int *p, int count, int lcm);

algo_results runEDF(int *c, int *p, int count, int lcm);
void simulateEDF(task *tasks, int count, int lcm, algo_results *results);

algo_results runLLF(int *c, int *p, int count, int lcm);
void simulateLLF(task *tasks, int count, int lcm, algo_results *results);

#endif