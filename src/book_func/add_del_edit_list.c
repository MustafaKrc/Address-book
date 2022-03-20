#include <stdio.h>
#include <string.h>

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

Status deleteContact(AddressBook *book, Contact **picked_contact, Node **deleted_contacts_stack)
{
    if (*picked_contact == NULL)
    {
        printf("You must pick a contact first!\n");
        return exit_not_picked_contact;
    }
    (*picked_contact)->stat = deleted;
    *deleted_contacts_stack = stackPush(*picked_contact, *deleted_contacts_stack);
    // picked_contact = NULL;
    printf("Deleted the picked contact!\n");
    return exit_success;
}

Status editContact(Contact **picked_contact, Node **edited_contacts, Node **deleted_contacts)
{
    Contact *dummy_contact = initContact();
    getInfo(dummy_contact);
    (*picked_contact)->stat = deleted;

    *deleted_contacts = stackPush(*picked_contact, *deleted_contacts);
    *edited_contacts = insertByOrder(*edited_contacts, dummy_contact);

    return exit_success;
}

Status listContacts(AddressBook *book)
{
    printContacts(book->contacts, book->contact_count);
    // enter anything to continue

    return exit_success;
}