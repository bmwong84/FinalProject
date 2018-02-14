
//Bryant Wong
//Final Project

#ifndef ENTRY_
#define ENTRY_
#include <iostream>
#include <vector>
#include <string>
#include "Affiliates.h"
#include "ContactInfo.h"

//class that is the data for the AddressBook binary search tree
class Entry //: public AddressBook
{
	friend class AddressBook;
private://each entry's identifiers
	std::string Id;								//ID is a string because we are not performing any mathematical functions on it.  can be changed to string for faster comparing
	std::string firstName;
	std::string middleName;
	std::string lastName;
	std::string company;
	ContactInfo contactInfo;		//a class to hold the entry's contact info
	std::vector <Affiliates> affiliates;		//a vector full of class Affiliates that hold the affiliates' identifiers and contact info
	//AddressBook & parent;
public:
	Entry();
	~Entry();

	void clearAffiliates()		//vector of affiliates kept adding cumulative affiliates, then I changed it to ptr.  now this is not needed
	{
		int size = this->affiliates.size();
		for (int count = 0; count < size; count++)
		{
			this->affiliates.pop_back();
		}
	}

	//setters and getters for each variable
	//gets the class to allow access to this class's private member variables
	ContactInfo& getContactInfo() 
	{ 
		return this->contactInfo; 
	}

	void setAffiliates(std::vector<Affiliates> _affiliates)
	{
		affiliates = _affiliates;
	}
	//gets the vector to allow acces to the affiliate class within
	std::vector<Affiliates>& getAffiliates()
	{
		return this->affiliates;
	}

	std::string getId()
	{
		return Id;
	};
	void setId(std::string& _Id)
	{
		Id = _Id;
	};
	std::string getFirstName()
	{
		return firstName;
	};
	void setFirstName(std::string& _firstName)
	{
		firstName = _firstName;
	};
	std::string getMiddleName()
	{
		return middleName;
	};
	void setMiddleName(std::string& _middleName)
	{
		middleName = _middleName;
	};
	std::string getLastName()
	{
		return lastName;
	};
	void setLastName(std::string& _lastName)
	{
		lastName = _lastName;
	};
	std::string getCompany()
	{
		return company;
	};
	void setCompany(std::string& _company)
	{
		company = _company;
	};
	
	
	
	
	
};




#endif
