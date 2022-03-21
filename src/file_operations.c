#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header/init.h"
#include "header/types.h"
#include "header/double_linked_list.h"
#include "header/stack.h"
#include "header/string_func.h"
#include "header/print.h"

#define CONTACT_FILE "contacts.vcf"
#define TEMP_FILE "temp.vcf" // new save will be written here and changed name to CONTACT_FILE

Status loadFile(AddressBook *book)
{
    /*
        Loads file into given book parameter
    */
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
    /*
        Saves changes into the file
    */

    FILE *new_file = fopen(TEMP_FILE, "a+");
    if (new_file == NULL)
        return exit_failure_cannot_open_file;

    unsigned int contact_index = 0;
    unsigned int file_contact_index = 0;
    Contact *temp;

    while (!isEmptyNode(*edited_contacts_head) || (*book)->contacts[contact_index] != NULL)
    {
        // getting the alphabetically first contact from loaded contacts and added(edited) contacts into the temp variable
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
    *deleted_contacts = NULL; // deleting deleted_contacts just in case
                              // freeing inside elements will throw double free error as they were freed in discardAllChanges() function.

    fclose(new_file);
    rename(TEMP_FILE, CONTACT_FILE);
    free(*book);
    *book = NULL;

    return exit_success;
}

Status quickSaveFile(AddressBook **book, Node **edited_contacts, Node *deleted_contacts)
{
    /*
        Saves file and loads saved file into the given book parameter
    */
    saveFile(book, edited_contacts, &deleted_contacts);
    clearScreen();
    printf("Saved!\n\n");
    loadFile(*book);
    return exit_success;
}
