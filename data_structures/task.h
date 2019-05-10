#ifndef TASK_H
#define TASK_H

typedef struct
{
    int task_number;
    int execTime;
    int pendingExecTime;
    int period;   
} task;

#endif