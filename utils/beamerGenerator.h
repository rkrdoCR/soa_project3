#ifndef BEAMER_GENERATOR_H
#define BEAMER_GENERATOR_H

#include <gtk/gtk.h>
#include "../algorithms/algorithms.h"
#include "../beamer/beamerBuilder.h"

void generateBeamer(simulation_settings *formSettings);
void generateBeamerDoc(algo_results *ar, int tasks_count, int lcm);
int computeLCM(int *periods, int len);

#endif