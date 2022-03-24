#include <stdio.h>
#include <stdlib.h>

#include "../header/types.h"
#include "../header/stack.h"
#include "../header/double_linked_list.h"

Status discardAllChanges(Node **edited_contacts, Node **deleted_contacts)
{
    /*
        Discarding all non saved changes
        Saved changes are not tracked, therefore cannot reversed
    */
    while (*edited_contacts != NULL)
    {
        pop(edited_contacts);
    }
    while (stackTop(*deleted_contacts) != NULL)
    {
        stackTop(*deleted_contacts)->stat = unchanged; // setting stat to unchanged from deleted
        stackPop(deleted_contacts);
    }
    *edited_contacts = NULL;
    *deleted_contacts = NULL;
    return exit_success;
}