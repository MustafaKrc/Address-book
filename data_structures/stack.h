#ifndef STACK_H
#define STACK_h

#define STRING_LEN 33

#include "types.h"

Node *stackPush(Contact *, Node *);
Contact *stackPop(Node **);
Contact *stackTop(Node *);

#endif