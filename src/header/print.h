#ifndef PRINT_H
#define PRINT_H

#include "types.h"

void clearScreen();
void sleepScreen(int amount_in_seconds);
void printContacts(Contact **contacts, unsigned int count);

#endif