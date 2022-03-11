#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include "types.h"
#include "stdbool.h"
#include <stdlib.h>

Node *insertByOrder(Node *, Contact *);
Contact *pop(Node **);

#endif