#ifndef BOOK_H
#define BOOK_H

#include "data_structures/types.h"

AddressBook *initBook();
Contact *initContact();
Node *initEditedContacts();

Status addContact(Node **head_edited_contacts);
Status editContact(AddressBook *book);
Status searchContact(AddressBook *book, Contact **picked_contact);
Status deleteContact(AddressBook *book, Contact **picked_contact);
#endif