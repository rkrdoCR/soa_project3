//This is a test to ijnvoke several of the functions that are necessary to create beamer
#include "beamerBuilder.h"


int main (){
    algo_results ar;

    int a[8] = {  
        0, 1, 2, 3, 0, 1, 2, 3   /*  initializers for row indexed by 0 */
    };

    int b[8] = {  
        0, 1, 2, 3, 0, 1, 2, 3   /*  initializers for row indexed by 0 */
    };

    int c[8] = {  
        0, 1, 2, 3, 0, 1, 2, 3   /*  initializers for row indexed by 0 */ 
    };

    int **m[3]={&a,&b,&c};

    ar.selected=1;
    ar.matrix=m;
    ar.schedulable=1;

    printf("Scheduling simulator: Reading template \n");
    createTabular(&ar, 3, 8);

    //copyTemplateToTemp();
    copyTemplateToTempBash();

    readTemplate();

    compileBeamer();

    

}