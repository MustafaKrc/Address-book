#ifndef TYPES_H
#define TYPES_H
// max 32 char;
#define F_NAME_LEN 33
#define L_NAME_LEN 33
#define NUMBER_LEN 16
#define EMAIL_LEN 33
#define MAX_LINE_LENGTH 200 // must be greater than F_NAME_LEN + L_NAME_LEN + NUMBER_LEN + EMAIL_LEN

#define CONTACT_COUNT 32768 // 2^15(about 1.75 mb of memory) max contact count

typedef enum
{
    add_contact,
    search_contact,
    edit_contact,
    delete_contact,
    list_contacts,
    save_changes,
    discard_all_changes,
    close_app,
    yes,
    no

} MenuOption;

typedef enum
{
    exit_success,
    exit_failure_unknown,
    exit_failure_invalid_file_ptr,
    exit_failure_cannot_open_file,
    exit_failure_invalid_contact_stat,
    invalid_input_type,
    exit_not_picked_contact,
    exit_save_error

} Status;

typedef enum
{
    byName,
    byPhoneNumber,
    byEmail
} SearchType;

typedef enum
{
    unchanged,
    deleted
} ContactStatus;

typedef enum
{
    input_char,
    input_integer,

} InputType;

typedef struct Contact
{
    char *f_name;
    char *l_name;
    char *phone_number;
    char *email;
    unsigned int index;
    struct Contact *new_info;
    ContactStatus stat;

} Contact;

typedef struct AddressBook
{
    unsigned int contact_count;
    Contact *contacts[CONTACT_COUNT];

} AddressBook;

typedef struct Node
{
    Contact *contact;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct MatchedContacts
{
    unsigned int count;
    Contact **matches;
} MatchedContacts;

#endif