#ifndef MENU_H
#define MENU_H

#include "data_structures/types.h"

MenuOption getOption(InputType, const char *);   // might not be needed
Status menu(AddressBook **, Node *, Contact **); // parameters: PartialAddressBook *

#endif