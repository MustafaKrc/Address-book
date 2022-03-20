#include <stdio.h>
#include <stdlib.h>

#include "../header/file_operations.h"
#include "../header/types.h"

AddressBook *initBook()
{
    AddressBook *book = (AddressBook *)malloc(sizeof(AddressBook));
    loadFile(book);

    return book;
}

Node *initEditedContacts()
{
    Node *head = NULL;
    return head;
}

Contact *initContact()
{
    Contact *contact = (Contact *)malloc(sizeof(Contact));
    contact->f_name = (char *)malloc(sizeof(char) * F_NAME_LEN);
    contact->l_name = (char *)malloc(sizeof(char) * L_NAME_LEN);
    contact->email = (char *)malloc(sizeof(char) * EMAIL_LEN);
    contact->phone_number = (char *)malloc(sizeof(char) * NUMBER_LEN);
    contact->index = 0;
    contact->new_info = NULL;
    contact->stat = unchanged;

    return contact;
}