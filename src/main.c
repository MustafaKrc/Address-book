#include <stdio.h>
#include "header/menu.h"
#include "header/init.h"
#include "header/types.h"

int main(void)
{

    AddressBook *book = initBook();
    Node *edited_contacts = initEditedContacts();
    Contact *picked_contact = NULL;
    Node *deleted_contacts = NULL;

    menu(&book, edited_contacts, &picked_contact, deleted_contacts);

    return 0;
}