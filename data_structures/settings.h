#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdlib.h>

typedef struct 
{
    int executionTimes[6];
    int periods[6];
    //algorithms
    int rm;
    int edf;
    int llf;
    // checkboxes 
    int combineAll;

}simulation_settings;

#endif