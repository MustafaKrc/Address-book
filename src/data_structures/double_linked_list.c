#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../header/types.h"
#include "../header/string_func.h"

Node *initNode(Contact *contact)
{
    /*
        Initializing new Node object with given contact and returning it
    */
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->contact = contact;
    return new_node;
}

Node *insertByOrder(Node *head, Contact *new_contact)
{
    /*
        Inserts the given contact into the given head variable by alphabetical order
    */
    Node *node_new_contact = initNode(new_contact);
    Node *prev_node;
    Node *head_copy = head;

    if (head == NULL)
    {
        head = node_new_contact;
        return head;
    }

    while (head_copy != NULL && isPreviousContact(head_copy->contact, node_new_contact->contact, false, 0))
    {
        prev_node = head_copy;
        head_copy = head_copy->next;
    }

    if (head_copy == NULL)
    {
        prev_node->next = node_new_contact;
        node_new_contact->prev = prev_node;
        return head;
    }
    if (head_copy == head)
    {
        node_new_contact->next = head_copy;
        head_copy->prev = node_new_contact;
        head = node_new_contact;
        return head;
    }

    prev_node->next = node_new_contact;
    node_new_contact->prev = prev_node;
    node_new_contact->next = head_copy;
    head_copy->prev = node_new_contact;

    return head;
}

Contact *pop(Node **head)
{
    /*
        Returns the contact of head element and pops the head element
    */
    Contact *temp = (*head)->contact;
    Node *temp_head = *head;

    if ((*head)->next == NULL)
    {
        free(temp_head);
        (*head) = NULL;
        return temp;
    }
    (*head)->next->prev = NULL;
    (*head) = (*head)->next;
    free(temp_head);
    return temp;
}

bool isEmptyNode(Node *head) // doubly linked list
{
    /*
        Returns true if given head node is empty
    */
    if (head == NULL)
        return true;
    return false;
}
