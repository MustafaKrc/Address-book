#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>

void clearScreen(void);
bool isPreviousContact(Contact *, Contact *, bool, int);
bool isOnlyDigit(char *);
bool isEmptyNode(Node *);
bool isSameContact(Contact *contact, Contact *dummy_contact, SearchType);
void printContacts(Contact **, unsigned int count);
bool isSubstringContact(Contact *contact, Contact *dummy_contact, SearchType);
bool compareCaseIgnore(char *word1, char *word2);

#endif