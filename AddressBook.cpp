//Bryant Wong
//CSCI2421 final project

#include "AddressBook.h"
#include <algorithm>
#include <cstring>			//for strlen

Entry::Entry()
{}

Entry::~Entry()
{}

void AddressBook::addEntry(Entry* entry)
{
	this->BSTBook.addNode(entry->getId(), entry);			//add an entry to the binary search tree
}

void AddressBook::deleteEntry(Node* node)
{
	std::cout << "Deleting entry" << std::endl;			//delete an entry from the binary search tree
	this->BSTBook.deleteNode(node);
}

void AddressBook::displayEntry(Node* aEntry)			//displays the data of a passed node
{
	std::cout << "ID: " << aEntry->getEntry()->getId() << std::endl;
	std::cout << "First Name: " << aEntry->getEntry()->getFirstName() << std::endl;
	std::cout << "Middle Name/initial: " << aEntry->getEntry()->getMiddleName() << std::endl;
	std::cout << "Last Name: " << aEntry->getEntry()->getLastName() << std::endl;
	std::cout << "Company: " << aEntry->getEntry()->getCompany() << std::endl;
	std::cout << "Home Phone: " << aEntry->getEntry()->getContactInfo().getHomePhone() << std::endl;
	std::cout << "Office Phone: " << aEntry->getEntry()->getContactInfo().getOfficePhone() << std::endl;
	std::cout << "E-mail address: " << aEntry->getEntry()->getContactInfo().getEMail() << std::endl;
	std::cout << "Mobile Phone: " << aEntry->getEntry()->getContactInfo().getMobilePhone() << std::endl;
	std::cout << "Street Address: " << aEntry->getEntry()->getContactInfo().getStreetAddress() << std::endl;
	std::cout << "City: " << aEntry->getEntry()->getContactInfo().getCity() << std::endl;
	std::cout << "State:  " << aEntry->getEntry()->getContactInfo().getState() << std::endl;
	std::cout << "Zip: " << aEntry->getEntry()->getContactInfo().getZip() << std::endl;
	std::cout << "Country: " << aEntry->getEntry()->getContactInfo().getCountry() << std::endl;
	//std::cout << aEntry->getEntry()->getAffiliates().size();
	for (int count = 0; count < aEntry->getEntry()->getAffiliates().size(); count++)
	{
		std::cout << "Affiliate " << count + 1 << ": " << aEntry->getEntry()->getAffiliates()[count].getAffiliateFirstName() << " " << aEntry->getEntry()->getAffiliates()[count].getAffiliateLastName() <<
			", " << aEntry->getEntry()->getAffiliates()[count].getAffiliateMobileNumber() << ", " << aEntry->getEntry()->getAffiliates()[count].getAffiliateEMail() << std::endl;
	}
	std::cout << std::endl;
}

std::vector<Node*> AddressBook::searchEntry(int searchField, std::string search, bool contains)			//search algorithm, overloaded, if bool contains is false, then search exact, else search by contains
{
	{
		std::vector<Node*> temp;
		std::vector<Node*> firstResult;
		this->getBSTBook().toVector(this->getBSTBook().Root(), temp);		//this should populate the vector with pointers to the contents of the bst?
		for (int count = 0; count < temp.size(); count++) //for each entry in the vector
		{
			if (searchField >14 && searchField < 19 && temp[count]->getEntry()->getAffiliates().size()>0)		//searches through affiliate field
			{
				for (int affLoop=0; affLoop < temp[count]->getEntry()->getAffiliates().size(); affLoop++)
				{
					if (this->equals(search, temp[count]->getEntry(), searchField, affLoop, contains))
					{
						firstResult.push_back(temp[count]);			//if any of the affiliates contain what we are searching for, add the entry to the vector
						break;
					}
				}
			}
			{
				if (this->equals(search, temp[count]->getEntry(), searchField, 0, contains))			//searches any of the rest of the fields
				{
					firstResult.push_back(temp[count]);			//adds results to a vector
				}
			}
		}//end first search
		if (firstResult.size() > 0)
		{
			std::cout << firstResult.size() << " results found.  Would you like to view them?  (y/n)" << std::endl;
			char view;
			std::cin >> view;
			if (view == 'y' || view == 'Y')
			{
				std::cout << "Displaying search results" << std::endl;
				for (int count = 0; count < firstResult.size(); count++)
				{
					displayEntry(firstResult[count]);		//displays the search results
				}
			}
			std::cout << "Would you like to refine your search? (y/n)" << std::endl;
			char secSearch;
			std::cin >> secSearch;
			if (secSearch == 'y' || secSearch == 'Y')
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
					std::cout << "19. Return to main menu" << std::endl;
					std::cin >> menuchoice;
					while (std::cin.fail())
					{
						std::cout << "Invalid entry.  Please Enter a number" << std::endl;
						std::cin.clear();
						std::cin.ignore(256, '\n');
						std::cin >> menuchoice;
					}
					if (menuchoice < 19 && menuchoice >0)
					{
						if (contains)
							std::cout << "Enter the text or number the entry you are searching for may contain: ";
						else
							std::cout << "Enter the exact text or number you wish to search for: ";
						std::string secondSearchText;
						std::cin >> secondSearchText;
						std::vector<Node*> secondResult;
						for (int count = 0; count < firstResult.size(); count++) //for each entry in the vector
						{
							if (firstResult[count]->getEntry()->getAffiliates().size() > 0)		//get affiliate vector size
							{
								for (int affLoop = 0; affLoop < firstResult[count]->getEntry()->getAffiliates().size(); affLoop++)		//loops through affiliates
								{
									if (this->equals(secondSearchText, firstResult[count]->getEntry(), menuchoice, affLoop, contains))		//searches for any matches
									{
										secondResult.push_back(firstResult[count]);
										break;
									}
								}
							}
							else
							{
								if (this->equals(secondSearchText, firstResult[count]->getEntry(), menuchoice, 0, contains))		//else run through the other fields
								{
									secondResult.push_back(firstResult[count]);
								}
							}
						
						}
						if (secondResult.size() > 0)			//secondary search result size >0, then ask if they want to view
						{
							std::cout << secondResult.size() << " results found.  Would you like to view them?  (y/n)" << std::endl;
							char view;
							std::cin >> view;
							if (view == 'y' || view == 'Y')
							{
								std::cout << "Displaying secondary search results" << std::endl;
								for (int count = 0; count < secondResult.size(); count++)
								{
									displayEntry(secondResult[count]);
								}
							}
						}
						else if (secondResult.size() == 0)
						{
							std::cout << "No results match those criteria" << std::endl;
						}
						return secondResult;
						break;//end second search
					}
					else if (menuchoice == 19)
					{
						break;
					}
					else
						std::cout << "Invalid choice, please select a field" << std::endl;
				}
			}
			else                //if they don't want to perform secondary search
				return firstResult;
		}
		else
			std::cout << "No results match those criteria" << std::endl;
			return firstResult;
	}
}

// to check is integer from stack overflow, modified to accept my parameters
//http://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
inline bool isInteger(const std::string& string)
{
	if (string.empty() || ((!isdigit(string[0])) && (string[0] != '-') && (string[0] != '+')))
		return false;
	char *charPtr;
	strtol(string.c_str(), &charPtr, 10);
	return(*charPtr == 0);
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

void AddressBook::editEntry(int editField, Node* node)
{
	std::cout << "Enter the value you wish to change that field to: ";
	std::string fieldEntry;
	std::getline(std::cin >> std::ws, fieldEntry);
	if (editField == 1)//wow factor, check isdgit
	{
		while (getBSTBook().checkId(fieldEntry, getBSTBook().Root()) == false || fieldEntry.size() != 9 || !isInteger(fieldEntry))		//checks if an ID is already being used, is not 9 digits, or is not an integer
		{
			std::cout << "Invalid entry, please enter a unique 9-digit identification number" << std::endl;
			std::getline(std::cin >> ws, fieldEntry);		//if any of the above are true, ask for the entry again
		}
		node->getEntry()->setId(fieldEntry);			//sets the ID after proper entry is entered
	}
	else if (editField == 2)
	{
		node->getEntry()->setFirstName(fieldEntry);
	}
	else if (editField == 3)
	{
		node->getEntry()->setMiddleName(fieldEntry);
	}
	else if (editField == 4)
	{
		node->getEntry()->setLastName(fieldEntry);
	}
	else if (editField == 5)
	{
		node->getEntry()->setCompany(fieldEntry);
	}
	else if (editField == 6)
	{
		while (!checkPhoneNumber(fieldEntry))			//runs inline checkPhoneNumber for spaces, parentheses, or dashes, and whether it is a 10 digit phone numbers
		{
			std::cout << "Invalid entry.  Please enter a 10 digit phone number" << std::endl;
			std::getline(std::cin >> ws, fieldEntry);
		}
		node->getEntry()->getContactInfo().setHomePhone(fieldEntry);
	}
	else if (editField == 7)
	{
		while (!checkPhoneNumber(fieldEntry))
		{
			std::cout << "Invalid entry.  Please enter a 10 digit phone number" << std::endl;
			std::getline(std::cin >> ws, fieldEntry);
		}
		node->getEntry()->getContactInfo().setOfficePhone(fieldEntry);
	}
	else if (editField == 8)
	{
		while (!(fieldEntry.find("@") != std::string::npos) || !(fieldEntry.find(".") != std::string::npos))			//checks if email contains @ and . 
		{
			std::cout << "Invalid e-mail address.  E-mail address must contain '@' and '.'" << std::endl;
			std::cout << "Please enter the entry's e-mail address" << std::endl;
			std::getline(std::cin >> ws, fieldEntry);
		}
		node->getEntry()->getContactInfo().setEMail(fieldEntry);
	}
	else if (editField == 9)
	{
		while (!checkPhoneNumber(fieldEntry))
		{
			std::cout << "Invalid entry.  Please enter a 10 digit phone number" << std::endl;
			std::getline(std::cin >> ws, fieldEntry);
		}
		node->getEntry()->getContactInfo().setMobilePhone(fieldEntry);
	}
	else if (editField == 10)
	{
		node->getEntry()->getContactInfo().setStreetAddress(fieldEntry);
	}
	else if (editField == 11)
	{
		node->getEntry()->getContactInfo().setCity(fieldEntry);
	}
	else if (editField == 12)
	{
		node->getEntry()->getContactInfo().setState(fieldEntry);
	}
	else if (editField == 13)
	{
		node->getEntry()->getContactInfo().setZip(fieldEntry);
	}
	else if (editField == 14)
	{
		node->getEntry()->getContactInfo().setCountry(fieldEntry);
	}
	else if (editField >14 && editField < 19 && node->getEntry()->affiliates.size()>0)		//if the field is part of the affiliates and there are actually affiliates
	{
		std::cout << "Please enter the affiliate you wish to edit (1 - " << node->getEntry()->affiliates.size()<< ")" << std::endl;		//asks for the affiliate they wish to edit
		int affiliate;
		std::cin >> affiliate;
		while (std::cin.fail())
		{
			std::cout << "Invalid entry.  Please Enter a number" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> affiliate;
		}
		while (affiliate <1 || affiliate >node->getEntry()->affiliates.size())
		{
			std::cout << "Invalid number, please enter the affiliate you wish to edit (1 - " << node->getEntry()->affiliates.size() << ")" << std::endl;
			std::cin >> affiliate;
		}
		if (editField == 15)
		{
			node->getEntry()->getAffiliates()[affiliate].setAffiliateFirstName(fieldEntry);
		}
		else if (editField==16)
		{
			node->getEntry()->getAffiliates()[affiliate].setAffiliateLastName(fieldEntry);
		}
		else if (editField == 17)
		{
			while (!checkPhoneNumber(fieldEntry))
			{
				std::cout << "Invalid entry.  Please enter a 10 digit phone number" << std::endl;
				std::getline(std::cin >> ws, fieldEntry);
			}
			node->getEntry()->getAffiliates()[affiliate].setAffiliateMobileNumber(fieldEntry);
		}
		else if (editField == 18)
		{
			while (!(fieldEntry.find("@") != std::string::npos) || !(fieldEntry.find(".") != std::string::npos))
			{
				std::cout << "Invalid e-mail address.  E-mail address must contain '@' and '.'" << std::endl;
				std::cout << "Please enter the entry's e-mail address" << std::endl;
				std::getline(std::cin >> ws, fieldEntry);
			}
			node->getEntry()->getAffiliates()[affiliate].setAffiliateEMail(fieldEntry);
		}
	}
	else if (node->getEntry()->affiliates.size() == 0)
	{
		std::cout << "No affiliates to edit" << std::endl;
	}
	std::cout << "Entry edited to: " << std::endl;
	displayEntry(node);
}





void AddressBook::readFile(std::ifstream& instream, AddressBook& book)		//to read the file provided
{
	Entry* tempEntry;
	std::string tId, tFirstName, tMiddleName, tLastName, tCompany, tHomePhone, tOfficePhone, tMobilePhone, tEmail, tStreetAddress, tCity, tState, tZip, tCountry, tAffiliateLine, tAffiliateFirstName, tAffiliateLastName, tAffiliateMobileNumber, tAffiliateEmail;
	int test=0;

	while (!instream.eof())
	{
		std::getline(instream, tId);
		tempEntry = new Entry();
		if (tId != "|")			//check if line is the end of the entry
		{
			tempEntry->setId(tId);
			std::getline(instream, tFirstName);
		}
		else
			continue;
		if (tFirstName != "|")
		{
			tempEntry->setFirstName(tFirstName);
			std::getline(instream, tMiddleName);
		}
		else
			continue;
		if (tMiddleName != "|")
		{
			tempEntry->setMiddleName(tMiddleName);
			std::getline(instream, tLastName);
		}
		else
			continue;
		if (tLastName != "|")
		{
			tempEntry->setLastName(tLastName);
			std::getline(instream, tCompany);
		}
		else
			continue;
		if (tCompany != "|")
		{
			tempEntry->setCompany(tCompany);
			std::getline(instream, tHomePhone);
		}
		if (tHomePhone != "|")
		{
			tempEntry->contactInfo.setHomePhone(tHomePhone);
			std::getline(instream, tOfficePhone);
		}
		else
			continue;
		if (tOfficePhone != "|")
		{
			tempEntry->contactInfo.setOfficePhone(tOfficePhone);
			std::getline(instream, tEmail);
		}
		else
			continue;
		if (tEmail != "|")
		{
			tempEntry->contactInfo.setEMail(tEmail);
			std::getline(instream, tMobilePhone);
		}
		else
			continue;
		if (tMobilePhone != "|")
		{
			tempEntry->contactInfo.setMobilePhone(tMobilePhone);
			std::getline(instream, tStreetAddress);
		}
		else
			continue;
		if (tStreetAddress != "|")
		{
			tempEntry->contactInfo.setStreetAddress(tStreetAddress);
			std::getline(instream, tCity);
		}
		else
			continue;
		if (tCity != "|")
		{
			tempEntry->contactInfo.setCity(tCity);
			std::getline(instream, tState);
		}
		else
			continue;
		if (tState != "|")
		{
			tempEntry->contactInfo.setState(tState);
			std::getline(instream, tZip);
		}
		else
			continue;
		if (tZip != "|")
		{
			tempEntry->contactInfo.setZip(tZip);
			std::getline(instream, tCountry);
		}
		else
			continue;
		if (tCountry != "|")
		{
			tempEntry->contactInfo.setCountry(tCountry);
			std::getline(instream, tAffiliateLine);
			while (tAffiliateLine != "|")
			{
				std::stringstream tssAffiliate(tAffiliateLine);
				Affiliates tAffiliateEntry;		//creates a temp instance of class Affiliate
				std::string tString;		//creats a temp string
				std::getline(tssAffiliate, tString, ',');		//reads the first and last name into tString
				std::stringstream tssName;
				tssName << tString;		//places first and last name into a temp string stream
				std::getline(tssName, tAffiliateFirstName, ' ');		//reads the first name into tAffiliateFirstName until a space
				tAffiliateEntry.setAffiliateFirstName(tAffiliateFirstName);		//sets the first name of the affiliate to what was read
				std::getline(tssName, tAffiliateLastName, ' ');
				tAffiliateEntry.setAffiliateLastName(tAffiliateLastName);
				std::getline(tssAffiliate, tAffiliateMobileNumber, ',');		//reads the mobile number, the next string in the affiliate before the next comma
				tAffiliateEntry.setAffiliateMobileNumber(tAffiliateMobileNumber);
				std::getline(tssAffiliate, tAffiliateEmail, ';');
				tAffiliateEntry.setAffiliateEMail(tAffiliateEmail);
				tempEntry->affiliates.push_back(tAffiliateEntry);
				//std::cout << tempEntry->getAffiliates()[0].getAffiliateFirstName();			//test code; affiliates were not being imported correctly
				std::getline(instream, tAffiliateLine);
				//if (tAffiliateLine == "|")
				//	break;
			}
			tempEntry->setAffiliates(tempEntry->affiliates);
		}
		book.BSTBook.addNode(tempEntry->getId(), tempEntry);		
		/*test++;				//test code to check if they were reading in all the files
		if (test % 10 == 0)
		{
			std::cout << "Read in " << test << "entries"<<std::endl;;
		}*/
		//tempEntry->clearAffiliates();
	}
}
void AddressBook::writeFile(ofstream& outstream)
{

}
vector<Node*> AddressBook::sortEntries(int searchField, vector<Node*>sortList, bool secondSort, int searchField2)
{
	vector<Node*> temp = sortList;
	const int totalSearchFields = 15;
	if (secondSort)		//if sorting by two fields
	{
		//I was going to make the code pretty but the predicate in the stable_sort is giving me problems
		//for (int count = 1; count < totalSearchFields; count++)
		//{

		//}

		//SORRY ABOUT THIS CODE.  checks every combination of first and second search field for secondary sort
		//Actually, I believe stable_sort must mark whatever it has sorted once before when you run it again the second time, it can see
		//exactly what was sorted before and maintain that sorting fidelity but both must be called in the same function/not lose scope
		//because when I ran two different sorts, it did not "remember" how the first one was sorted when only calling a stable_sort on the second sort.
		if (searchField == 1)			
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareId);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 2)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 3)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 4)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 5)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 6)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 7)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 8)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 9)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 10)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 11)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 12)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareState);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 13)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		else if (searchField == 14)
		{
			std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			if (searchField2 == 1)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareId);
			}
			else if (searchField2 == 2)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareFirstName);
			}
			else if (searchField2 == 3)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMiddleName);
			}
			else if (searchField2 == 4)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareLastName);
			}
			else if (searchField2 == 5)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCompany);
			}
			else if (searchField2 == 6)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareHomePhone);
			}
			else if (searchField2 == 7)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareOfficePhone);
			}
			else if (searchField2 == 8)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareEmail);
			}
			else if (searchField2 == 9)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareMobilePhone);
			}
			else if (searchField2 == 10)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareStreetAddress);
			}
			else if (searchField2 == 11)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCity);
			}
			else if (searchField2 == 12)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareState);
			}
			else if (searchField2 == 13)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareZip);
			}
			else if (searchField2 == 14)
			{
				std::stable_sort(temp.begin(), temp.end(), this->compareCountry);
			}
		}
		return temp;
	}
	else if (secondSort == false)		//if only sorting by one field
	//bubblesort from Gaddis C++: From Control Structures through Objects 8th ed. brief pp
	{
		bool swap;
		Node* tempNode;
		do
		{
			swap = false;		//set bool to false
			for (int count = 0; count < temp.size() - 1; count++)
			{
				if (!(lessThan(temp[count]->getEntry(), temp[count + 1]->getEntry(), searchField)) /*== false*/)		//if less than is false, sort it
				{
					tempNode = temp[count];					//swaps the nodes
					temp[count] = temp[count + 1];
					temp[count + 1] = tempNode;
					swap = true;		//if a swap occured, set to bool to true to run the sort again
				}
			}
		} while (swap);
		return temp;			//return the sorted vector of nodes
	}
}

//below is stuff i never used
////contains?  overloaded search function instead
//void AddressBook::searchEntryContains(int searchField, std::string search)
//{
//	{
//		std::vector<Node*> temp;
//		std::vector<Node*> firstResult;
//		this->getBSTBook().toVector(this->getBSTBook().Root(), temp);		//this should populate the vector with pointers to the contents of the bst?
//		for (int count = 0; count < temp.size(); count++) //for each entry in the vector
//		{
//			if (temp[count]->getEntry()->getAffiliates().size() > 14 && temp[count]->getEntry()->getAffiliates().size() < 19)
//			{
//				for (int affLoop; affLoop < temp[count]->getEntry()->getAffiliates().size(); affLoop++)
//				{
//					if (this->equals(search, temp[count]->getEntry(), searchField, affLoop, true))
//					{
//						firstResult.push_back(temp[count]);
//					}
//				}
//			}
//			else
//			{
//				if (this->equals(search, temp[count]->getEntry(), searchField, 0, true))
//				{
//					firstResult.push_back(temp[count]);
//				}
//			}
//		}//end first search
//		std::cout << firstResult.size() << " results found.  Would you like to view them?  (y/n)" << std::endl;
//		char view;
//		std::cin >> view;
//		if (view == 'y' || view == 'Y')
//		{
//			std::cout << "Displaying search results" << std::endl;
//			for (int count = 0; count < firstResult.size(); count++)
//			{
//				displayEntry(firstResult[count]);
//			}
//		}
//		std::cout << "Would you like to refine your search? (y/n)" << std::endl;
//		char secSearch;
//		std::cin >> secSearch;
//
//		if (secSearch == 'y' || secSearch == 'Y')
//		{
//			int menuchoice = 0;
//			while (menuchoice != 19)
//			{
//				std::cout << "Please enter the field with which you wish to search for the entry " << std::endl;
//				std::cout << "1. Entry's ID number" << std::endl;
//				std::cout << "2. Entry's first name" << std::endl;
//				std::cout << "3. Entry's middle name (or initial)" << std::endl;
//				std::cout << "4. Entry's last name" << std::endl;
//				std::cout << "5. Entry's company" << std::endl;
//				std::cout << "6. Entry's home phone number" << std::endl;
//				std::cout << "7. Entry's office phone number" << std::endl;
//				std::cout << "8. Entry's e-mail address" << std::endl;
//				std::cout << "9. Entry's mobile phone number" << std::endl;
//				std::cout << "10. Entry's street address" << std::endl;
//				std::cout << "11. Entry's city" << std::endl;
//				std::cout << "12. Entry's state" << std::endl;
//				std::cout << "13. Entry's zip" << std::endl;
//				std::cout << "14. Entry's country" << std::endl;
//				std::cout << "15. Entry's affiliate's first name" << std::endl;
//				std::cout << "16. Entry's affiliate's last name" << std::endl;
//				std::cout << "17. Entry's affiliate's mobile number" << std::endl;
//				std::cout << "18. Entry's affiliate's e-mail" << std::endl;
//				std::cout << "19. Return to main menu" << std::endl;
//				std::cin >> menuchoice;
//				if (menuchoice < 19 && menuchoice >0)
//				{
//					std::cout << "Enter the text or number the entry you are searching for may contain: ";
//					std::string secondSearchText;
//					std::cin >> secondSearchText;
//					std::vector<Node*> secondResult;
//					for (int count = 0; count < firstResult.size(); count++) //for each entry in the vector
//					{
//						if (firstResult[count]->getEntry()->getAffiliates().size() > 14 && firstResult[count]->getEntry()->getAffiliates().size() < 19)
//						{
//							for (int affLoop; affLoop < firstResult[count]->getEntry()->getAffiliates().size(); affLoop++)
//							{
//								if (this->equals(secondSearchText, firstResult[count]->getEntry(), menuchoice, affLoop, true))
//								{
//									secondResult.push_back(firstResult[count]);
//								}
//							}
//						}
//						else
//						{
//							if (this->equals(secondSearchText, firstResult[count]->getEntry(), menuchoice, 0, true))
//							{
//								secondResult.push_back(firstResult[count]);
//							}
//						}
//					}
//					std::cout << secondResult.size() << " results found.  Would you like to view them?  (y/n)" << std::endl;
//					char view;
//					std::cin >> view;
//					if (view == 'y' || view == 'Y')
//					{
//						std::cout << "Displaying secondary search results" << std::endl;
//						for (int count = 0; count < secondResult.size(); count++)
//						{
//							displayEntry(secondResult[count]);
//						}
//					}
//					break;//end second search
//				}
//				else if (menuchoice == 19)
//				{
//					break;
//				}
//				else
//					std::cout << "Invalid choice, please select a field" << std::endl;
//			}
//
//		}
//	}
//}

//beginning of "exact search"
//if (searchField == 1)
//{
//	//returns the pointer to the node with the entry with this ID exactly
//	if (this->getBSTBook().findNode(search, this->getBSTBook().Root()) == nullptr)
//	{
//		std::cout << "No entries with ID match exactly to " << search << std::endl;
//	}
//	else
//	{
//		std::cout << "Entry found, would you like to display the entry's contents (y/n)?" << std::endl;
//		char display;
//		std::cin >> display;
//		if (display == 'y' || display == 'Y')
//		{
//			displayEntry(this->getBSTBook().findNode(search, this->getBSTBook().Root()));
//		}
//	}
//}
//else