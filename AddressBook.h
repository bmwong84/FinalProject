//Bryant Wong
//CSCI2421 final project
#include <string>
#include <sstream>
#include "BST.h"
#include "Node.h"
#include "Entry.h"
#ifndef ADDRESS_BOOK
#define ADDRESS_BOOK


class AddressBook
{
private:
	BST BSTBook;		//the binary search tree instance that holds the data

public:
	BST& getBSTBook()			//returns the instance of the class to allow access to member variables and functions
	{
		return this->BSTBook;
	}
	void addEntry(Entry* entry);			//passes an the pointer to the entry to be added
	void editEntry(int editField, Node* node);			//passes the field to edit and the pointer to the node that holds the entry to be edited
	void deleteEntry(Node* node);		//calls the search function in menu then is passed the node to be deleted
	std::vector<Node*> searchEntry(int searchField, std::string search, bool contains);		//returns a vector of node pointers pointing to the entries that were found
	//void searchEntryContains(int searchField, std::string search);		//switched to overloaded function above
	void readFile(std::ifstream& instream, AddressBook& book);			//reads the entire contents of the infile
	void writeFile(std::ofstream& outstream);		//not used, write to file is accomplished in the menu
	vector<Node*> sortEntries(int searchField, vector<Node*> sortList, bool secondSort, int searchField2=0);	//sort, overloaded for secondary sort
	void displayEntry(Node* aEntry);		//displays the data of the entry pointed to by the passed node
	
	//for searching vector, for every field
	static bool equals(std::string& search, Entry* entry2, int field, int affiliatesIndex = 0, bool contains=false)
	{
		if (field == 1)
		{
			if (contains)
			{
				return (entry2->getId().find(search) != std::string::npos);		//if search is searching for "contains", return if this the entry in the tree contains the user input
			}
			else
				return (search == entry2->getId());		//else returns true if it matches exactly
		}
		else if (field == 2)
		{
			if (contains)
			{
				return (entry2->getFirstName().find(search) != std::string::npos);		
			}
			else
				return (search == entry2->getFirstName());
		}
		else if (field == 3)
		{
			if (contains)
			{
				return (entry2->getMiddleName().find(search) != std::string::npos);		
			}
			else
				return (search == entry2->getMiddleName());
		}
		else if (field == 4)
		{
			if (contains)
			{
				return (entry2->getLastName().find(search) != std::string::npos);
			}
			else
				return (search == entry2->getLastName());
		}
		else if (field == 5)
		{
			if (contains)
			{
				return (entry2->getCompany().find(search) != std::string::npos);
			}
			else
				return (search == entry2->getCompany());
		}
		else if (field == 6)
		{
			if (contains)
			{
				return (entry2->contactInfo.getHomePhone().find(search) != std::string::npos);
			}
			else
				return (search == entry2->contactInfo.getHomePhone());
		}
		else if (field == 7)
		{
			if (contains)
			{
				return (entry2->contactInfo.getOfficePhone().find(search) != std::string::npos);
			}
			else
				return (search == entry2->contactInfo.getOfficePhone());
		}
		else if (field == 8)
		{
			if (contains)
			{
				return (entry2->contactInfo.getEMail().find(search) != std::string::npos);
			}
			else
				return (search == entry2->contactInfo.getEMail());
		}
		else if (field == 9)
		{
			if (contains)
			{
				return (entry2->contactInfo.getMobilePhone().find(search) != std::string::npos);
			}
			else
				return (search == entry2->contactInfo.getMobilePhone());
		}
		else if (field == 10)
		{
			if (contains)
			{
				return (entry2->contactInfo.getStreetAddress().find(search) != std::string::npos);
			}
			else
				return (search == entry2->contactInfo.getStreetAddress());
		}
		else if (field == 11)
		{
			if (contains)
			{
				return (entry2->contactInfo.getCity().find(search) != std::string::npos);
			}
			else
				return (search == entry2->contactInfo.getCity());
		}
		else if (field == 12)
		{
			if (contains)
			{
				return (entry2->contactInfo.getState().find(search) != std::string::npos);
			}
			else
				return (search == entry2->contactInfo.getState());
		}
		else if (field == 13)
		{
			if (contains)
			{
				return (entry2->contactInfo.getZip().find(search) != std::string::npos);
			}
			else
				return (search == entry2->contactInfo.getZip());
		}
		else if (field == 14)
		{
			if (contains)
			{
				return (entry2->contactInfo.getCountry().find(search) != std::string::npos);
			}
			else
				return (search == entry2->contactInfo.getCountry());
		}
		else if (field == 15)	//affiliates' first name
		{
			if (affiliatesIndex == 0)
			{
				return false;
			}
			if (contains)
			{
				return (entry2->affiliates[affiliatesIndex].getAffiliateFirstName().find(search) != std::string::npos);
			}
			else
				return (search == entry2->affiliates[affiliatesIndex].getAffiliateFirstName());
		}
		else if (field == 16)	//affiliates' last name
		{
			if (affiliatesIndex == 0)
			{
				return false;
			}
			if (contains)
			{
				return (entry2->affiliates[affiliatesIndex].getAffiliateLastName().find(search) != std::string::npos);
			}
			else
				return (search == entry2->affiliates[affiliatesIndex].getAffiliateLastName());
		}
		else if (field == 17)	//affiliates' cell num
		{
			if (affiliatesIndex == 0)
			{
				return false;
			}
			if (contains)
			{
				return (entry2->affiliates[affiliatesIndex].getAffiliateMobileNumber().find(search) != std::string::npos);
			}
			else
				return (search == entry2->affiliates[affiliatesIndex].getAffiliateMobileNumber());
		}
		else if (field == 18)	//affiliates' email address
		{
			if (affiliatesIndex == 0)
			{
				return false;
			}
			if (contains)
			{
				return (entry2->affiliates[affiliatesIndex].getAffiliateEMail().find(search) != std::string::npos);
			}
			else
				return (search == entry2->affiliates[affiliatesIndex].getAffiliateEMail());
		}
	}

	//for sorting vector
	//returns <= to essentially "skip" the entry for sorting if they are the same value
	static bool lessThan(Entry* entry1, Entry* entry2, int field, int affiliatesIndex = 0)
	{
		if (field == 1)
		{
			return (entry1->getId() <= entry2->getId());
		}
		else if (field == 2)
		{
			return (entry1->getFirstName() <= entry2->getFirstName());
		}
		else if (field == 3)
		{
			return (entry1->getMiddleName() <= entry2->getMiddleName());
		}
		else if (field == 4)
		{
			return (entry1->getLastName() <= entry2->getLastName());
		}
		else if (field == 5)
		{
			return (entry1->getCompany() <= entry2->getCompany());
		}
		else if (field == 6)
		{
			return (entry1->contactInfo.getHomePhone() <= entry2->contactInfo.getHomePhone());
		}
		else if (field == 7)
		{
			return (entry1->contactInfo.getOfficePhone() <= entry2->contactInfo.getOfficePhone());
		}
		else if (field == 8)
		{
			return (entry1->contactInfo.getMobilePhone() <= entry2->contactInfo.getMobilePhone());
		}
		else if (field == 9)
		{
			return (entry1->contactInfo.getEMail() <= entry2->contactInfo.getEMail());
		}
		else if (field == 10)
		{
			return (entry1->contactInfo.getStreetAddress() <= entry2->contactInfo.getStreetAddress());
		}
		else if (field == 11)
		{
			return (entry1->contactInfo.getCity() <= entry2->contactInfo.getCity());
		}
		else if (field == 12)
		{
			return (entry1->contactInfo.getState() <= entry2->contactInfo.getState());
		}
		else if (field == 13)
		{
			return (entry1->contactInfo.getZip() <= entry2->contactInfo.getZip());
		}
		else if (field == 14)
		{
			return (entry1->contactInfo.getCountry() <= entry2->contactInfo.getCountry());
		}
		else if (field == 15)	//affiliates' first name
		{
			if (affiliatesIndex == 0)
			{
				return false;
			}
			return (entry1->affiliates[affiliatesIndex].getAffiliateFirstName() <= entry2->affiliates[affiliatesIndex].getAffiliateFirstName());
		}
		else if (field == 16)	//affiliates' last name
		{
			if (affiliatesIndex == 0)
			{
				return false;
			}
			return (entry1->affiliates[affiliatesIndex].getAffiliateLastName() <= entry2->affiliates[affiliatesIndex].getAffiliateLastName());
		}
		else if (field == 17)	//affiliates' cell num
		{
			if (affiliatesIndex == 0)
			{
				return false;
			}
			return (entry1->affiliates[affiliatesIndex].getAffiliateMobileNumber() <= entry2->affiliates[affiliatesIndex].getAffiliateMobileNumber());
		}
		else if (field == 18)	//affiliates' email address
		{
			if (affiliatesIndex == 0)
			{
				return false;
			}
			return (entry1->affiliates[affiliatesIndex].getAffiliateEMail() <= entry2->affiliates[affiliatesIndex].getAffiliateEMail());
		}
	}


	//so many predicates!!!!!!!! for stable_sort
	static bool compareId(Node* left, Node* right)
	{
		return(left->getEntry()->getId() < right->getEntry()->getId());
	}
	static bool compareFirstName(Node* left, Node* right)
	{
		return(left->getEntry()->getFirstName() < right->getEntry()->getFirstName());
	}
	static bool compareMiddleName(Node* left, Node* right)
	{
		return(left->getEntry()->getMiddleName() < right->getEntry()->getMiddleName());
	}
	static bool compareLastName(Node* left, Node* right)
	{
		return(left->getEntry()->getLastName() < right->getEntry()->getLastName());
	}
	static bool compareCompany(Node* left, Node* right)
	{
		return(left->getEntry()->getCompany() < right->getEntry()->getCompany());
	}
	static bool compareHomePhone(Node* left, Node* right)
	{
		return(left->getEntry()->getContactInfo().getHomePhone() < right->getEntry()->getContactInfo().getHomePhone());
	}
	static bool compareOfficePhone(Node* left, Node* right)
	{
		return(left->getEntry()->getContactInfo().getOfficePhone() < right->getEntry()->getContactInfo().getOfficePhone());
	}
	static bool compareEmail(Node* left, Node* right)
	{
		return(left->getEntry()->getContactInfo().getEMail() < right->getEntry()->getContactInfo().getEMail());
	}
	static bool compareMobilePhone(Node* left, Node* right)
	{
		return(left->getEntry()->getContactInfo().getMobilePhone() < right->getEntry()->getContactInfo().getMobilePhone());
	}
	static bool compareStreetAddress(Node* left, Node* right)
	{
		return(left->getEntry()->getContactInfo().getStreetAddress() < right->getEntry()->getContactInfo().getStreetAddress());
	}
	static bool compareCity(Node* left, Node* right)
	{
		return(left->getEntry()->getContactInfo().getCity() < right->getEntry()->getContactInfo().getCity());
	}
	static bool compareState(Node* left, Node* right)
	{
		return(left->getEntry()->getContactInfo().getState() < right->getEntry()->getContactInfo().getState());
	}
	static bool compareZip(Node* left, Node* right)
	{
		return(left->getEntry()->getContactInfo().getZip() < right->getEntry()->getContactInfo().getZip());
	}
	static bool compareCountry(Node* left, Node* right)
	{
		return(left->getEntry()->getContactInfo().getCountry() < right->getEntry()->getContactInfo().getCountry());
	}

};

#endif