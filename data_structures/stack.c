#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"
#include <string.h>

Node *stackPush(Contact *contact, Node *head)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->contact = contact;
    new_node->next = head;
    new_node->prev = NULL;
    if (head == NULL)
    {
        return new_node;
    }
    head->prev = new_node;
    return new_node;
}

Contact *stackPop(Node **head)
{
    Contact *contact = (*head)->contact;
    Node *temp = *head;
    *head = (*head)->next;
    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }
    free(temp);
    return contact;
}

Contact *stackTop(Node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    return head->contact;
}

/*

void push(struct String **head, char val[STRING_LEN])
{
    struct String *node = (struct String *)malloc(sizeof(struct String));

    strcpy(node->val, val);
    node->next = *head;
    *head = node;
}

char *pop(struct String **head)
{


        //DONT FORGET TO FREE RETURN VALUE AFTER USE



if (*head == NULL)
{
    return '\0';
}
struct String *temp = *head;
*head = (*head)->next;
char *val = (char *)malloc(sizeof(char) * STRING_LEN);
strcpy(val, temp->val);
free(temp);
return val;
}

char *top(struct String *head)
{
    if (head == NULL)
    {
        return '\0';
    }
    return head->val;
}

bool isEmpty(struct String *head)
{
    return head == NULL;
}

void Print(struct String *head)
{
    // might not fully print string, might need nested while loops
    printf("Linked List = ");
    while (head != NULL)
    {
        printf("%s", head->val);
        head = head->next;
    }
    printf("\n");
}

void reverse(struct String **head)
{
    struct String *stack;
    struct String *beginning = *head;
    while (*head != NULL)
    {
        push(&stack, (*head)->val);
        *head = (*head)->next;
    }
    *head = beginning;
    while (beginning != NULL)
    {
        strcpy(beginning->val, pop(&stack));
        beginning = beginning->next;
    }
}
*/