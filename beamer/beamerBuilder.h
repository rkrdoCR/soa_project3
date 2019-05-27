#ifndef BEAMER_BUILDER_H
#define BEAMER_BUILDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../data_structures/algo_results.h"

//int copyTemplateToTempBash();
int copyTemplateToTempBash(char *file_to_copy);
int copyTemplateToTemp();
int readTemplate();
void createBeamer(algo_results *ar, int tasks_count, int lcm, int combine_all);
void compileBeamer();
void createTabular(algo_results *ar, int tasks_count, int lcm, char *tabular_name);
void createTabularCA(algo_results *ar0, algo_results *ar1, algo_results *ar2, int tasks_count, int lcm, char *tabular_name);
void flushTempFiles();
void StringDecoder(char *input, char *output);
void addKeyToDecoder(char *key, char *value);
void flushDecoder();
void createTestResults();
void createTaskSet(algo_results *ar, int tasks_count);

#endif