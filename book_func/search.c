#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "print.h"
#include "../menu.h"
#include "../data_structures/types.h"
#include "../data_structures/double_linked_list.h"
#include "../data_structures/stack.h"
#include "../misc/string_func.h"

Status getName(char f_name[F_NAME_LEN], char l_name[L_NAME_LEN])
{
ask_names:
    printf("(Enter - to skip!) Enter the name of contact: ");
    scanf("%32s", f_name);
    fflush(stdin);
    printf("(Enter - to skip!) Enter the surname of contact: ");
    scanf("%32s", l_name);
    fflush(stdin);

    if (strcmp(f_name, "-") == 0 && strcmp(l_name, "-") == 0)
    {
        printf("You must enter atleast 1 parameter!\n");
        goto ask_names;
    }

    return exit_success;
}

Status getPhoneNumber(char phone_number[NUMBER_LEN])
{
ask_phone_number:
    printf("Enter the phone number of contact: ");
    scanf("%32s", phone_number);
    fflush(stdin);
    if (!isOnlyDigit(phone_number))
    {
        printf("Invalid number!\n");
        goto ask_phone_number;
    }
    return exit_success;
}

Status getEmail(char email[EMAIL_LEN])
{
ask_email:
    printf("Enter the email of contact: ");
    scanf("%32s", email);
    fflush(stdin);
    if (strcmp(email, "-") == 0)
    {
        printf("Invalid!\n");
        goto ask_email;
    }

    return exit_success;
}

MatchedContacts *findBinarySearch(AddressBook *book, Contact *dummy_contact, SearchType search_type)
{
    if (book->contact_count == 0)
    {
        printf("There isn't any contact!\n");
        sleepScreen(2);
        return NULL;
    }

    MatchedContacts *matched_contacts = (MatchedContacts *)malloc(sizeof(MatchedContacts));
    long int arr_size = 4;
    matched_contacts->count = 0;
    matched_contacts->matches = (Contact **)malloc(sizeof(Contact *) * arr_size);
    long int lower = 0;
    long int upper = book->contact_count - 1;
    long int middle;
    long int before_check = 1;
    long int after_check = 1;
    Node *stack_head = NULL;
    Contact *ordered_contact;

    while (lower <= upper && lower >= 0)
    {
        middle = (lower + upper) / 2;
        if (isSameContact(book->contacts[middle], dummy_contact, search_type))
        {

            // use stack here to make it alphabeticly ordered !!
            while (middle - before_check >= 0 && isSameContact(book->contacts[middle - before_check], dummy_contact, search_type))
            {
                stack_head = stackPush(book->contacts[middle - (before_check)++], stack_head);
            }

            while (stackTop(stack_head) != NULL)
            {
                ordered_contact = stackPop(&stack_head);
                if (matched_contacts->count < arr_size - 1)
                {
                    matched_contacts->matches[(matched_contacts->count)++] = ordered_contact;
                }
                else
                {
                    arr_size *= 4;
                    matched_contacts->matches = (Contact **)realloc(matched_contacts->matches, arr_size);
                    matched_contacts->matches[(matched_contacts->count)++] = ordered_contact;
                }
            }

            if (matched_contacts->count < arr_size - 1)
            {
                matched_contacts->matches[(matched_contacts->count)++] = book->contacts[middle];
            }
            else
            {
                arr_size *= 4;
                matched_contacts->matches = (Contact **)realloc(matched_contacts->matches, arr_size);
                matched_contacts->matches[(matched_contacts->count)++] = book->contacts[middle];
            }

            while (middle + after_check <= book->contact_count - 1 && isSameContact(book->contacts[middle + after_check], dummy_contact, search_type))
            {
                if (matched_contacts->count < arr_size - 1)
                {
                    matched_contacts->matches[(matched_contacts->count)++] = book->contacts[middle + (after_check)++];
                }
                else
                {
                    arr_size *= 4;
                    matched_contacts->matches = (Contact **)realloc(matched_contacts->matches, arr_size);
                    matched_contacts->matches[(matched_contacts->count)++] = book->contacts[middle + (after_check)++];
                }
            }

            return matched_contacts;
        }

        else if (isPreviousContact(book->contacts[middle], dummy_contact, false, 0))
        {
            lower = middle + 1;
        }
        else
        {
            upper = middle - 1;
        }
    }
    return matched_contacts;
}

void printMatchedContacts(MatchedContacts *matched_contacts)
{
    printContacts(matched_contacts->matches, matched_contacts->count);
}

MatchedContacts *AdvancedSearch(AddressBook *book, MatchedContacts *matched_contacts,
                                Contact *dummy_contact, SearchType search_type)
{
    // segmentation fault if no contacts match
    free(matched_contacts->matches);

    matched_contacts = (MatchedContacts *)calloc(sizeof(MatchedContacts), 1);
    unsigned int arr_size = 4;
    matched_contacts->count = 0;
    matched_contacts->matches = (Contact **)malloc(sizeof(Contact *) * arr_size);

    for (unsigned int i = 0; i < book->contact_count; i++)
    {

        if (isSubstringContact(book->contacts[i], dummy_contact, search_type))
        {
            if (matched_contacts->count < arr_size - 1)
            {
                matched_contacts->matches[(matched_contacts->count)++] = book->contacts[i];
            }
            else
            {
                arr_size *= 4;
                matched_contacts->matches = (Contact **)realloc(matched_contacts->matches, arr_size);
                matched_contacts->matches[(matched_contacts->count)++] = book->contacts[i];
            }
        }
    }
    return matched_contacts;
}

Contact *pickContact_again(AddressBook *book, MatchedContacts *matched_contacts,
                           Contact *dummy_contact, SearchType search_type, bool is_contact_found)
{
    Contact *picked_contact;
    int picked_index;
    char picked_index_safe[3];
ask_contact_again:
    if (is_contact_found)
    {
        printf("Enter the index number of the contact you want to pick and pin to main menu!\nEnter 0 to quit picking\n: ");
        scanf("%2s", picked_index_safe);
        fflush(stdin);
        picked_index = atoi(picked_index_safe);
    }
    else
    {
        free(matched_contacts->matches);
        free(matched_contacts);
        return NULL;
    }

    switch (picked_index)
    {
    case 0:
        if (strcmp(picked_index_safe, "0") == 0)
        {
            free(matched_contacts->matches);
            free(matched_contacts);
            return NULL;
        }
        else
        {
            printf("Invalid!\n");
            goto ask_contact_again;
        }

    default:
        if (picked_index > matched_contacts->count)
        {
            printf("Index is too big!\n");
            goto ask_contact_again;
        }
        picked_contact = matched_contacts->matches[picked_index - 1];
        free(matched_contacts->matches);
        free(matched_contacts);
        return picked_contact;
    }
}

Contact *pickContact(AddressBook *book, MatchedContacts *matched_contacts,
                     Contact *dummy_contact, SearchType search_type, bool is_advanced_searched)
{
    int picked_index;
    char picked_index_safe[3];
    Contact *picked_contact;
ask_contact:

    printf("Enter the index number of the contact you want to pick and pin to main menu!\nEnter 0 to quit picking\n");
    if (!is_advanced_searched)
    {
        printf("Enter -1 to do advanced search\n");
    }
    scanf("%2s", picked_index_safe);
    fflush(stdin);
    picked_index = atoi(picked_index_safe);

    switch (picked_index)
    {
    case -1:
        if (is_advanced_searched)
        {
            printf("Invalid!\n");
            goto ask_contact;
        }
        matched_contacts = AdvancedSearch(book, matched_contacts, dummy_contact, search_type);

        if (matched_contacts->count == 0)
        {
            printf("There was not any contact matching your search!\n");
            return pickContact_again(book, matched_contacts, dummy_contact, search_type, false);
        }
        else
        {
            printMatchedContacts(matched_contacts);
            return pickContact_again(book, matched_contacts, dummy_contact, search_type, true);
        }

    case 0:
        if (strcmp(picked_index_safe, "0") == 0)
        {
            free(matched_contacts->matches);
            free(matched_contacts);
            return NULL;
        }
        else
        {
            printf("Invalid\n");
            goto ask_contact;
        }

    default:
        if (picked_index > matched_contacts->count)
        {
            printf("Index is too big!\n");
            goto ask_contact;
        }
        picked_contact = matched_contacts->matches[picked_index - 1];
        free(matched_contacts->matches);
        free(matched_contacts);
        return picked_contact;
    }
}

MatchedContacts *findLinearSearch(AddressBook *book, Contact *dummy_contact, SearchType search_type)
{
    MatchedContacts *matched_contacts = (MatchedContacts *)malloc(sizeof(MatchedContacts));
    unsigned int arr_size = 4;
    matched_contacts->count = 0;
    matched_contacts->matches = (Contact **)malloc(sizeof(Contact *) * arr_size);

    for (unsigned int i = 0; i < book->contact_count; i++)
    {
        if (isSameContact(book->contacts[i], dummy_contact, search_type))
        {
            if (matched_contacts->count < arr_size - 1)
            {
                matched_contacts->matches[(matched_contacts->count)++] = book->contacts[i];
            }
            else
            {
                arr_size *= 4;
                matched_contacts->matches = (Contact **)realloc(matched_contacts->matches, arr_size);
                matched_contacts->matches[(matched_contacts->count)++] = book->contacts[i];
            }
        }
    }
    return matched_contacts;
}

Contact *findContact(AddressBook *book, SearchType search_type)
{
    // check nearest (up and down contacts) if they match, if they do put them in array and ask user to select one (1-9)
    // this function better return contact* array instead of pointer MAYBE NOT

    // DONT FORGET TO FREE DUMMY
    char f_name[F_NAME_LEN];
    char l_name[L_NAME_LEN];
    char phone_number[NUMBER_LEN];
    char email[EMAIL_LEN];

    // dummy declared here to skip info part
    Contact *dummy_contact = (Contact *)malloc(sizeof(Contact));

    dummy_contact->f_name = f_name;
    dummy_contact->l_name = l_name;
    dummy_contact->phone_number = phone_number;
    dummy_contact->email = email;

    MatchedContacts *matched_contacts;
    Contact *picked_contact = (Contact *)malloc(sizeof(Contact));

    MenuOption opinion;

    switch (search_type)
    {
    case byName:
        getName(f_name, l_name);
        matched_contacts = findBinarySearch(book, dummy_contact, search_type);
        if (matched_contacts == NULL)
        {
            free(dummy_contact);
            return NULL;
        }
        if (matched_contacts->count > 0)
        {
            printMatchedContacts(matched_contacts);
            picked_contact = pickContact(book, matched_contacts, dummy_contact, search_type, false);
            free(dummy_contact);
            return picked_contact;
        }
        else
        {
            opinion = getOption(input_char, "There was not any contact matching your search!\nWould you like to do advanced search? (Y/N): ");
            switch (opinion)
            {
            case yes:
                matched_contacts = AdvancedSearch(book, matched_contacts, dummy_contact, search_type);
                if (matched_contacts->count > 0)
                {
                    printMatchedContacts(matched_contacts);
                    picked_contact = pickContact(book, matched_contacts, dummy_contact, search_type, true);
                    free(dummy_contact);
                    return picked_contact;
                }
                else
                {
                    printf("There was no matching contact!\n");
                    free(dummy_contact);
                    return NULL;
                }
            case no:
                free(dummy_contact);
                return NULL;
            default:
                printf("This isnt possible or is it?\nin function: findContact\n");
                break;
            }
        }

    case byPhoneNumber:
        getPhoneNumber(phone_number);
        matched_contacts = findLinearSearch(book, dummy_contact, search_type);
        if (matched_contacts->count > 0)
        {
            printMatchedContacts(matched_contacts);
            picked_contact = pickContact(book, matched_contacts, dummy_contact, search_type, false);
            free(dummy_contact);
            return picked_contact;
        }
        else
        {
            opinion = getOption(input_char, "There was not any contact matching your search!\nWould you like to do advanced search? (Y/N): ");
            switch (opinion)
            {
            case yes:
                picked_contact = pickContact(book, matched_contacts, dummy_contact, search_type, false);
                free(dummy_contact);
                return picked_contact;
            case no:
                free(dummy_contact);
                return NULL;
            default:
                printf("This isnt possible or is it?\nin function: findContact\n");
                break;
            }
        }

    case byEmail:
        getEmail(email);
        matched_contacts = findLinearSearch(book, dummy_contact, search_type);
        if (matched_contacts->count > 0)
        {
            printMatchedContacts(matched_contacts);
            picked_contact = pickContact(book, matched_contacts, dummy_contact, search_type, false);
            free(dummy_contact);
            return picked_contact;
        }
        else
        {
            opinion = getOption(input_char, "There was not any contact matching your search!\nWould you like to do advanced search? (Y/N): ");
            switch (opinion)
            {
            case yes:
                picked_contact = pickContact(book, matched_contacts, dummy_contact, search_type, false);
                free(dummy_contact);
                return picked_contact;
            case no:
                free(dummy_contact);
                return NULL;
            default:
                printf("This isnt possible or is it?\nin function: findContact\n");
                break;
            }
        }
    }
    free(dummy_contact);
    return NULL; // not necessity
}

Status searchContact(AddressBook *book, Contact **picked_contact)
{
    // full matching name +"-" or maybe non matching surname causing segmentation fault

    char temp[3];
    SearchType search_type;
    Contact *searched_contact;
ask_search_type:
    printf("How would you like to search contact:\n1- By Name 2- By Phone number 3- By Email: ");
    scanf("%2s", temp);
    fflush(stdin);

    if (strcmp(temp, "1") == 0)
    {
        search_type = byName;
    }
    else if (strcmp(temp, "2") == 0)
    {
        search_type = byPhoneNumber;
    }
    else if (strcmp(temp, "3") == 0)
    {
        search_type = byEmail;
    }
    else
    {
        printf("Invalid\n");
        goto ask_search_type;
    }

    searched_contact = findContact(book, search_type);

    if (searched_contact == NULL)
    {
        *picked_contact = NULL;
        // either not found or user quit finding
    }
    else
    {
        *picked_contact = searched_contact;
    }
    return exit_success;
}