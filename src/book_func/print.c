#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <string.h>

#include "../header/types.h"
#include "../header/math_func.h"

void sleepScreen(int amount_in_seconds)
{
    /*
        Freezing screen for given amount in seconds
    */
    sleep(amount_in_seconds);
}

void clearScreen()
{
    /*
        Clearing screen
    */
    printf("\e[1;1H\e[2J");
}

void printContactHeader()
{
    /*
        printing matched contact header
    */
    printf("_________________________________________________________________________");
    printf("____________________");
    printf("_________________________________");
    printf("_\n");

    printf("|                             Name and Surname                           ");
    printf("|   Phone Number  ");
    printf("|               Email              ");
    printf("|\n");
}

void printContactSeperator()
{
    /*
        printing the matched contact seperator
    */
    printf("|                                                                        ");
    printf("|                 ");
    printf("|                                  ");
    printf("|\n");
}

void printContact(Contact *contact, unsigned int print_index)
{
    /*
        Prints the contact information with adjusted spacing for the table
    */
    int name_space = F_NAME_LEN + L_NAME_LEN - digitCount(print_index) - strlen(contact->f_name) - strlen(contact->l_name) + 4;
    int number_space = NUMBER_LEN - strlen(contact->phone_number) + 1;
    int email_space = EMAIL_LEN - strlen(contact->email) + 1;

    printf("|");
    printf("%u-", print_index);
    for (int i = 0; i < name_space / 2; i++)
    {
        printf(" ");
    }
    printf("%s %s", contact->f_name, contact->l_name);
    for (int i = 0; i < (name_space % 2 == 1 ? (name_space / 2) + 1 : name_space / 2); i++)
    {
        printf(" ");
    }
    printf("|");

    for (int i = 0; i < number_space / 2; i++)
    {
        printf(" ");
    }
    printf("%s", contact->phone_number);
    for (int i = 0; i < (number_space % 2 == 1 ? (number_space / 2) + 1 : number_space / 2); i++)
    {
        printf(" ");
    }
    printf("|");
    for (int i = 0; i < email_space / 2; i++)
    {
        printf(" ");
    }
    printf("%s", contact->email);
    for (int i = 0; i < (email_space % 2 == 1 ? (email_space / 2) + 1 : email_space / 2); i++)
    {
        printf(" ");
    }
    printf("|\n");
}

void printContactFooter()
{
    /*
        prints the matched contact footer
    */
    printf("|________________________________________________________________________");
    printf("____________________");
    printf("_________________________________");
    printf("|\n");
}

void printContacts(Contact **contacts, unsigned int count)
{
    /*
        Prints the matched contacts table
    */
    if (count == 0)
    {
        printf("There isn't any contact!\n");
        sleepScreen(2);
        return;
    }
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