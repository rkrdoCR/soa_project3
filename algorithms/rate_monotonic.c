#include "rate_monotonic.h"
#include <stdio.h>

double computeUtilization(task *tasks, int count);
double computeUpperBound(int count);
int getDeadlinesPresentInColumn(int col, deadline *deadlines, int dcount);
deadline *getDeadlines(int k, deadline *deadlines, int dcount);
int computeDealinesCount(task *tasks, int lcm, int count);

void simulateRM(task *tasks, int count, int lcm, algo_results *results);

algo_results runRM(int *c, int *p, int count, int lcm)
{
    task *tasks_set = malloc(sizeof(task) * count);
    algo_results results;

    int i, j = 0;
    for (i = 0; i < count; i++)
    {
        tasks_set[i].execTime = c[i];
        tasks_set[i].period = p[i];
        j++;
    }

    //compute utilization (u)
    double u = computeUtilization(tasks_set, j);

    //compute upper bound (U)
    double U = computeUpperBound(j);

    //check schedulability
    if (u <= U)
    {
        results.schedulable = 1;
    }
    else
    {
        results.schedulable = 0;
    }

    //run simulation
    simulateRM(tasks_set, j, lcm, &results);

    return results;
}

double computeUtilization(task *tasks, int count)
{
    double result;

    int i;
    for (i = 0; i < count; i++)
    {
        result += (double)tasks[i].execTime / (double)tasks[i].period;
    }

    return result;
}

double computeUpperBound(int count)
{
    double n = (double)count;
    return n * ((pow(2.0, 1 / n)) - 1);
}

int computeDealinesCount(task *tasks, int lcm, int count)
{
    int total_d = 0;

    int i;
    for (i = 0; i < count; i++)
    {
        total_d += (lcm / tasks[i].period) - 1;
    }

    return total_d;
}

int getDeadlinesPresentInColumn(int col, deadline *deadlines, int dcount)
{
    int i, j = 0;
    for (i = 0; i < dcount; i++)
    {
        if (deadlines[i].column == col)
        {
            j++;
        }
    }
    return j;
}

deadline *getDeadlines(int col, deadline *deadlines, int dcount)
{
    int j = getDeadlinesPresentInColumn(col, deadlines, dcount);

    deadline *r = malloc(sizeof(deadline) * j);
    if (j > 0)
    {
        int i, k = 0;
        for (i = 0; i < dcount; i++)
        {
            if (deadlines[i].column == col)
            {
                r[k] = deadlines[i];
                k++;
            }
        }
        return r;
    }
    return NULL;
}

void simulateRM(task *tasks, int count, int lcm, algo_results *results)
{
    int c = 1, task_row = 0, column = 0;
    task t;

    //allocate matrix
    results->matrix = (int **)malloc(count * sizeof(int *));
    int a;
    for (a = 0; a < count; a++)
    {
        results->matrix[a] = (int *)malloc(lcm * sizeof(int));
    }

    //add tasks to priority queue
    tasks[0].task_number = c;
    tasks[0].pendingExecTime = tasks[0].execTime;
    Node *p_queue = newNode(tasks[0], tasks[0].period);
    int i;
    for (i = 1; i < count; i++)
    {
        tasks[i].task_number = ++c;
        tasks[i].pendingExecTime = tasks[i].execTime;
        push(&p_queue, tasks[i], tasks[i].period);
    }

    //prebuild matrix (blanks and periods)
    int j, k;
    int b = 0;
    int deadlines_count = computeDealinesCount(tasks, lcm, count);
    deadline deadlines[deadlines_count];
    for (j = 0; j < count; j++)
    {
        int p = tasks[j].period;
        int n = tasks[j].task_number;

        deadline d;

        for (k = 0; k < lcm; k++)
        {
            if (k > 0 && k % p == 0)
            {
                //results->matrix[j][k] = n;
                d.row = j;
                d.column = k - 1;
                d.task_number = n;
                deadlines[b++] = d;
            }
            else
            {
                results->matrix[j][k] = 0;
            }
        }
    }

    //TODO: fill the matrix with tasks.
    int start_col = 0;
    deadline *c_deadlines;
    while (1)
    {
        if (!isEmpty(&p_queue))
        {
            task t = pop(&p_queue);
            j = t.task_number - 1;
            k = 0;
            for (; j < count; j++)
            {
                //t = pop(&p_queue);

                for (k = start_col; k <= (start_col + t.execTime); k++)
                {
                    if (t.pendingExecTime > 0)
                    {
                        results->matrix[j][k] = t.task_number;
                        t.pendingExecTime--;
                        start_col++;
                    }
                    else
                    {
                        break;
                    }

                    //check for deadlines
                    c_deadlines = getDeadlines(k, &deadlines, deadlines_count);
                    if (c_deadlines)
                    {
                        if (t.pendingExecTime > 0)
                        {
                            if (isEmpty(&p_queue))
                            {
                                p_queue = newNode(t, t.period);
                            }
                            else
                            {
                                push(&p_queue, t, t.period);
                            }
                        }

                        int deadlinesInCol = getDeadlinesPresentInColumn(k, &deadlines, deadlines_count);
                        int y;
                        for (y = 0; y < deadlinesInCol; y++)
                        {
                            task taskToPush = tasks[c_deadlines[y].task_number - 1];

                            if (Exists(&p_queue, taskToPush)) // failed deadline
                            {
                                k++;
                                j = c_deadlines[y].row;

                                results->matrix[j][k] = 13; //13 means failed deadline
                                return;
                            }

                            if (isEmpty(&p_queue))
                            {
                                p_queue = newNode(taskToPush, taskToPush.period);
                            }
                            else
                            {
                                push(&p_queue, taskToPush, taskToPush.period);
                            }
                        }

                        break;
                    }
                }

                if (!isEmpty(&p_queue))
                {
                    t = pop(&p_queue);
                    j = t.task_number - 2;
                }
                else
                {
                    //check for deadlines
                    c_deadlines = getDeadlines(k, &deadlines, deadlines_count);
                    if (c_deadlines)
                    {
                        if (t.pendingExecTime > 0)
                        {
                            if (isEmpty(&p_queue))
                            {
                                p_queue = newNode(t, t.period);
                            }
                            else
                            {
                                push(&p_queue, t, t.period);
                            }
                        }

                        int deadlinesInCol = getDeadlinesPresentInColumn(k, &deadlines, deadlines_count);
                        int y;
                        for (y = 0; y < deadlinesInCol; y++)
                        {
                            task taskToPush = tasks[c_deadlines[y].task_number - 1];
                            if (isEmpty(&p_queue))
                            {
                                p_queue = newNode(taskToPush, taskToPush.period);
                            }
                            else
                            {
                                push(&p_queue, taskToPush, taskToPush.period);
                            }
                        }
                    }
                    // else
                    // {
                    //     if (k < lcm)
                    //     {
                    //         int x;
                    //         for (x = 0; x < count; x++)
                    //         {
                    //             results->matrix[x][k] = 7;
                    //         }
                    //         start_col++;
                    //         j = 0;
                    //     }
                    //     else
                    //     {
                    //         return;
                    //     }
                        
                    // }
                }
            }
        }
        else
        {
            if (k < lcm)
                k++;
            else
            {
                return;
            }
        }
    }
}