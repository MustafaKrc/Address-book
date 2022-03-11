#include <stdlib.h>
#include <stdio.h>
#include "data_structures/types.h"
#include "file_operations.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "data_structures/types.h"

/*
void safeClose(PartialAddressBook *)
{
    saveFile(contacts);
    exit(0);
}
*/

// isEmptyStack()

int digitCount(int number)
{
    int digit = 0;
    while (number > 0)
    {
        number /= 10;
        digit++;
    }
    return digit;
}

void printContactHeader()
{
    // 1 + 65 + 1 + 15 + 1 + 32 +
    printf("|                        Name and Surname                        ");
    printf("|  Phone Number  ");
    printf("|             Email             ");
    printf("|\n");
}

void printContactSeperator()
{
    printf("|                                                                ");
    printf("|                ");
    printf("|                               ");
    printf("|\n");
}

void printContact(Contact *contact, unsigned int print_index)
{

    printf("|");
    printf("%u-", print_index);
    for (int i = 0; i < (F_NAME_LEN + L_NAME_LEN - 3 - digitCount(print_index) - (strlen(contact->f_name) + strlen(contact->l_name))) / 2; i++)
    {
        printf(" ");
    }
    printf("%s %s", contact->f_name, contact->l_name);
    for (int i = 0; i < (F_NAME_LEN + L_NAME_LEN - 3 - digitCount(print_index) - (strlen(contact->f_name) + strlen(contact->l_name))) / 2; i++)
    {
        printf(" ");
    }
    printf("|");

    for (int i = 0; i < (NUMBER_LEN - strlen(contact->phone_number)) / 2; i++)
    {
        printf(" ");
    }
    printf("%s", contact->phone_number);
    for (int i = 0; i < (NUMBER_LEN - strlen(contact->phone_number)) / 2; i++)
    {
        printf(" ");
    }
    printf("|");
    for (int i = 0; i < (EMAIL_LEN - 1 - strlen(contact->email)) / 2; i++)
    {
        printf(" ");
    }
    printf("%s", contact->email);
    for (int i = 0; i < (EMAIL_LEN - 1 - strlen(contact->email)) / 2; i++)
    {
        printf(" ");
    }
    printf("|\n");
}

void printContactFooter()
{
    printf("|________________________________________________________________");
    printf("_________________");
    printf("________________________________");
    printf("|\n");
}

void printContacts(Contact **contacts, unsigned int count)
{
    unsigned int index = 0;
    printContactHeader();

    while (index < count - 1)
    {
        printContact(contacts[index], index + 1);
        printContactSeperator();
        index++;
    }
    printContact(contacts[index], index + 1);
    printContactFooter();
}

bool isEmptyNode(Node *head) // double linked list
{
    if (head == NULL)
        return true;
    return false;
}

void clearScreen()
{
    printf("\e[1;1H\e[2J");
}

bool compareCaseIgnore(char *word1, char *word2)
{
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
    switch (search_type)
    {
    case byName:
        if (strcmp(dummy_contact->f_name, "-") == 0)
        {
            if (compareCaseIgnore(dummy_contact->l_name, contact->l_name))
            {
                return true;
            }
            return false;
        }
        else if (strcmp(dummy_contact->l_name, "-") == 0)
        {
            if (compareCaseIgnore(dummy_contact->f_name, contact->f_name))
            {
                return true;
            }
            return false;
        }
        else
        {
            if (compareCaseIgnore(dummy_contact->f_name, contact->f_name) &&
                compareCaseIgnore(dummy_contact->l_name, contact->l_name))
            {
                return true;
            }
            return false;
        }
    case byPhoneNumber:
        return compareCaseIgnore(dummy_contact->phone_number, contact->phone_number);

    case byEmail:
        return compareCaseIgnore(dummy_contact->email, contact->email);
    }
    return false;
}

bool cmp(char *p, char *s, int idx, int m)
{
    for (int i = 0; i < m; i++)
        if (p[i] != s[idx + i])
            return false;
    return true;
}

bool strstrCaseIgnore(char *word1, char *word2)
{

    int M = 1e9 + 9, p = 31, n = strlen(word1), m = strlen(word2);
    int h = 1, a = 0, b = 0;
    if (m > n)
        return false;

    for (int i = 0; i < m - 1; i++)
    {
        h = (h * p) % M;
    }

    for (int i = 0; i < m; i++)
    {
        a = a * p + word1[i];
        b = b * p + word2[i];
        a %= M;
        b %= M;
    }

    for (int i = m; i <= n; i++)
    {
        if (a == b && cmp(word2, word1, i - m, m))
        {
            return true;
        }

        if (i < n)
        {
            a = (p * (a - h * word1[i - m]) + word1[i]) % M;
        }

        if (a < 0)
        {
            a += M;
        }
    }

    return false;
}

bool isSubstringContact(Contact *contact, Contact *dummy_contact, SearchType search_type)
{
    switch (search_type)
    {
    case byName:
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

        return (strstrCaseIgnore(contact->phone_number, dummy_contact->phone_number) &&
                strstrCaseIgnore(contact->phone_number, dummy_contact->phone_number));

    case byEmail:

        return (strstrCaseIgnore(contact->phone_number, dummy_contact->phone_number) &&
                strstrCaseIgnore(contact->phone_number, dummy_contact->phone_number));
    }
    return false;
}

bool isPreviousContact(Contact *contact1, Contact *contact2, bool is_surname, int index)
{
    char first_char1;
    char first_char2;
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
    while (*input)
    {
        if (isdigit(*input++) == 0)
        {
            return 0;
        }
    }
    return 1;
}