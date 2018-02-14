//Bryant Wong
//CSCI2421 final project
#include "AddressBook.h"

#ifndef MENU_
#define MENU_

//contains functions that run menu functions in class AddressBook
void runMenu(AddressBook& book);		//declaration for the menu that calls all of the other menu functions
void addEntry(AddressBook& book);		
void editEntry(AddressBook& book);
void deleteEntry(AddressBook& book);
std::vector<Node*> searchEntry(AddressBook& book);			//returns a vector of Node* that match the search criteria
void readFile(AddressBook& book);			
void viewEntries(AddressBook& book);
void writeFile(AddressBook& book);
std::vector<Node*> sortEntries(AddressBook& book, vector<Node*>sortList);
#endif