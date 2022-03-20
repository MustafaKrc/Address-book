#ifndef STACK_H
#define STACK_h

#define STRING_LEN 33

#include <stdbool.h>
#include "types.h"

Node *stackPush(Contact *contact, Node *head_stack);
Contact *stackPop(Node **head_stack);
Contact *stackTop(Node *head_stack);

#endif