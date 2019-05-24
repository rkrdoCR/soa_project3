#ifndef BEAMER_BUILDER_H
#define BEAMER_BUILDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../data_structures/algo_results.h"

int copyTemplateToTempBash();
int copyTemplateToTemp();
int readTemplate();
void createBeamer(int number);
void compileBeamer();
void createTabular(algo_results *ar, int tasks_count, int lcm);


#endif