#include <stdio.h>
#include <stdlib.h>

#include "../header/types.h"
#include "../header/stack.h"
#include "../header/double_linked_list.h"

Status discardAllChanges(Node **edited_contacts, Node *deleted_contacts)
{

    while (*edited_contacts != NULL)
    {
        pop(edited_contacts);
    }

    while (stackTop(deleted_contacts) != NULL)
    {
        stackTop(deleted_contacts)->stat = unchanged;
        stackPop(&deleted_contacts);
    }
    return exit_success;
}