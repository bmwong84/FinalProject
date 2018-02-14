//Bryant Wong
//CSCI 2421 Final Project

#include "Menu.h"
#include <algorithm>	// to use str.erase
#include "BST.h"
#include "AddressBook.h"
#include "Entry.h"
#include <cstring> //for strlen


// to check isinteger from stack overflow, modified to accept my parameters
//http://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
//called to check if ID is an integer or not
inline bool isInteger(const std::string& string)
{
	if (string.empty() || ((!isdigit(string[0])) && (string[0] != '-') && (string[0] != '+')))		//if the string is NOT a digit and it's not - and + or it's empty, return false
		return false;
	char *charPtr;
	strtol(string.c_str(), &charPtr, 10);	//converts a string to a long in base 10
	return(*charPtr == 0);
}

void runMenu(AddressBook& book)		//runs the menu to call the other menu functions
{
	readFile(book);
	char menuchoice = '0';
	while (menuchoice != '6')
	{
		std::cout << "Welcome to your address book, please choose an action" << std::endl;
		std::cout << "1. Add an entry." << std::endl;
		std::cout << "2. Edit an entry." << std::endl;
		std::cout << "3. Delete an entry." << std::endl;
		std::cout << "4. Search and view an entry." << std::endl;
		std::cout << "5. Select entries to write to file." << std::endl;
		std::cout << "6. Exit" << std::endl;
		std::cin >> menuchoice;
		switch (menuchoice)
		{
		case '1':
		{
			addEntry(book);		//self explanatory
			break;
		}
		case'2':
		{
			if (book.getBSTBook().Root() == nullptr)		//if the root is nullptr, don't run anything because addressbook is empty
			{
				std::cout << "Address book is empty!" << std::endl;
				break;
			}
			editEntry(book);
			break;
		}
		case'3':
		{
			if (book.getBSTBook().Root()==nullptr)
			{
				std::cout << "Address book is empty!" << std::endl;
				break;
			}
			deleteEntry(book);
			break;
		}
		case '4':
		{
			if (book.getBSTBook().Root() == nullptr)
			{
				std::cout << "Address book is empty!" << std::endl;
				break;
			}
			searchEntry(book);
			break;
		}
		case'5':
		{
			if (book.getBSTBook().Root() == nullptr)
			{
				std::cout << "Address book is empty!" << std::endl;
				break;
			}
			writeFile(book);
			break;
		}
		case '6':
		{
			break;
		}
		default:
			std::cout << "Invalid choice, please enter a valid choice" << std::endl;
		}

	}//end main menu
	
}

void viewEntries(AddressBook& book)
{

}




inline bool checkPhoneNumber(std::string number)
{
	//char ignoreChars[] = "()-";		//array of characters to be ignored includes ()-
	//for (int count = 0; count < std::strlen(ignoreChars); count++)
	//{
	//	number.erase(std::remove(number.begin(), number.end(), ignoreChars[count]));	//for each character, erase those characters
	//}
	//std::string test = number;
	//test.erase(std::remove(test.begin(), test.end(), ')'));
	//std::string number2 = test;
	//number2.erase(std::remove(number2.begin(), number2.end(), '('));
	//std::string number3 = number2;
	//number3.erase(std::remove(number3.begin(), number3.end(), '-'));
	//std::string number4 = number3;
	if (number.size() != 10 || !isInteger(number))	//if temp is not a number or 10 digits...
		return false;
	else
		return true;		//if the entry is okay, return true
}

void addEntry(AddressBook& book)
{
	//temp variables to hold what's inputted
	std::string tId, tFirstName, tMiddleName, tLastName, tCompany, tHomePhone, tOfficePhone, tMobilePhone, tEmail, tStreetAddress, tCity, tState, tZip, tCountry, tAffiliateLine, tAffiliateFirstName, tAffiliateLastName, tAffiliateMobileNumber, tAffiliateEmail;
	int numAffiliates;		//number of affiliates
	Entry* tempEntry;		//pointer to class to hold the data
	std::cout << "Please enter a unique 9-digit identification number" << std::endl;
	std::getline(std::cin >> std::ws, tId);			//user input for ID
	while (book.getBSTBook().checkId(tId, book.getBSTBook().Root()) == false || tId.size()!=9 || !isInteger(tId))		//checks if user input is 9 digits, is an integer, and if it's used or not yet
	{
		std::cout << "Invalid entry, please enter a unique 9-digit identification number" << std::endl;			//if any of these are not true, asks for input again
		std::getline(std::cin>>ws, tId);
	}
	if (book.getBSTBook().checkId(tId, book.getBSTBook().Root()))			//i guess this is checking to see if the ID is in use or not again, I could just remove this line, but hey double checking
	{
		tempEntry = new Entry();			//creats a new instance of class Entry
		tempEntry->setId(tId);				
		std::cout << "Please enter the entry's first name" << std::endl;			//user input for each field
		std::getline(std::cin >> ws, tFirstName);
		tempEntry->setFirstName(tFirstName);
		std::cout << "Please enter the entry's middle name (or initial)" << std::endl;
		std::getline(std::cin >> ws, tMiddleName);
		tempEntry->setMiddleName(tMiddleName);
		std::cout << "Please enter the entry's last name" << std::endl;
		std::getline(std::cin >> ws, tLastName);
		tempEntry->setLastName(tLastName);
		std::cout << "Please enter the entry's company" << std::endl;
		std::getline(std::cin >> ws, tCompany);
		tempEntry->setCompany(tCompany);
		//code to erase certain characters using str.erase from stackoverflow
		//http://stackoverflow.com/questions/5891610/how-to-remove-certain-characters-from-a-string-in-c
		//in the inline bool checkphonenumber
		std::cout << "Please enter the entry's home phone number" << std::endl;
		std::getline(std::cin >> ws, tHomePhone);
		while(!checkPhoneNumber(tHomePhone))		//while the check returns false
		{
			std::cout << "Invalid entry.  Please enter a 10 digit phone number" << std::endl;
			std::getline(std::cin >> ws, tHomePhone);		//re-enter the number
		}
		tempEntry->getContactInfo().setHomePhone(tHomePhone);
		std::cout << "Please enter the entry's office phone number" << std::endl;
		std::getline(std::cin >> ws, tOfficePhone);
		while (!checkPhoneNumber(tOfficePhone))
		{
			std::cout << "Invalid entry.  Please enter a 10 digit phone number" << std::endl;
			std::getline(std::cin >> ws, tOfficePhone);
		}
		tempEntry->getContactInfo().setOfficePhone(tOfficePhone);
		std::cout << "Please enter the entry's e-mail address" << std::endl;
		std::getline(std::cin >> ws, tEmail);
		while (!(tEmail.find("@") != std::string::npos) || !(tEmail.find(".") != std::string::npos))
		{
			std::cout << "Invalid e-mail address.  E-mail address must contain '@' and '.'" << std::endl;
			std::cout << "Please enter the entry's e-mail address" << std::endl;
			std::getline(std::cin >> ws, tEmail);
		}
		tempEntry->getContactInfo().setEMail(tEmail);
		std::cout << "Please enter the entry's mobile phone number" << std::endl;
		std::getline(std::cin >> ws, tMobilePhone);
		while (!checkPhoneNumber(tMobilePhone))
		{
			std::cout << "Invalid entry.  Please enter a 10 digit phone number" << std::endl;
			std::getline(std::cin >> ws, tMobilePhone);
		}
		tempEntry->getContactInfo().setMobilePhone(tMobilePhone);
		std::cout << "Please enter the entry's street address" << std::endl;
		std::getline(std::cin >> ws, tStreetAddress);
		tempEntry->getContactInfo().setStreetAddress(tStreetAddress);
		std::cout << "Please enter the entry's city" << std::endl;
		std::getline(std::cin >> ws, tCity);
		tempEntry->getContactInfo().setCity(tCity);
		std::cout << "Please enter the entry's state" << std::endl;
		std::getline(std::cin >> ws, tState);
		tempEntry->getContactInfo().setState(tState);
		std::cout << "Please enter the entry's zip" << std::endl;
		std::getline(std::cin >> ws, tZip);
		tempEntry->getContactInfo().setZip(tZip);
		std::cout << "Please enter the entry's country" << std::endl;
		std::getline(std::cin >> ws, tCountry);
		tempEntry->getContactInfo().setCountry(tCountry);
		std::cout << "How many affiliates does this person have?" << std::endl;		//number of affiliates
		std::cin >> numAffiliates;
		//code to check if an entry is an integer from stackoverflow
		//http://stackoverflow.com/questions/18728754/checking-input-value-is-an-integer
		while (std::cin.fail())
		{
			std::cout << "Invalid entry.  Please Enter a number" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> numAffiliates;
		}
		//i believe this is the same as std::cin.fail()
		//while (!(std::cin >> numAffiliates))
		//{
		//	std::cout << "Invalid entry.  Please enter an integer: " << std::endl;
		//	std::cin.clear();
		//}
		for (int count = 0; count < numAffiliates; count++)				//loop to populate each affiliate's info
		{
			Affiliates tAffiliates;
			std::cout << "Please enter affiliate " << count + 1 << "'s first name" << std::endl;
			std::getline(std::cin >> ws, tAffiliateFirstName);
			tAffiliates.setAffiliateFirstName(tAffiliateFirstName);
			std::cout << "Please enter affiliate " << count + 1 << "'s last name" << std::endl;
			std::getline(std::cin >> ws, tAffiliateLastName);
			tAffiliates.setAffiliateLastName(tAffiliateLastName);
			std::cout << "Please enter affiliate " << count + 1 << "'s mobile number" << std::endl;
			std::getline(std::cin >> ws, tAffiliateMobileNumber);
			while (!checkPhoneNumber(tAffiliateMobileNumber))
			{
				std::cout << "Invalid entry.  Please enter a 10 digit phone number" << std::endl;
				std::getline(std::cin >> ws, tAffiliateMobileNumber);
			}
			tAffiliates.setAffiliateMobileNumber(tAffiliateMobileNumber);
			std::cout << "Please enter affiliate " << count + 1 << "'s e-mail address" << std::endl;
			std::getline(std::cin >> ws, tAffiliateEmail);
			while (!(tAffiliateEmail.find("@") != std::string::npos) || !(tAffiliateEmail.find(".") != std::string::npos))
			{
				std::cout << "Invalid e-mail address.  E-mail address must contain '@' and '.'" << std::endl;
				std::cout << "Please enter the entry's e-mail address" << std::endl;
				std::getline(std::cin >> ws, tAffiliateEmail);
			}
			tAffiliates.setAffiliateEMail(tAffiliateEmail);
			tempEntry->getAffiliates().push_back(tAffiliates);
		}
		book.addEntry(tempEntry);			//sends the entry to the book to be added to the tree
		std::cout << "Entry added" << std::endl;
	}
	
}
void deleteEntry(AddressBook& book)
{
	vector<Node*> temp;
	std::cout << "Search for an entry to delete" << std::endl;
	temp = searchEntry(book);		//sets vector of nodes temp to what the search function returns
	if (temp.size() > 0)			//if the vector has nodes in it
	{
		std::cout << "Select an entry to delete (1 - " << temp.size() << ")" << std::endl;		//select one to delete
		int select = -1;
		while (std::cin.fail())			//if it's not a number
		{
			std::cout << "Invalid entry.  Please Enter a number" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> select;			//enter a number!
		}
		while (select < 1 || select>temp.size())			//while out of bounds
		{
			std::cin >> select;
			while (std::cin.fail())			//if it's not a number
			{
				std::cout << "Invalid entry.  Please Enter a number" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> select;			//enter a number!
			}
			if (select < 1 || select>temp.size())
			{
				std::cout << "Invalid choice, please slect an entry to delete (1 - "  << temp.size() <<  ")" << std::endl;		//choose something in bounds!
			}
		}
		std::cout << "You are choosing to delete: " << std::endl;
		book.displayEntry(temp[select-1]);		//you are choosing to delete this guy!
		std::cout << "Is this correct? (y/n)" << std::endl;
		char correct;
		std::cin >> correct;
		while (correct != 'y' && correct != 'Y' && correct != 'n'&& correct != 'N')
		{
			std::cout << "Invalid entry, please indicate if this entry is the one you wish to delete (y to delete, n to not delete)" << std::endl;
			std::cin >> correct;
		}
		if (correct == 'y' || correct == 'Y')
			book.deleteEntry(temp[select-1]);		//calls delete function in addressbook 
		else if (correct == 'n' || correct == 'N')
		{
			std::cout << "Entry not deleted, returning to main menu" << std::endl;
		}
	}
}

void editEntry(AddressBook& book)
{
	vector<Node*> temp;
	std::cout << "Search for an entry to edit" << std::endl;
	temp = searchEntry(book);
	if (temp.size() > 0)
	{
		std::cout << "Select an entry to edit (1 - " << temp.size() << ")"<< std::endl;
		int select = -1;
		while (select < 1 || select>temp.size())		//while out of bounds
		{
			std::cin >> select;
			while (std::cin.fail())			//if it's not a number
			{
				std::cout << "Invalid entry.  Please Enter a number" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> select;			//enter a number!
			}
			if (select < 1 || select>temp.size())		//if not a number
			{
				std::cout << "Invalid choice, please select an entry to edit (1 - " <<")"<< temp.size() << std::endl;
			}
		}

		int menuchoice = 0;
		while (menuchoice != 19)
		{
			std::cout << "You selected the following entry: " << std::endl;
			book.displayEntry(temp[select-1]);
			std::cout << "Please enter the field you wish to edit " << std::endl;
			std::cout << "1. Entry's ID number" << std::endl;
			std::cout << "2. Entry's first name" << std::endl;
			std::cout << "3. Entry's middle name (or initial)" << std::endl;
			std::cout << "4. Entry's last name" << std::endl;
			std::cout << "5. Entry's company" << std::endl;
			std::cout << "6. Entry's home phone number" << std::endl;
			std::cout << "7. Entry's office phone number" << std::endl;
			std::cout << "8. Entry's e-mail address" << std::endl;
			std::cout << "9. Entry's mobile phone number" << std::endl;
			std::cout << "10. Entry's street address" << std::endl;
			std::cout << "11. Entry's city" << std::endl;
			std::cout << "12. Entry's state" << std::endl;
			std::cout << "13. Entry's zip" << std::endl;
			std::cout << "14. Entry's country" << std::endl;
			std::cout << "15. Entry's affiliate's first name" << std::endl;
			std::cout << "16. Entry's affiliate's last name" << std::endl;
			std::cout << "17. Entry's affiliate's mobile number" << std::endl;
			std::cout << "18. Entry's affiliate's e-mail" << std::endl;
			std::cin >> menuchoice;
			while (std::cin.fail())			//if it's not a number
			{
				std::cout << "Invalid entry.  Please Enter a number" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> menuchoice;			//enter a number!
			}
			if (menuchoice < 1 || menuchoice >18)
			{
				std::cout << "Invalid choice " << std::endl;
			}
			else
			{
				book.editEntry(menuchoice, temp[select-1]);		//calls editEntry in address book
				break;
			}
		}
	}
	else
	{
		std::cout << "No entries selected to edit.  Returning to main menu" << std::endl;
	}
}



vector<Node*> searchEntry(AddressBook& book)
{
	int menuchoice = 0;
	while (menuchoice != 19)
	{
		std::cout << "Please enter the field with which you wish to search for the entry " << std::endl;
		std::cout << "1. Entry's ID number" << std::endl;
		std::cout << "2. Entry's first name" << std::endl;
		std::cout << "3. Entry's middle name (or initial)" << std::endl;
		std::cout << "4. Entry's last name" << std::endl;
		std::cout << "5. Entry's company" << std::endl;
		std::cout << "6. Entry's home phone number" << std::endl;
		std::cout << "7. Entry's office phone number" << std::endl;
		std::cout << "8. Entry's e-mail address" << std::endl;
		std::cout << "9. Entry's mobile phone number" << std::endl;
		std::cout << "10. Entry's street address" << std::endl;
		std::cout << "11. Entry's city" << std::endl;
		std::cout << "12. Entry's state" << std::endl;
		std::cout << "13. Entry's zip" << std::endl;
		std::cout << "14. Entry's country" << std::endl;
		std::cout << "15. Entry's affiliate's first name" << std::endl;
		std::cout << "16. Entry's affiliate's last name" << std::endl;
		std::cout << "17. Entry's affiliate's mobile number" << std::endl;
		std::cout << "18. Entry's affiliate's e-mail" << std::endl;
		//std::cout << "19. Exit" << std::endl;
		std::cin >> menuchoice;
		while (std::cin.fail())			//if not a number
		{
			std::cout << "Invalid entry.  Please Enter a number" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> menuchoice;
		}
		if (menuchoice < 19 && menuchoice >0)
		{
			int choice2 = 0;			//second choice
			std::string temp;
			while (std::cin.fail())
			{
				std::cout << "Invalid entry.  Please Enter a number" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> choice2;
			}
			while (choice2 != 3)
			{
				std::cout << "Would you like to perform an 'exact' search or a 'contains' search?" << std::endl;		//self explanatory
				std::cout << "1. Exact search" << std::endl;
				std::cout << "2. Contains search" << std::endl;
				std::cout << "3. Return to 'select field to search by' menu" << std::endl;
				std::cin >> choice2;
				switch (choice2)
				{
				case 1:
				{
					std::cout << "Enter the exact text or number you wish to search for: ";
					std::cin >> temp;
					return book.searchEntry(menuchoice, temp, false);		//calls search function passing false for "contains"
					break;
				}
				case 2:
				{
					std::cout << "Enter the text or number that is contained in the entry you wish to search for: ";
					std::cin >> temp;
					return book.searchEntry(menuchoice, temp, true);		//calls search function with "contains"
					break;
				}
				default:
				{
					std::cout << "Invalid choice" << std::endl;
				}
				}
			}
		}
		//else if (menuchoice == 19)
		//{
		//	std::vector <Node*> temp;
		//	return temp;	//needs to return something, empty vector?
		//}
		else
		{
			std::cout << "Invalid Entry" << std::endl;
		}
	}
}

void readFile(AddressBook& book)
{
	//add choose to read large database or small database
	int menuchoice = 0;
	while (menuchoice != 1 && menuchoice != 2)
	{
		std::cout << "Would you like to read the large address book or the small address book?" << std::endl;		//read the small file or large file
		std::cout << "1.  Large address book" << std::endl;
		std::cout << "2.  Small address book" << std::endl;
		std::cin >> menuchoice;
		while (std::cin.fail())
		{
			std::cout << "Invalid entry, please hit 1 for large address book or 2 for small address book" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> menuchoice;
		}
		if (menuchoice == 2)
		{
			std::cout << "Reading databasesmall.txt" << std::endl;		
			ifstream instream("databasesmall.txt");
			book.readFile(instream, book);		//calls addressbook member function read file
			instream.close();
		}
		else if (menuchoice == 1)
		{
			std::cout << "Reading databaselarge.txt" << std::endl;
			ifstream instream("databaselarge.txt");
			book.readFile(instream, book);
			instream.close();
		}
		else
			std::cout << "Invalid entry." << std::endl;
	}
};

void writeFile(AddressBook& book)			//oh god the menus
{
	char keepChoosing = 'y';
	vector<Node*> temp;				//makes a temp vector full of poitners...
	vector<Node*> writeList;			//makes a vector full of pointers to be written
	while (keepChoosing != 'n' && keepChoosing != 'N')			//menu loop to see if they wish to keep searching for entries
	{
		std::cout << "Search for an entry you wish to write to file" << std::endl;
		temp = searchEntry(book);			//these are the files that are to be written to file chosen by the user in the search function
		if (temp.size() > 0)
		{
			char selectAgain = 'y';
			while (selectAgain == 'y' || selectAgain == 'Y')			//menu loop to check if they want to add another entry from the returned search list
			{
				std::cout << "Select an entry you wish to write to file (1 - " << temp.size() << ")" << std::endl;
				int select = -1;
				while (std::cin.fail())
				{
					std::cout << "Invalid entry.  Please Enter a number" << std::endl;
					std::cin.clear();
					std::cin.ignore(256, '\n');
					std::cin >> select;
				}
				while (select < 1 || select>temp.size())		//menu loop to select an entry
				{
					std::cin >> select;
					if (select < 1 || select>temp.size())
					{
						std::cout << "Invalid choice, please select an entry you wish to write to file (1 - " << temp.size() << ")" << std::endl;
					}
				}
				std::cout << "You are choosing to write the following entry to file: " << std::endl;
				book.displayEntry(temp[select - 1]);			//displays the entry that they chose
				std::cout << "Is this correct? (y/n)" << std::endl;
				char correct;
				std::cin >> correct;
				while (correct != 'y' && correct != 'Y' && correct != 'n'&& correct != 'N')
				{
					std::cout << "Invalid entry, please indicate if this entry is the one you wish to write to file (y/n)" << std::endl;
					std::cin >> correct;
				}
				if (correct == 'y' || correct == 'Y')
				{
					std::cout << "Entry added to list to write to file" << std::endl;
					writeList.push_back(temp[select - 1]);
					std::cout << "Would you like to select another entry from this list?" << std::endl;				//do we want to loop and choose another entry from this file?
					std::cin >> selectAgain;
					while (selectAgain != 'y' && selectAgain != 'Y' && selectAgain != 'n'&& selectAgain != 'N')
					{
						std::cout << "Invalid entry, would you like to select another entry from this list?" << std::endl;
						std::cin >> selectAgain;
					}
					if (selectAgain == 'y' || selectAgain == 'Y')
					{
						continue;			//if yes, skip the rest of the loop that calls the search function and select another from this list
					}
					else if (selectAgain == 'n' || selectAgain == 'N')
					{
						break;		//if not, break out of this loop and ask if they want to search for more entries to write to file
					}
					
				}
				else if (correct == 'n' || correct == 'N')
				{
					std::cout << "Entry not selected" << std::endl;
					std::cout << "Would you like to search for another entry to write to file?" << std::endl;
					char again;
					std::cin >> again;
					while (again != 'y' && again != 'Y' && again != 'n'&& again != 'N')
					{
						std::cout << "Invalid entry, please indicate if this entry is the one you wish to write to file (y/n)" << std::endl;
						std::cin >> again;
					}
					//keepChoosing = again;
				}
			}
			std::cout << "Would you like to search for another entry to write to file?" << std::endl;
			char again;
			std::cin >> again;
			while (again != 'y' && again != 'Y' && again != 'n'&& again != 'N')
			{
				std::cout << "Invalid entry, please indicate if you would like to search for another entry to write to file (y/n)" << std::endl;
				std::cin >> again;
			}
			keepChoosing = again;
		}
	}
	std::cout << "You selected " << writeList.size() << " entries to write to file." << std::endl;			//after all that crap is done, you have this many entries hooray
	std::cout << "Would you like to sort your entries before writing to file? (y/n)" << std::endl;
	char firstSort = '0';
	std::cin >> firstSort;
	while (firstSort != 'y' && firstSort != 'Y' && firstSort != 'n'&& firstSort != 'N')				//uwanna sort?
	{
		std::cout << "Invalid entry, would you like to sort your entries before writing to file (y/n)?" << std::endl;
		std::cin >> firstSort;
	}
	if (firstSort == 'y' || firstSort == 'Y')
	{
		std::vector <Node*> tempVect;
		tempVect = sortEntries(book, writeList);		//calls menu member function sort where it asks if user wants to sort by 1 field or by 2 fields with secondary sort
		writeList = tempVect;							//the list to be written is now the sorted list
	}

	int writeFields = 0;
	bool Id = false, firstName = false, middleName = false, lastName = false, company = false, homePhone = false, officePhone = false;		//bools to select which fields they want to write
	bool eMail = false, mobilePhone = false, streetAddress = false, city = false, state = false, zip = false, country = false;
	bool affiliateFirstName = false, affiliateLastName = false, affiliateMobile = false, affiliateEmail = false;
	while (writeFields != 20)			
	{
		std::cout << "Please select the fields you wish to write to file: " << std::endl;
		std::cout << "1. Entry's ID number" << std::endl;
		std::cout << "2. Entry's first name" << std::endl;
		std::cout << "3. Entry's middle name (or initial)" << std::endl;
		std::cout << "4. Entry's last name" << std::endl;
		std::cout << "5. Entry's company" << std::endl;
		std::cout << "6. Entry's home phone number" << std::endl;
		std::cout << "7. Entry's office phone number" << std::endl;
		std::cout << "8. Entry's e-mail address" << std::endl;
		std::cout << "9. Entry's mobile phone number" << std::endl;
		std::cout << "10. Entry's street address" << std::endl;
		std::cout << "11. Entry's city" << std::endl;
		std::cout << "12. Entry's state" << std::endl;
		std::cout << "13. Entry's zip" << std::endl;
		std::cout << "14. Entry's country" << std::endl;
		std::cout << "15. Entry's affiliate's first name" << std::endl;
		std::cout << "16. Entry's affiliate's last name" << std::endl;
		std::cout << "17. Entry's affiliate's mobile number" << std::endl;
		std::cout << "18. Entry's affiliate's e-mail" << std::endl;
		std::cout << "19. Select all fields" << std::endl;
		std::cout << "20. Finished choosing fields" << std::endl;
		std::cin >> writeFields;
		while (std::cin.fail())
		{
			std::cout << "Invalid entry.  Please Enter a number" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> writeFields;
		}
		if (writeFields < 20 && writeFields > 0)		//if in bounds
		{
			if (writeFields == 1)		//if selected...set bool to true for fields
				Id = true;
			if (writeFields == 2)
				firstName = true;
			if (writeFields == 3)
				middleName = true;
			if (writeFields == 4)
				lastName = true;
			if (writeFields == 5)
				company = true;
			if (writeFields == 6)
				homePhone = true;
			if (writeFields == 7)
				officePhone = true;
			if (writeFields == 8)
				eMail = true;
			if (writeFields == 9)
				mobilePhone = true;
			if (writeFields == 10)
				streetAddress = true;
			if (writeFields == 11)
				city = true;
			if (writeFields == 12)
				state = true;
			if (writeFields == 13)
				zip = true;
			if (writeFields == 14)
				country = true;
			if (writeFields == 15)
				affiliateFirstName = true;
			if (writeFields == 16)
				affiliateLastName = true;
			if (writeFields == 17)
				affiliateMobile = true;
			if (writeFields == 18)
				affiliateEmail = true;
			if (writeFields == 19)		//FOR ALL FIELDS
			{
				Id = true; firstName = true; middleName = true; lastName = true; company = true; homePhone = true; officePhone = true;
				eMail = true; mobilePhone = true; streetAddress = true; city = true; state = true; zip = true; country = true;
				affiliateFirstName = true; affiliateLastName = true; affiliateMobile = true; affiliateEmail = true;
				std::cout << "All fields selected" << std::endl;
				break;
			}
			else if (writeFields == 20)
			{
				break;
			}
			else
			{
				std::cout << "Invalid Entry" << std::endl;
				continue;
			}
			std::cout << "You have chosen the following fields to write to file: " << std::endl;			//once chose, list the ones they chose
			if (Id)
				std::cout << "ID " << std::endl;
			if (firstName)
				std::cout << "first name " << std::endl;
			if (middleName)
				std::cout << "middle name " << std::endl;
			if (lastName)
				std::cout << "last name " << std::endl;
			if (company)
				std::cout << "company " << std::endl;
			if (homePhone)
				std::cout << "home phone " << std::endl;
			if (officePhone)
				std::cout << "office phone " << std::endl;
			if (eMail)
				std::cout << "e-mail address " << std::endl;
			if (mobilePhone)
				std::cout << "mobile phone " << std::endl;
			if (streetAddress)
				std::cout << "street address " << std::endl;
			if (city)
				std::cout << "city " << std::endl;
			if (state)
				std::cout << "state " << std::endl;
			if (zip)
				std::cout << "zip code " << std::endl;
			if (country)
				std::cout << "country " << std::endl;
			if (affiliateFirstName)
				std::cout << "affiliate's first name " << std::endl;
			if (affiliateLastName)
				std::cout << "affiliate last name " << std::endl;
			if (affiliateMobile)
				std::cout << "affiliate mobile number" << std::endl;
			if (affiliateEmail)
				std::cout << "affiliate e-mail address " << std::endl;
			std::cout << std::endl;
		}
	}
	std::cout << "Would you like to view what you are writing to file?" << std::endl;		//uwanna see what you're writing or nah?
	char viewWrite;
	std::cin >> viewWrite;
	while (viewWrite != 'y' && viewWrite != 'Y' && viewWrite != 'n'&& viewWrite != 'N')
	{
		std::cout << "Invalid entry, would you like to view what you are writing to file?" << std::endl;
		std::cin >> viewWrite;
	}
	if (viewWrite == 'y' || viewWrite == 'Y')
	{
		for (int count = 0; count < writeList.size(); count++)
		{
			if (Id)
				std::cout << writeList[count]->getEntry()->getId() << std::endl;			//if they chose it, cout it
			if (firstName)			
				std::cout << writeList[count]->getEntry()->getFirstName() << std::endl;
			if (middleName)
				std::cout << writeList[count]->getEntry()->getMiddleName() << std::endl;
			if (lastName)
				std::cout << writeList[count]->getEntry()->getLastName() << std::endl;
			if (company)
				std::cout << writeList[count]->getEntry()->getCompany() << std::endl;
			if (homePhone)
				std::cout << writeList[count]->getEntry()->getContactInfo().getHomePhone() << std::endl;
			if (officePhone)
				std::cout << writeList[count]->getEntry()->getContactInfo().getOfficePhone() << std::endl;
			if (eMail)
				std::cout << writeList[count]->getEntry()->getContactInfo().getEMail() << std::endl;
			if (mobilePhone)
				std::cout << writeList[count]->getEntry()->getContactInfo().getMobilePhone() << std::endl;
			if (streetAddress)
				std::cout << writeList[count]->getEntry()->getContactInfo().getStreetAddress() << std::endl;
			if (city)
				std::cout << writeList[count]->getEntry()->getContactInfo().getCity() << std::endl;
			if (state)
				std::cout << writeList[count]->getEntry()->getContactInfo().getState() << std::endl;
			if (zip)
				std::cout << writeList[count]->getEntry()->getContactInfo().getZip() << std::endl;
			if (country)
				std::cout << writeList[count]->getEntry()->getContactInfo().getCountry() << std::endl;
			for (int aff = 0; aff < writeList[count]->getEntry()->getAffiliates().size(); aff++)
			{
				if (affiliateFirstName)
					std::cout << writeList[count]->getEntry()->getAffiliates()[aff].getAffiliateFirstName() << " ";
				if (affiliateLastName)
					std::cout << writeList[count]->getEntry()->getAffiliates()[aff].getAffiliateLastName() << ", ";
				if (affiliateMobile)
					std::cout << writeList[count]->getEntry()->getAffiliates()[aff].getAffiliateMobileNumber() << ", " ;
				if (affiliateEmail)
					std::cout << writeList[count]->getEntry()->getAffiliates()[aff].getAffiliateEMail();
				std::cout << std::endl;
			}
			std::cout << "|" << std::endl;
		}
	}

	std::ofstream outstream;			//open an outstream
	std::string fileName;
	std::cout << "Enter the name of the output file: " << std::endl;
	std::getline(std::cin >> ws, fileName);			//enter the file name they want to write
	fileName = fileName + ".txt";			//append .txt to it to make it a text document
	outstream.open(fileName.c_str());			//create the outstream with the file name they typed in.txt
	for (int count = 0; count < writeList.size(); count++)
	{
		if (Id)
			outstream << writeList[count]->getEntry()->getId() << std::endl;			//if they chose it, write it to file
		if (firstName)
			outstream << writeList[count]->getEntry()->getFirstName() << std::endl;
		if (middleName)
			outstream << writeList[count]->getEntry()->getMiddleName() << std::endl;
		if (lastName)
			outstream << writeList[count]->getEntry()->getLastName() << std::endl;
		if (company)
			outstream << writeList[count]->getEntry()->getCompany() << std::endl;
		if (homePhone)
			outstream << writeList[count]->getEntry()->getContactInfo().getHomePhone() << std::endl;
		if (officePhone)
			outstream << writeList[count]->getEntry()->getContactInfo().getOfficePhone() << std::endl;
		if (eMail)
			outstream << writeList[count]->getEntry()->getContactInfo().getEMail() << std::endl;
		if (mobilePhone)
			outstream << writeList[count]->getEntry()->getContactInfo().getMobilePhone() << std::endl;
		if (streetAddress)
			outstream << writeList[count]->getEntry()->getContactInfo().getStreetAddress() << std::endl;
		if (city)
			outstream << writeList[count]->getEntry()->getContactInfo().getCity() << std::endl;
		if (state)
			outstream << writeList[count]->getEntry()->getContactInfo().getState() << std::endl;
		if (zip)
			outstream << writeList[count]->getEntry()->getContactInfo().getZip() << std::endl;
		if (country)
			outstream << writeList[count]->getEntry()->getContactInfo().getCountry() << std::endl;
		for (int aff = 0; aff < writeList[count]->getEntry()->getAffiliates().size(); aff++)
		{
			if (affiliateFirstName)
				outstream << writeList[count]->getEntry()->getAffiliates()[aff].getAffiliateFirstName() << " ,";
			if (affiliateLastName)
				outstream << writeList[count]->getEntry()->getAffiliates()[aff].getAffiliateLastName() << " ,";
			if (affiliateMobile)
				outstream << writeList[count]->getEntry()->getAffiliates()[aff].getAffiliateMobileNumber()<< " ,";
			if (affiliateEmail)
				outstream << writeList[count]->getEntry()->getAffiliates()[aff].getAffiliateEMail() << " ;";
			outstream << std::endl;
		}//end affiliate for loop
		outstream << "|" << std::endl;
	}

	std::cout << "Writing to file" << std::endl;
	outstream.close();
}

vector<Node*> sortEntries(AddressBook& book, vector<Node*> sortList)
{
	int sortBy;
	std::cout << "Would you like to sort by one field or sort by first one field, then a second field?" << std::endl;	
	std::cout << "1.  Sort by 1 field only" << std::endl;
	std::cout << "2.  Sort by one field, then a second field" << std::endl;
	std::cin >> sortBy;
	while (std::cin.fail())
	{
		std::cout << "Invalid entry.  Please enter 1 to sort by 1 field only, or 2 to sort first by one field, then a second field" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> sortBy;
	}
	if (sortBy == 1)
	{
		int menuchoice = 0;
		vector<Node*> temp = sortList;					//the list is what was passed here
		vector<Node*> firstSorted;
		while (menuchoice < 1 || menuchoice>18)			//menu loop to choose field to sort by first time
		{
			std::cout << "Please enter the field to sort by: " << std::endl;
			std::cout << "1. Entry's ID number" << std::endl;
			std::cout << "2. Entry's first name" << std::endl;
			std::cout << "3. Entry's middle name (or initial)" << std::endl;
			std::cout << "4. Entry's last name" << std::endl;
			std::cout << "5. Entry's company" << std::endl;
			std::cout << "6. Entry's home phone number" << std::endl;
			std::cout << "7. Entry's office phone number" << std::endl;
			std::cout << "8. Entry's e-mail address" << std::endl;
			std::cout << "9. Entry's mobile phone number" << std::endl;
			std::cout << "10. Entry's street address" << std::endl;
			std::cout << "11. Entry's city" << std::endl;
			std::cout << "12. Entry's state" << std::endl;
			std::cout << "13. Entry's zip" << std::endl;
			std::cout << "14. Entry's country" << std::endl;
			std::cout << "15. Entry's affiliate's first name" << std::endl;
			std::cout << "16. Entry's affiliate's last name" << std::endl;
			std::cout << "17. Entry's affiliate's mobile number" << std::endl;
			std::cout << "18. Entry's affiliate's e-mail" << std::endl;
			std::cin >> menuchoice;
			while (std::cin.fail())
			{
				std::cout << "Invalid entry.  Please Enter a number" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> menuchoice;
			}
			if (menuchoice < 19 && menuchoice > 0)
			{
				firstSorted = book.sortEntries(menuchoice, temp, false);			//sorts using overloaded addressbook member function, with secondary sort not active
				return firstSorted;
			}
			else
			{
				std::cout << "Invalid Entry" << std::endl;
			}
		}
	}
	if (sortBy == 2)
	{
		vector<Node*> temp = sortList;
		vector<Node*> secondSorted;
		int menuchoice = 0;
		while (menuchoice < 1 || menuchoice>14)			//choose first sort
		{
			std::cout << "Please enter the first field to sort by: " << std::endl;
			std::cout << "1. Entry's ID number" << std::endl;
			std::cout << "2. Entry's first name" << std::endl;
			std::cout << "3. Entry's middle name (or initial)" << std::endl;
			std::cout << "4. Entry's last name" << std::endl;
			std::cout << "5. Entry's company" << std::endl;
			std::cout << "6. Entry's home phone number" << std::endl;
			std::cout << "7. Entry's office phone number" << std::endl;
			std::cout << "8. Entry's e-mail address" << std::endl;
			std::cout << "9. Entry's mobile phone number" << std::endl;
			std::cout << "10. Entry's street address" << std::endl;
			std::cout << "11. Entry's city" << std::endl;
			std::cout << "12. Entry's state" << std::endl;
			std::cout << "13. Entry's zip" << std::endl;
			std::cout << "14. Entry's country" << std::endl;
			std::cin >> menuchoice;
			while (std::cin.fail())
			{
				std::cout << "Invalid entry.  Please Enter a number" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> menuchoice;
			}
			if (menuchoice < 15 && menuchoice > 0)
			{
				int menuchoice2 = 0;
				while (menuchoice2 < 1 || menuchoice2>14)			//choose second field for secondary sort
				{
					std::cout << "Please enter the second field to sort by: " << std::endl;
					std::cout << "1. Entry's ID number" << std::endl;
					std::cout << "2. Entry's first name" << std::endl;
					std::cout << "3. Entry's middle name (or initial)" << std::endl;
					std::cout << "4. Entry's last name" << std::endl;
					std::cout << "5. Entry's company" << std::endl;
					std::cout << "6. Entry's home phone number" << std::endl;
					std::cout << "7. Entry's office phone number" << std::endl;
					std::cout << "8. Entry's e-mail address" << std::endl;
					std::cout << "9. Entry's mobile phone number" << std::endl;
					std::cout << "10. Entry's street address" << std::endl;
					std::cout << "11. Entry's city" << std::endl;
					std::cout << "12. Entry's state" << std::endl;
					std::cout << "13. Entry's zip" << std::endl;
					std::cout << "14. Entry's country" << std::endl;
					std::cin >> menuchoice2;
					while (std::cin.fail())
					{
						std::cout << "Invalid entry.  Please Enter a number" << std::endl;
						std::cin.clear();
						std::cin.ignore(256, '\n');
						std::cin >> menuchoice2;
					}
					if (menuchoice < 15 && menuchoice > 0)
					{
						secondSorted = book.sortEntries(menuchoice, temp, true, menuchoice2);		//with secondary sort active
						return secondSorted;
					}
					else
					{
						std::cout << "Invalid Entry" << std::endl;
					}
				}
			}
			else
			{
				std::cout << "Invalid Entry" << std::endl;
			}
		}
	}
}


//	/*std::cout << "Would you like to perform a secondary sort with another field (y/n)" << std::endl;
//	char secondSort = '0';
//	std::cin >> secondSort;
//	vector<Node*> secondSorted;
//	while (secondSort != 'y' && secondSort != 'Y' && secondSort != 'n'&& secondSort != 'N')
//	{
//		std::cout << "Invalid entry, would you like to perform a secondary sort with another field (y/n)?" << std::endl;
//		std::cin >> secondSort;
//	}
//	if (secondSort == 'y' || secondSort == 'Y')
//	{
//		menuchoice = 0;
//		while (menuchoice <1 || menuchoice>18)
//		{
//			std::cout << "Please enter the field to perform a secondary sort with: " << std::endl;
//			std::cout << "1. Entry's ID number" << std::endl;
//			std::cout << "2. Entry's first name" << std::endl;
//			std::cout << "3. Entry's middle name (or initial)" << std::endl;
//			std::cout << "4. Entry's last name" << std::endl;
//			std::cout << "5. Entry's company" << std::endl;
//			std::cout << "6. Entry's home phone number" << std::endl;
//			std::cout << "7. Entry's office phone number" << std::endl;
//			std::cout << "8. Entry's e-mail address" << std::endl;
//			std::cout << "9. Entry's mobile phone number" << std::endl;
//			std::cout << "10. Entry's street address" << std::endl;
//			std::cout << "11. Entry's city" << std::endl;
//			std::cout << "12. Entry's state" << std::endl;
//			std::cout << "13. Entry's zip" << std::endl;
//			std::cout << "14. Entry's country" << std::endl;
//			std::cin >> menuchoice;
//			if (menuchoice < 15 && menuchoice > 0)
//			{
//				secondSorted = book.sortEntries(menuchoice, firstSorted, true);
//				return secondSorted;
//			}
//			else
//			{
//				std::cout << "Invalid Entry" << std::endl;
//			}
//		}*/
//
////	}
//	else
//	{
//		return firstSorted;
//	}
//
//}