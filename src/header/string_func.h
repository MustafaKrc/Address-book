#ifndef STRING_FUNC_H
#define STRING_FUNC_H

#include <stdbool.h>

#include "types.h"

bool compareCaseIgnore(char *word1, char *word2);
bool strstrCaseIgnore(char *word1, char *word2);

bool isSameContact(Contact *contact, Contact *dummy_contact, SearchType search_type);
bool isSubstringContact(Contact *contact, Contact *dummy_contact, SearchType search_type);
bool isPreviousContact(Contact *contact1, Contact *contact2, bool is_surname, int starting_index);

bool isOnlyDigit(char *input);
bool clearBuffer();

#endif