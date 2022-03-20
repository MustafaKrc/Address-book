#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../header/types.h"
#include "../header/string_func.h"

Node *initNode(Contact *contact)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->contact = contact;
    return new_node;
}

Node *insertByOrder(Node *head, Contact *new_contact)
{
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

bool isEmptyNode(Node *head) // double linked list
{
    if (head == NULL)
        return true;
    return false;
}

/*

void Print(Node *head)
{
    printf("Linked list = ");
    while (head != NULL)
    {
        printf(" %d", head->contact);
        head = head->next;
    }
    printf("\n");
}

Node *Reverse(Node *head)
{
    Node *temp;
    while (head != NULL)
    {
        temp = head->prev;
        head->prev = head->next;
        head->next = temp;
        head = head->prev;
    }

    return temp->prev;
}

Node *Remove(Node *head, int index)
{
    if (index < 0)
    {
        printf("Invalid!\n");
        return head;
    }
    if (index == 0)
    {
        Node *new_head;
        new_head = head->next;
        head->next->prev = NULL;
        free(head);

        return new_head;
    }

    int curr_index = -1;
    Node *removed_element;
    Node *head_copy = head;

    while (head != NULL)
    {
        curr_index += 1;
        if (curr_index == index - 1)
        {
            removed_element = head->next;
            if (removed_element->next != NULL)
            {
                head->next = head->next->next;
                head->next->prev = head;
            }
            else
            {
                head->next = NULL;
            }

            free(removed_element);
            break;
        }
        head = head->next;
    }
    if (curr_index != index - 1)
    {
        printf("Linked List is too short!\n");
    }
    return head_copy;
}

int Get(Node *head, int index)
{
    int curr_index = -1;

    while (head != NULL)
    {
        curr_index += 1;
        if (curr_index == index)
        {
            return head->contact;
        }
        head = head->next;
    }
    printf("Linked list is too short!\n");
    return 0;
}

void PrintBackwards(Node *head)
{
    if (head == NULL)
    {
        return;
    }
    while (head->next != NULL)
    {
        head = head->next;
    }
    printf("Reverse Linked List = ");

    while (head != NULL)
    {
        printf(" %d", head->contact);
        head = head->prev;
    }
    printf("\n");
}

*/
