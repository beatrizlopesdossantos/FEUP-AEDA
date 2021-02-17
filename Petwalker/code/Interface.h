#ifndef PETWALKERPROJAEDA_INTERFACE_H
#define PETWALKERPROJAEDA_INTERFACE_H

#include "Exceptions.h"
#include "Petwalker.h" //já inclui os servicos, clients, employees e date

/**
 * This function is used to ask the user what he wants to do in the company.
 * It outputs the 'main menu' of the Petwalker Interface.
 */
bool beginning();
/**
 * This function is used to ask the user what he wants to create in the company.
 */
bool create();
/**
 * This function is used to ask the user what information about the company he wants to read.
 */
bool read();
/**
 * This function is used to ask the user what he wants update in the company.
 */
bool update();
/**
 * This function is used to ask the user in which way he wants to search for the company's information.
 */
bool search();
/**
 * This function is used to ask the user what he wants to delete in the company.
 */
bool obj_delete();
/**
 * This function is used to exit the interface or any of it's dedicated menus.
 */
bool exit(bool full_exit);
/**
 * This function is used to save all objects to files.
 */
bool saveFile();


#endif //PETWALKERPROJAEDA_INTERFACE_H
