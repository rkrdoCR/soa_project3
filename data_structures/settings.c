#include "settings.h"

settings* fillSettings(int combineAll, int rm, int edf, int llf){

    settings* formSettings = malloc(sizeof(settings));
    
    formSettings->combineAll = combineAll;
    formSettings->rm = rm;
    formSettings->edf = edf;
    formSettings->llf = llf;

    return formSettings;
}