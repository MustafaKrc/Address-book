#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "../header/types.h"

bool compareCaseIgnore(char *word1, char *word2)
{
    /*
        Comparing string (Case insensitive)
    */
    char char1 = tolower(*word1);
    char char2 = tolower(*word2);
    while (*word1 != '\0')
    {

        if (char1 != char2)
        {
            return false;
        }
        word1++;
        word2++;
        char1 = tolower(*word1);
        char2 = tolower(*word2);
    }
    if (*word2 != '\0')
    {
        return false;
    }
    return true;
}

bool isSameContact(Contact *contact, Contact *dummy_contact, SearchType search_type)
{
    /*
        Comparing contacts by given search_type parameter
        Comparing is done by comparing strings of contact(only the search_type strings)
    */
    switch (search_type)
    {
    case byName:
        // ignoring if string is "-"
        if (strcmp(dummy_contact->f_name, "-") == 0)
        {
            return compareCaseIgnore(dummy_contact->l_name, contact->l_name);
        }
        else if (strcmp(dummy_contact->l_name, "-") == 0)
        {
            return compareCaseIgnore(dummy_contact->f_name, contact->f_name);
        }
        else
        {
            return (compareCaseIgnore(dummy_contact->f_name, contact->f_name) &&
                    compareCaseIgnore(dummy_contact->l_name, contact->l_name));
        }
    case byPhoneNumber:
        return compareCaseIgnore(dummy_contact->phone_number, contact->phone_number);

    case byEmail:
        return compareCaseIgnore(dummy_contact->email, contact->email);
    }
    return false;
}

bool strstrCaseIgnore(const char *haystack, const char *needle)
{
    /*
        Implementation of strstr function in string.h but case insensitive
        Returns true if substring exists
    */
    char *pptr = (char *)needle;
    char *start = (char *)haystack;
    char *sptr;
    int slen = strlen(haystack);
    int plen = strlen(needle);

    for (; slen >= plen; start++, slen--)
    {

        while (toupper(*start) != toupper(*needle))
        {
            start++;
            slen--;
            if (slen < plen)
            {
                return false;
            }
        }

        sptr = start;
        pptr = (char *)needle;
        while (toupper(*sptr) == toupper(*pptr))
        {
            sptr++;
            pptr++;
            if ('\0' == *pptr)
            {
                return true;
            }
        }
    }

    return false;
}

bool isSubstringContact(Contact *contact, Contact *dummy_contact, SearchType search_type)
{
    /*
        Returns true if search_type of dummy_contact is substring of search_type of contact
    */
    switch (search_type)
    {
    case byName:
        // ignoring if string is "-"
        if (strcmp(dummy_contact->f_name, "-") == 0)
        {
            return strstrCaseIgnore(contact->l_name, dummy_contact->l_name);
        }
        else if (strcmp(dummy_contact->l_name, "-") == 0)
        {
            return strstrCaseIgnore(contact->f_name, dummy_contact->f_name);
        }
        else
        {
            return (strstrCaseIgnore(contact->f_name, dummy_contact->f_name) &&
                    strstrCaseIgnore(contact->l_name, dummy_contact->l_name));
        }

    case byPhoneNumber:
        return strstrCaseIgnore(contact->phone_number, dummy_contact->phone_number);

    case byEmail:
        return strstrCaseIgnore(contact->email, dummy_contact->email);
    }
    return false;
}

bool isPreviousContact(Contact *contact1, Contact *contact2, bool is_surname, int index)
{
    /*
        Returns true if contact1 is alphabetically previous than contact2 (names)

        is_surname should be false at initial call(function will switch to true if two contact has same name)
        index should be 0 at initial call as it indicates the indexes of chars that will be compared
    */
    char first_char1;
    char first_char2;
    // using tolower to prevent upper cases being previous than lower cases in everycase
    if (is_surname)
    {
        first_char1 = tolower(contact1->l_name[index]);
        first_char2 = tolower(contact2->l_name[index]);
    }
    else
    {
        first_char1 = tolower(contact1->f_name[index]);
        first_char2 = tolower(contact2->f_name[index]);
    }

    if (first_char1 == '\0' && first_char2 == '\0')
    {
        if (is_surname)
        {
            return true;
        }
        else
        {
            return isPreviousContact(contact1, contact2, true, 0);
        }
    }

    if (first_char1 == '\0')
        return true;

    if (first_char2 == '\0')
        return false;

    if (first_char1 - first_char2 < 0)
        return true;

    if (first_char1 - first_char2 > 0)
        return false;

    return isPreviousContact(contact1, contact2, is_surname, index + 1);
}

bool isOnlyDigit(char *input)
{
    /*
        Returns true if given string is only digit
    */
    while (*input)
    {
        if (isdigit(*input++) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void clearBuffer()
{
    /*
        Clears input buffer to prevent unwanted behaviour
    */
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}