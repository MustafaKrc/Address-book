#include <stdio.h>
#include <stdlib.h>

#include "../data_structures/types.h"
#include "../data_structures/stack.h"
#include "../data_structures/double_linked_list.h"

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