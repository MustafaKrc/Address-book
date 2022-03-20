#ifndef MENU_H
#define MENU_H

#include "types.h"

MenuOption getOption(InputType input_type, const char *message);
Status menu(AddressBook **book, Node *edited_contacts, Contact **picked_contact, Node *deleted_contacts);

#endif