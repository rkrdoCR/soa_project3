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
void createBeamer(algo_results *ar, int tasks_count, int lcm);
void compileBeamer();
void createTabular(algo_results *ar, int tasks_count, int lcm, char *tabular_name);
void flushTempFiles();
void StringDecoder(char *input, char *output);
void addKeyToDecoder(char *key, char *value);
void flushDecoder();

#endif