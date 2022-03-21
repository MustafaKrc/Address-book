#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../header/types.h"

Node *stackPush(Contact *contact, Node *head)
{
    /*
        Pushes given contact to given head node
        return the new head
        creates new node for given contact
    */
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
    /*
        Pops the head node of given head node and returns its contact
    */
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
    /*
        Returns the contact of given head node
        Returns null if stack is empty
    */
    if (head == NULL)
    {
        return NULL;
    }
    return head->contact;
}
