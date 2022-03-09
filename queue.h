#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct node
{
    char data;
    struct node* next;
}node;

node* CreateNode(char);
node* Enqueue(node*,char);
char Dequeue(node**);

node* CreateNode(char value)
{
    node *n = (node*) malloc(sizeof(node));

    if(n == NULL)
    {
        puts("error creating node!");
        return n;
    }

    n->data = value;
    n->next = NULL;

    return n;
}

node* Enqueue(node *head, char value)
{
    node *temp = head;
    node *_node = CreateNode(value);

    if(temp == NULL)
    {
        head = _node;
        return head;
    }

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = _node;
    return head;
}

char Dequeue(node **head)
{
    node* value;

    if(*head == NULL)
    {
        return ' ';
    }

    value = *head;

    *head = (*head)->next;

    return value->data;
}

void PrintQueue(node *head)
{
    if(head == NULL) 
    {
        puts("Queue empty");
        return;
    }

    while(head != NULL)
    {
        printf("%c->", head->data);
        head = head->next;
    }
    printf("null\n");
}

#endif