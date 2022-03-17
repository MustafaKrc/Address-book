#ifndef ADD_DEL_EDIT_H
#define ADD_DEL_EDIT_H

#include "../data_structures/types.h"

Status addContact(Node **head_edited_contacts);
Status deleteContact(AddressBook *book, Contact **picked_contacts);

#endif