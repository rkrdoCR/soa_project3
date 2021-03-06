#include <gtk/gtk.h>
#include "beamerGenerator.h"

void generateBeamer(simulation_settings *formSettings)
{
    int *p = malloc(sizeof(int) * 6);
    int *c = malloc(sizeof(int) * 6);

    //get the "n" valid periods (the ones != null)
    int i, j = 0;
    for (i = 0; i < 6; i++)
    {
        if (formSettings->periods[i] > 0)
        {
            p[j] = formSettings->periods[i];
            j++;
        }
    }

    //get the "n" valid exec times (the ones != null)
    i, j = 0;
    for (i = 0; i < 6; i++)
    {
        if (formSettings->executionTimes[i] > 0)
        {
            c[j] = formSettings->executionTimes[i];
            j++;
        }
    }

    //compute least common multiple
    int lcm = computeLCM(p, j);

    //allocate array for storing the results of the simulations
    algo_results algoResults[3];

    //rate monotonic selected
    if (formSettings->rm == 1)
    {
        algoResults[0] = runRM(c, p, j, lcm);
    }

    //earliest deadline first selected
    if (formSettings->edf == 1)
    {
        algoResults[1] = runEDF(c, p, j, lcm);
    }

    //least laxity first selected
    if (formSettings->llf == 1)
    {
        algoResults[2] = runLLF(c, p, j, lcm);
    }

    free(c);
    free(p);

    createBeamer(algoResults,j,lcm, formSettings->combineAll);
    //generateBeamerDoc(algoResults, j, lcm);
    
}

void generateBeamerDoc(algo_results *ar, int tasks_count, int lcm)
{
    g_print("Tasks info \n");

    int a;
    for(a = 0; a < tasks_count; a++)
    {
        g_print("%d    %d\n", ar->tasks_set[a].execTime, ar->tasks_set[a].period);
    }

    g_print("\nTasks set simulation \n\n");

    int i, j, k;
    for (k = 0; k < 3; k++)
    {
        if (ar[k].selected == 1)
        {
            g_print("Schedulability Test Results: u = %f --- U = %f\n\n", ar[k].u, ar[k].U);
            for (i = 0; i < tasks_count; i++)
            {
                for (j = 0; j < lcm; j++)
                {
                    g_print(" %d |", ar[k].matrix[i][j]);
                }
                g_print("\n");
            }
            
            free(ar[k].matrix);
        }
    }
}

//code taken from:
int computeLCM(int *p, int len)
{
    int periods[len];
    int i;
    for (i = 0; i < len; i++)
    {
        periods[i] = p[i];
    }

    long lcm = 1;
    int divisor = 2;
    while (1)
    {
        int cnt = 0;
        int divisible = 0;
        for (int i = 0; i < len; i++)
        {
            /**
             * lcm (n1,n2,... 0)=0.For negative number we convert into
             * positive and calculate lcm.
             */
            if (periods[i] == 0)
            {
                return 0;
            }
            else if (periods[i] < 0)
            {
                periods[i] = periods[i] * (-1);
            }
            if (periods[i] == 1)
            {
                cnt++;
            }
            /**
             * divide numbers by devisor if complete division i.e. without
             * remainder then replace number with quotient; used for find
             * next factor
             */
            if (periods[i] % divisor == 0)
            {
                divisible = 1;
                periods[i] = periods[i] / divisor;
            }
        }
        /**
         * If divisor able to completely divide any number from array
         * multiply with lcm and store into lcm and continue to same divisor
         * for next factor finding. else increment divisor
         */
        if (divisible)
        {
            lcm = lcm * divisor;
        }
        else
        {
            divisor++;
        }
        /**
         * Check if all numbers is 1 indicate we found all factors and
         * terminate while loop.
         */
        if (cnt == len)
        {
            return lcm;
        }
    }
}