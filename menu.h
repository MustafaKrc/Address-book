#ifndef MENU_H
#define MENU_H

#include "data_structures/types.h"

MenuOption getOption(InputType input_type, const char *message);                                          // might not be needed
Status menu(AddressBook **book, Node *edited_contacts, Contact **picked_contact, Node *deleted_contacts); // parameters: PartialAddressBook *

#endif