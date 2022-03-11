#ifndef FILE_OPERATORS_H
#define FILE_OPERATORS_H

Status loadFile(AddressBook *book);
Status quickSaveFile(AddressBook **book, Node **edited_contacts);
Status safeCloseApp(AddressBook **book, Node **edited_contacts);

#endif