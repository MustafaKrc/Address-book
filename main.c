#include <stdio.h>
#include "menu.h"
#include "book_func/init.h"
#include "data_structures/types.h"

// test

/*
    ***pseudo code***

    return enum status

    file operations -> load- save

    contact operations ->
        menu, add contact,
        search contact, edit contact,
        delete contact, list contacts,


*/

int main(void)
{

    AddressBook *book = initBook();
    Node *edited_contacts = initEditedContacts();
    Contact *picked_contact = NULL;
    Node *deleted_contacts = NULL;

    menu(&book, edited_contacts, &picked_contact, deleted_contacts);

    // test
    // printf("%s %s %s %s\n", picked_contact->f_name, picked_contact->l_name, picked_contact->phone_number, picked_contact->email);

    return 0;
}