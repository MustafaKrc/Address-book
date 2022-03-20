#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header/file_operations.h"
#include "header/types.h"
#include "header/add_del_edit_list.h"
#include "header/search.h"
#include "header/print.h"
#include "header/discard.h"
#include "header/string_func.h"

MenuOption getOption(InputType input_type, const char *message)
{
    char char_input[3];
    int int_input;
    char int_input_safe[3];
    printf("%s\n", message);
    switch (input_type)
    {
    case input_char:
        scanf("%2s", char_input);
        fflush(stdin);

        if (compareCaseIgnore(char_input, "y"))
            return yes;
        else if (compareCaseIgnore(char_input, "n"))
            return no;
        else
        {
            printf("Invalid!\n");
            return getOption(input_type, message);
        }

    case input_integer:
        scanf("%3s", int_input_safe);
        fflush(stdin);
        int_input = atoi(int_input_safe);

        switch (int_input)
        {
        case 1:
            return add_contact;
        case 2:
            return search_contact;
        case 3:
            return edit_contact;
        case 4:
            return delete_contact;
        case 5:
            return list_contacts;
        case 6:
            return save_changes;
        case 7:
            return discard_all_changes;

        case 0:
            if (strcmp("0", int_input_safe) == 0)
            {
                return close_app;
            }
            printf("Invalid!\n");
            return getOption(input_type, message);

        default:
            printf("Invalid!\n");
            return getOption(input_type, message);
        }

    default:
        printf("Invalid input_type\n");
        return exit_failure_unknown;
    }
}

void menuWelcome()
{
    printf("******* Address Book *******\n");
    sleepScreen(1);
    printf("Note: Changes will be applied after saving!\n\n");
    sleepScreen(3);
}

Status askSaveFile(AddressBook **book, Node **edited_contacts, Node *deleted_contacts)
{
    MenuOption grant = getOption(input_char, "Would you like to save now? (Y/N): ");

    if (grant == yes)
    {
        return quickSaveFile(book, edited_contacts, deleted_contacts);
    }
    return exit_success;
}

Status updatePrompt(char **main_menu_prompt, Contact **picked_contact)
{

    if (*picked_contact != NULL)
    {
        sprintf(*main_menu_prompt,
                "Please choose one of actions below!\n1-)Add Contact\n2-)Search and Pick Contact\n3-)Edit Contact                                            %s\n4-)Delete Contact                                        Name and Surname: %s %s\n5-)List All Contacts                                         Phone Number: %s\n6-)Save Changes                                                     Email: %s\n7-)Discard All Changes\n0-)Exit\n",
                "Picked Contact: ", (*picked_contact)->f_name, (*picked_contact)->l_name, (*picked_contact)->phone_number, (*picked_contact)->email);
    }
    else
    {
        sprintf(*main_menu_prompt, "Please choose one of actions below!\n1-)Add Contact\n2-)Search and Pick Contact%65s\n3-)Edit Contact\n4-)Delete Contact\n5-)List All Contacts\n6-)Save Changes\n7-)Discard All Changes\n0-)Exit\n",
                "Pick any contact to see information here");
    }

    return exit_success;
}

// ASK NOT TO SAVE BEFORE EXİT AND CHANGE İT TO EXİT
// SEGMANTATION FAULT İF NO CONTACT İS ADDED AND USER TRIES TO SEARCH !!
// after file saving,and loading book,,, picked contact will be gone!

// contact import from phones

Status menu(AddressBook **book, Node *edited_contacts, Contact **picked_contact, Node *deleted_contacts_stack) // parameters: PartialAddressBook *address_book
{
    MenuOption operation;

    clearScreen();
    menuWelcome();

    char *main_menu_prompt = (char *)malloc(sizeof(char) * 700);

    updatePrompt(&main_menu_prompt, picked_contact);
    operation = getOption(input_integer, main_menu_prompt);

    // ask if user wants to save
    // print info about you need to save the file to apply changes!
    while (operation != close_app)
    {
        switch (operation)
        {
        case add_contact:
            addContact(&edited_contacts);
            askSaveFile(book, &edited_contacts, deleted_contacts_stack);
            clearScreen();
            break;
        case search_contact:
            searchContact(*book, picked_contact);
            sleepScreen(1);
            clearScreen();
            if (*picked_contact != NULL)
            {
                printf("Picked the account!\n");
            }

            break;
        case edit_contact:
            editContact(picked_contact, &edited_contacts, &deleted_contacts_stack);
            askSaveFile(book, &edited_contacts, deleted_contacts_stack);
            // clearScreen();

            break;
        case delete_contact:
            clearScreen();
            if (deleteContact(*book, picked_contact, &deleted_contacts_stack) != exit_not_picked_contact)
            {
                askSaveFile(book, &edited_contacts, deleted_contacts_stack);
                clearScreen();
            }

            break;
        case list_contacts:
            clearScreen();
            listContacts(*book);

            break;
        case discard_all_changes:
            clearScreen();
            discardAllChanges(&edited_contacts, deleted_contacts_stack);
            printf("Discarded all non saved changes!\n");
            break;

        case save_changes:
            quickSaveFile(book, &edited_contacts, deleted_contacts_stack);
            clearScreen();
            printf("Saved!\n\n");
            break;
        case close_app:
            printf("%d", close_app);
            askSaveFile(book, &edited_contacts, deleted_contacts_stack);

            clearScreen();
            printf("Closing...\n");
            sleepScreen(1);
            return exit_success;

        default:
            printf("Invalid!\n");
            break;
        }
        updatePrompt(&main_menu_prompt, picked_contact);
        operation = getOption(input_integer, main_menu_prompt);
    }

    return exit_success;
}