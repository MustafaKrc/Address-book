#include <stdio.h>
#include <string.h>

#include "book_func/init.h"
#include "data_structures/types.h"
#include "data_structures/double_linked_list.h"
#include "data_structures/stack.h"
#include "misc/string_func.h"

#define CONTACT_FILE "contacts.vcf"
#define TEMP_FILE "temp.vcf"

Status loadFile(AddressBook *book)
{
    FILE *contacts_file = fopen(CONTACT_FILE, "r");

    if (contacts_file == NULL)
    {
        book->contact_count = 0;
        book->contacts[0] = NULL;
        return exit_success;
    }

    book->contacts[0] = initContact();

    unsigned int count = 0;
    while (fscanf(contacts_file, "%u %s %s %s %s\n",
                  &(book->contacts[count]->index), book->contacts[count]->f_name,
                  book->contacts[count]->l_name, book->contacts[count]->phone_number,
                  book->contacts[count]->email) != EOF)
    {

        book->contacts[count]->new_info = NULL;

        book->contacts[++count] = initContact();
    }
    book->contact_count = count;
    book->contacts[count] = NULL;
    fclose(contacts_file);
    return exit_success;
}

Status saveFile(AddressBook **book, Node **edited_contacts_head, Node **deleted_contacts)
{

    FILE *new_file = fopen(TEMP_FILE, "a+");
    if (new_file == NULL)
        return exit_failure_cannot_open_file;

    unsigned int contact_index = 0;
    unsigned int file_contact_index = 0;
    Contact *temp;

    while (!isEmptyNode(*edited_contacts_head) || (*book)->contacts[contact_index] != NULL)
    {
        if ((*book)->contacts[contact_index] != NULL && !isEmptyNode(*edited_contacts_head))
        {
            if (isPreviousContact((*book)->contacts[contact_index], (*edited_contacts_head)->contact, false, 0))
            {
                temp = (*book)->contacts[contact_index++];
            }

            else
            {
                temp = pop(edited_contacts_head);
            }
        }
        else if ((*book)->contacts[contact_index] != NULL)
        {
            temp = (*book)->contacts[contact_index++];
        }
        else if (!isEmptyNode(*edited_contacts_head))
        {
            temp = pop(edited_contacts_head);
        }
        else
        {
            return exit_save_error;
        }

        switch (temp->stat)
        {

        case unchanged:
            fprintf(new_file, "%u %s %s %s %s\n",
                    file_contact_index, temp->f_name,
                    temp->l_name, temp->phone_number,
                    temp->email);
            file_contact_index++;
            free(temp);
            break;
        case deleted:
            free(temp);
            break;

        default:
            return exit_failure_invalid_contact_stat;
        }
    }

    // need to clear deleted_contacts if it is not empty
    *deleted_contacts = NULL;

    fclose(new_file);
    rename(TEMP_FILE, CONTACT_FILE);
    free(*book);
    *book = initBook();

    return exit_success;
}

Status quickSaveFile(AddressBook **book, Node **edited_contacts, Node *deleted_contacts)
{
    saveFile(book, edited_contacts, &deleted_contacts);
    loadFile(*book);
    return exit_success;
}

Status safeCloseApp(AddressBook **book, Node **edited_contacts, Node *deleted_contacts)
{
    saveFile(book, edited_contacts, &deleted_contacts);
    return exit_success;
}
