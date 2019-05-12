//This is a test to ijnvoke several of the functions that are necessary to create beamer
#include "beamerBuilder.h"


int main (){
    printf("Scheduling simulator: Reading template \n");

    //copyTemplateToTemp();
    copyTemplateToTempBash();

    readTemplate();

    compileBeamer();

}