#include <stdio.h>
#include <string.h>

#include "init.h"
#include "../menu.h"
#include "../data_structures/types.h"
#include "../data_structures/double_linked_list.h"
#include "../misc/string_func.h"

Status getInfo(Contact *contact)
{
    MenuOption confirmation;
getInfo:
    printf("(OPTIONAL, enter - to skip!) Please enter the name of new contact!:(32MAX) ");
    scanf(" %32s", contact->f_name);
    fflush(stdin);

    printf("(OPTIONAL, enter - to skip!) Please enter the surname of new contact!:(32MAX) ");
    scanf(" %32s", contact->l_name);
    fflush(stdin);

    if (strcmp(contact->f_name, "-") == 0 && strcmp(contact->l_name, "-") == 0)
    {
        printf("You must enter atleast 1 paramter!\n");
        goto getInfo;
    }

askPhoneNumber:
    printf("Please enter the phone number of new contact!:(15MAX) ");
    scanf(" %32s", contact->phone_number);
    fflush(stdin);
    if (!isOnlyDigit(contact->phone_number))
    {
        printf("Invalid phone number!\n");
        goto askPhoneNumber;
    }

    printf("(OPTIONAL, enter - to skip!) Please enter the email of new contact!:(32MAX) ");
    scanf("%32s", contact->email);
    fflush(stdin);

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

Status deleteContact(AddressBook *book, Contact **picked_contact)
{
    if (*picked_contact == NULL)
    {
        printf("You must pick a contact first!\n");
        return exit_not_picked_contact;
    }
    (*picked_contact)->stat = deleted;
    *picked_contact = NULL;
    printf("Deleted the picked contact!\n");
    return exit_success;
}

Status editContact(AddressBook *book)
{
    // init new contact, get info, set contact new_info to old infos(new contact),
    // set contact new info to new created contact(old contact)

    return exit_success;
}