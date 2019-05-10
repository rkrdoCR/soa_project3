#include "priority_queue.h"

Node *newNode(task d, int p)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;

    return temp;
}

// Return the value at head
task peek(Node **head)
{
    return (*head)->data;
}

// Removes the element with the
// highest priority form the list
task pop(Node **head)
{
    Node *temp = *head;
    (*head) = (*head)->next;

    return temp->data;
    //free(temp);
}

// Function to push according to priority
void push(Node **head, task d, int p)
{
    Node *start = (*head);

    // Create new Node
    Node *temp = newNode(d, p);

    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->priority > p)
    {

        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else
    {

        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL &&
               start->next->priority < p)
        {
            start = start->next;
        }

        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}

//Function to check if a task is in the queue
int Exists(Node **head, task target)
{
    if(isEmpty(head))
        return 0;

    Node *current = (*head);

    if(current != NULL && current->next == NULL)
    {
        if(current->data.task_number == target.task_number)
            return 1;
    }

    while(current->next != NULL)
    {
        if(current->data.task_number == target.task_number)
            return 1;
        
        current = current->next;
    }
    return 0;
}

// Function to check is list is empty
int isEmpty(Node **head)
{
    return (*head) == NULL;
}