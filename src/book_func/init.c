#include <stdio.h>
#include <stdlib.h>

#include "../header/file_operations.h"
#include "../header/types.h"

AddressBook *initBook()
{
    /*
        Initializing book file and reading contacts from contacts file
        Returns the initialized book file
    */
    AddressBook *book = (AddressBook *)malloc(sizeof(AddressBook));
    loadFile(book);

    return book;
}

Node *initEditedContacts()
{
    /*
        Initializing edited_contacts head
        this function had more tasks, but later it got reduced
    */
    Node *head = NULL;
    return head;
}

Contact *initContact()
{
    /*
        Initializing Contact variable
        allocating memory and setting default values
    */
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