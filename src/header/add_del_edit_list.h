#ifndef ADD_DEL_EDIT_H
#define ADD_DEL_EDIT_H

#include "types.h"

Status addContact(Node **head_edited_contacts);
Status deleteContact(Contact **picked_contacts, Node **deleted_contacts);
Status editContact(Contact **picked_contact, Node **edited_contacts, Node **deleted_contacts);
Status listContacts(AddressBook *book, Contact **picked_contact);

#endif