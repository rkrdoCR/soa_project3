#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdlib.h>

struct settings
{
    int executionTime[6];
    int period[6];
    //algorithms
    int rm;
    int edf;
    int llf;
    // checkboxes 
    int schedulable;
    int combineAll;

};

typedef struct settings settings;

settings* fillSettings(int schedulable,int combineAll,int rm, int edf, int llf);

#endif