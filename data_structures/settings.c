#include "settings.h"

settings* fillSettings(int schedulable,int combineAll,int rm, int edf, int llf){
    printf("Started filling");
    settings* formSettings = malloc(sizeof(settings));
    formSettings->schedulable = schedulable;
    formSettings->combineAll = combineAll;
    formSettings->rm = rm;
    formSettings->edf = edf;
    formSettings->llf = llf;

    return formSettings;
}