#ifndef RATE_MONOTONIC_H
#define RATE_MONOTONIC_H

#include <math.h>

#include "data_structures/settings.h"
#include "data_structures/algo_results.h"
#include "data_structures/priority_queue.h"
#include "data_structures/task.h"

algo_results runRM(int *c, int *p, int count, int lcm);

#endif