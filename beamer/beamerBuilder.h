#ifndef BEAMER_BUILDER_H
#define BEAMER_BUILDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int copyTemplateToTempBash();
int copyTemplateToTemp();
int readTemplate();
void createBeamer(int number);
void compileBeamer();


#endif