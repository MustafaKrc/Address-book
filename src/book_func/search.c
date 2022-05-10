#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../header/print.h"
#include "../header/menu.h"
#include "../header/types.h"
#include "../header/double_linked_list.h"
#include "../header/stack.h"
#include "../header/string_func.h"

Status getName(char f_name[F_NAME_LEN], char l_name[L_NAME_LEN])
{
    /*
        Asks user to enter name and surname
        if user enters "-", app will ignore it
    */
ask_names:
    printf("(Enter - to skip!) Enter the name of contact: ");
    scanf("%32s", f_name);
    clearBuffer();
    printf("(Enter - to skip!) Enter the surname of contact: ");
    scanf("%32s", l_name);
    clearBuffer();

    if (strcmp(f_name, "-") == 0 && strcmp(l_name, "-") == 0)
    {
        printf("You must enter atleast 1 parameter!\n");
        goto ask_names;
    }

    return exit_success;
}

Status getPhoneNumber(char phone_number[NUMBER_LEN])
{
    /*
        Asks user to enter phone number
    */
ask_phone_number:
    printf("Enter the phone number of contact: ");
    scanf("%32s", phone_number);
    clearBuffer();
    if (!isOnlyDigit(phone_number))
    {
        printf("Invalid number!\n");
        goto ask_phone_number;
    }
    return exit_success;
}

Status getEmail(char email[EMAIL_LEN])
{
    /*
        Asks user to enter email
    */
ask_email:
    printf("Enter the email of contact: ");
    scanf("%32s", email);
    clearBuffer();
    if (strcmp(email, "-") == 0)
    {
        printf("Invalid!\n");
        goto ask_email;
    }

    return exit_success;
}

void printMatchedContacts(MatchedContacts *matched_contacts)
{
    /*
        printing matched contacts
    */
    printContacts(matched_contacts->matches, matched_contacts->count);
}

void appendMatchedContact(AddressBook *book, MatchedContacts *matched_contacts,
                          unsigned long int *arr_size, unsigned long int matched_contact_index)
{
    /*
        appending the matched contact to the matched contacts object
    */
    if (matched_contacts->count < *arr_size - 1)
    {
        matched_contacts->matches[(matched_contacts->count)++] = book->contacts[matched_contact_index];
    }
    else
    {
        *arr_size *= 4;
        matched_contacts->matches = (Contact **)realloc(matched_contacts->matches, *arr_size);
        matched_contacts->matches[(matched_contacts->count)++] = book->contacts[matched_contact_index];
    }
}

MatchedContacts *findBinarySearch(AddressBook *book, Contact *dummy_contact, SearchType search_type)
{
    /*
        Looks for exact matches of dummy contact in book parameter.
        Can only be used for search_type = byName, because contacts are only ordered by name

        Returns array of matched contacts
    */
    MatchedContacts *matched_contacts = (MatchedContacts *)malloc(sizeof(MatchedContacts));
    unsigned long int arr_size = 4; // to keep track of memory alloctaion to matched_contacts
    matched_contacts->count = 0;
    matched_contacts->matches = (Contact **)malloc(sizeof(Contact *) * arr_size);
    long int lower = 0;
    long int upper = book->contact_count - 1;
    long int middle;
    long int before_check = 1;
    long int after_check = 1;
    Node *stack_head = NULL;
    Contact *ordered_contact;

    // simple binary search
    while (lower <= upper && lower >= 0)
    {
        middle = (lower + upper) / 2;
        if (isSameContact(book->contacts[middle], dummy_contact, search_type))
        {
            // matching contact is found, now it will traverse backwards to check other contacts if they are also same contact
            //  use stack here to make it alphabeticly ordered !!(because it is going backwards)
            while (middle - before_check >= 0 && isSameContact(book->contacts[middle - before_check], dummy_contact, search_type))
            {
                stack_head = stackPush(book->contacts[middle - (before_check)++], stack_head);
            }
            // now we are popping stack and pushing found contacts into the matches
            // popping makes them ordered
            while (stackTop(stack_head) != NULL)
            {
                ordered_contact = stackPop(&stack_head);
                // cannot use appendMatchedContact function here, because the assigned contact is not book indexed(it comes from stack)
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
            // adding the initally found contact into mathces
            appendMatchedContact(book, matched_contacts, &arr_size, middle);

            // now it will check following contacts if they are same and adding them into matches
            // no need for stack here because they are already ordered(checking forwards)
            while (middle + after_check <= book->contact_count - 1 && isSameContact(book->contacts[middle + after_check], dummy_contact, search_type))
            {
                appendMatchedContact(book, matched_contacts, &arr_size, (middle + (after_check)++));
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

MatchedContacts *findLinearSearch(AddressBook *book, Contact *dummy_contact, SearchType search_type)
{
    /*
        Lineer search to find exact match of dummy contact in the book parameter by search_type
        Returns array of matched contacts
    */
    MatchedContacts *matched_contacts = (MatchedContacts *)malloc(sizeof(MatchedContacts));
    unsigned long int arr_size = 4;
    matched_contacts->count = 0;
    matched_contacts->matches = (Contact **)malloc(sizeof(Contact *) * arr_size);

    for (unsigned int i = 0; i < book->contact_count; i++)
    {
        if (isSameContact(book->contacts[i], dummy_contact, search_type))
        {
            appendMatchedContact(book, matched_contacts, &arr_size, i);
        }
    }
    return matched_contacts;
}

MatchedContacts *AdvancedSearch(AddressBook *book, MatchedContacts *matched_contacts,
                                Contact *dummy_contact, SearchType search_type)
{
    /*
        Advanced stands for existence of substrings (contacts will be displayed even if they are not same)
        Can be used for all search_types because it is doing linear search (binary is impossible)

        Returns array of matched contacts
    */
    free(matched_contacts->matches); // freeing previously found matched contacts

    matched_contacts = (MatchedContacts *)calloc(sizeof(MatchedContacts), 1);
    unsigned long int arr_size = 4;
    matched_contacts->count = 0;
    matched_contacts->matches = (Contact **)malloc(sizeof(Contact *) * arr_size);

    for (unsigned int i = 0; i < book->contact_count; i++)
    {
        if (isSubstringContact(book->contacts[i], dummy_contact, search_type))
        {
            appendMatchedContact(book, matched_contacts, &arr_size, i);
        }
    }
    return matched_contacts;
}

Contact *pickContact_again(AddressBook *book, MatchedContacts *matched_contacts,
                           Contact *dummy_contact, SearchType search_type, bool is_contact_found)
{
    /*
        Ask user to pick contact above listed matched contacts
        difference between pickContact and pickContact_again is that _again function does not ask for Advanced search

        returns the picked contact or NULL if user doesnt select anything
    */
    Contact *picked_contact;
    int picked_index;
    char picked_index_safe[10]; // using string in scanf in order to prevent scanf from reading char which causes infinite loop
ask_contact_again:
    if (is_contact_found)
    {
        printf("Enter the index number of the contact you want to pick and pin to main menu!\nEnter 0 to quit picking\n: ");
        scanf("%9s", picked_index_safe);
        clearBuffer();
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
    /*
    Ask user to pick contact above listed matched contacts

    returns the picked contact or NULL if user doesnt select anything
*/
    int picked_index;
    char picked_index_safe[10]; // using string in scanf in order to prevent scanf from reading char which causes infinite loop
    Contact *picked_contact;
ask_contact:

    printf("Enter the index number of the contact you want to pick and pin to main menu!\nEnter 0 to quit picking\n");
    if (!is_advanced_searched)
    {
        printf("Enter -1 to do advanced search\n");
    }
    scanf("%9s", picked_index_safe);
    clearBuffer();
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
            sleepScreen(2);
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

Status searchContact(AddressBook *book, Contact **pinned_contact)
{
    /*
        Asks user to select search_type and calls the findContact function
        The picked contact will be written inside the given Contact** picked_contact parameter
    */

    char ask_search_type[3];
    SearchType search_type;
    // Contact *searched_contact = NULL;

    char f_name[F_NAME_LEN];
    char l_name[L_NAME_LEN];
    char phone_number[NUMBER_LEN];
    char email[EMAIL_LEN];

    Contact *dummy_contact = (Contact *)malloc(sizeof(Contact)); // dummy will be deleted later, just needed to hold information which user gives

    dummy_contact->f_name = f_name;
    dummy_contact->l_name = l_name;
    dummy_contact->phone_number = phone_number;
    dummy_contact->email = email;

    MatchedContacts *matched_contacts;
    Contact *picked_contact = (Contact *)malloc(sizeof(Contact));

    MenuOption opinion;
ask_search_type:
    printf("How would you like to search contact:\n1- By Name 2- By Phone number 3- By Email: ");
    scanf("%2s", ask_search_type);
    clearBuffer();

    if (strcmp(ask_search_type, "1") == 0)
    {
        search_type = byName;

        getName(f_name, l_name);
        matched_contacts = findBinarySearch(book, dummy_contact, search_type);

        if (matched_contacts->count > 0)
        {
            printMatchedContacts(matched_contacts);
            picked_contact = pickContact(book, matched_contacts, dummy_contact, search_type, false);
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
                }
                else
                {
                    printf("There was no matching contact!\n");
                    sleepScreen(2);
                }
            case no:
                break;
            default:
                // not possible
                break;
            }
        }
    }
    else if (strcmp(ask_search_type, "2") == 0)
    {
        search_type = byPhoneNumber;

        getPhoneNumber(phone_number);
        matched_contacts = findLinearSearch(book, dummy_contact, search_type);
        if (matched_contacts->count > 0)
        {
            printMatchedContacts(matched_contacts);
            picked_contact = pickContact(book, matched_contacts, dummy_contact, search_type, false);
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
                }
                else
                {
                    printf("There was no matching contact!\n");
                    sleepScreen(2);
                }
            case no:
                break;
            default:
                // not possible
                break;
            }
        }
    }
    else if (strcmp(ask_search_type, "3") == 0)
    {
        search_type = byEmail;

        getEmail(email);
        matched_contacts = findLinearSearch(book, dummy_contact, search_type);
        if (matched_contacts->count > 0)
        {
            printMatchedContacts(matched_contacts);
            picked_contact = pickContact(book, matched_contacts, dummy_contact, search_type, false);
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
                }
                else
                {
                    printf("There was no matching contact!\n");
                    sleepScreen(2);
                }
            case no:
                break;
            default:
                // not possible
                break;
            }
        }
    }
    else
    {
        printf("Invalid\n");
        goto ask_search_type;
    }

    // searched_contact = findContact(book, search_type);
    free(dummy_contact);
    *pinned_contact = picked_contact;

    return exit_success;
}