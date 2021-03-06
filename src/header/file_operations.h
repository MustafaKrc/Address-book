#ifndef FILE_OPERATORS_H
#define FILE_OPERATORS_H

#include "types.h"

Status loadFile(AddressBook *book);
Status quickSaveFile(AddressBook **book, Node **edited_contacts, Node *deleted_contacts);

#endif