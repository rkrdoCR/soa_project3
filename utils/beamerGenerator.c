#include "beamerGenerator.h"
#include "gtk/gtk.h"

void generateBeamer(simulation_settings *formSettings)
{
    int *p = malloc(sizeof(int)*6);
    int *c = malloc(sizeof(int)*6);

    int i, j = 0;
    for (i = 0; i < 6; i++)
    {
        if(formSettings->periods[i] > 0)
        {
            p[j] = formSettings->periods[i];
            j++;
        }
    }

    i, j = 0;
    for (i = 0; i < 6; i++)
    {
        if(formSettings->executionTimes[i] > 0)
        {
            c[j] = formSettings->executionTimes[i];
            j++;
        }
    } 

    int lcm = computeLCM(p, j);

    algo_results algoResults[3];

    if (formSettings->rm)
    {
        algoResults[0] = runRM(c, p, j, lcm);
    }

    if (formSettings->edf)
    {
        //algoResults[1] = runEDF();
    }

    if (formSettings->llf)
    {
        //algoResults[2] = runLLF();
    }

    free(c);
    free(p);
    //free(formSettings);

    generateBeamerDoc(algoResults, j, lcm);
}

void generateBeamerDoc(algo_results *ar, int tasks_count, int lcm)
{
    int i, k;
    for(i = 0; i < tasks_count; i++)
    {
        for(k = 0; k < lcm; k++)
        {
            g_print(" %d |", ar[0].matrix[i][k]);
        }
        g_print("\n");
    }

    // int c;
    // for (c = 0; c < ta)
    free(ar[0].matrix);
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