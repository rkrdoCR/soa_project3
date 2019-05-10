#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_h

#include <stdlib.h>

#include "data_structures/task.h"

typedef struct node
{
    task data;

    // Lower values indicate higher priority
    int priority;

    struct node *next;

} Node;

Node *newNode(task d, int p);
task peek(Node **head);
task pop(Node **head);
void push(Node **head, task d, int p);
int Exists(Node **head, task target);
int isEmpty(Node **head);

#endif