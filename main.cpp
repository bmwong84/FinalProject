//Bryant Wong
//CSCI 2421 Final Project
#include "BST.h"
#include "Menu.h"
#include "AddressBook.h"

int main()
{
	//BST BSTBook;				//instantiates the BST address book
	AddressBook addressBook;	//creates an instance of class AddressBook	
	runMenu(addressBook);		//runs the main menu, all other functions are handled by the menu function
	return 0;
}