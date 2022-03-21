#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../header/init.h"
#include "../header/print.h"
#include "../header/menu.h"
#include "../header/types.h"
#include "../header/double_linked_list.h"
#include "../header/stack.h"
#include "../header/string_func.h"

Status getInfo(Contact *contact)
{
    MenuOption confirmation;
getInfo:
    printf("(OPTIONAL, enter - to skip!) Please enter the name of new contact!:(32MAX) ");
    scanf(" %32s", contact->f_name);
    clearBuffer();

    printf("(OPTIONAL, enter - to skip!) Please enter the surname of new contact!:(32MAX) ");
    scanf(" %32s", contact->l_name);
    clearBuffer();

    if (strcmp(contact->f_name, "-") == 0 && strcmp(contact->l_name, "-") == 0)
    {
        printf("You must enter atleast 1 paramter!\n");
        goto getInfo;
    }

askPhoneNumber:
    printf("Please enter the phone number of new contact!:(15MAX) ");
    scanf(" %32s", contact->phone_number);
    clearBuffer();
    if (!isOnlyDigit(contact->phone_number))
    {
        printf("Invalid phone number!\n");
        goto askPhoneNumber;
    }

    printf("(OPTIONAL, enter - to skip!) Please enter the email of new contact!:(32MAX) ");
    scanf("%32s", contact->email);
    clearBuffer();

    printf("New Contact:\nName and surname: %s %s\nPhone number: %s\nEmail: %s\n",
           contact->f_name, contact->l_name, contact->phone_number, contact->email);

    confirmation = getOption(input_char, "Confirm new contact informations (Y/N): ");
    if (confirmation == no)
    {
        goto getInfo;
    }

    return exit_success;
}

Status addContact(Node **head_edited_contacts)
{
    Contact *new_contact = initContact();
    getInfo(new_contact);

    *head_edited_contacts = insertByOrder(*head_edited_contacts, new_contact);

    return exit_success;
}

Status deleteContact(AddressBook *book, Contact **picked_contact, Node **deleted_contacts_stack)
{
    if (*picked_contact == NULL)
    {
        printf("You must pick a contact first!\n");
        return exit_not_picked_contact;
    }
    (*picked_contact)->stat = deleted;
    *deleted_contacts_stack = stackPush(*picked_contact, *deleted_contacts_stack);
    *picked_contact = NULL;
    printf("Deleted the picked contact!\n");
    return exit_success;
}

Status editContact(Contact **picked_contact, Node **edited_contacts, Node **deleted_contacts)
{
    if (*picked_contact == NULL)
    {
        printf("You must pick a contact first!\n\n");
        return exit_not_picked_contact;
    }

    Contact *dummy_contact = initContact();
    getInfo(dummy_contact);
    (*picked_contact)->stat = deleted;
    (*picked_contact) = NULL;

    *deleted_contacts = stackPush(*picked_contact, *deleted_contacts);
    *edited_contacts = insertByOrder(*edited_contacts, dummy_contact);

    clearScreen();
    printf("Edited the account!\n\n");

    return exit_success;
}

Contact *pickAmongAllContacts(AddressBook *book)
{
    int picked_index;
    char picked_index_safe[3];
    Contact *picked_contact;
ask_contact_all:

    printf("Enter the index number of the contact you want to pick and pin to main menu!\nEnter 0 to quit picking\n");

    scanf("%2s", picked_index_safe);
    clearBuffer();
    picked_index = atoi(picked_index_safe);

    switch (picked_index)
    {

    case 0:
        if (strcmp(picked_index_safe, "0") == 0)
        {
            return NULL;
        }
        else
        {
            printf("Invalid\n");
            goto ask_contact_all;
        }

    default:
        if (picked_index > book->contact_count)
        {
            printf("Index is too big!\n");
            goto ask_contact_all;
        }
        picked_contact = book->contacts[picked_index - 1];
        return picked_contact;
    }
    return NULL;
}

Status listContacts(AddressBook *book, Contact **picked_contact)
{
    printContacts(book->contacts, book->contact_count);
    if (book->contact_count > 0)
    {
        *picked_contact = pickAmongAllContacts(book);
    }

    return exit_success;
}