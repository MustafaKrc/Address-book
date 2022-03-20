#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <stdbool.h>

#include "types.h"

Node *insertByOrder(Node *, Contact *);
Contact *pop(Node **);
bool isEmptyNode(Node *head);

#endif