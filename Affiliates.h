//Bryant Wong
//CSCI 2421 Final Project

#ifndef AFFILIATES_
#define AFFILIATES_
#include <iostream>
#include <string>

//a class holding an entry's affiliates
class Affiliates//:public Entry
{
	friend class Entry;
	friend class AddressBook;
private:
	//the affiliate's identifiers and contact info
	std::string affiliateFirstName;
	std::string affiliateLastName;
	std::string affiliateMobileNumber;
	std::string affiliateEMail;
public:

	//setters and getters for these variables
	std::string getAffiliateFirstName()
	{
		return affiliateFirstName;
	};
	void setAffiliateFirstName(std::string& _affiliateFirstName)
	{
		affiliateFirstName = _affiliateFirstName;
	};
	std::string getAffiliateLastName()
	{
		return affiliateLastName;
	};
	void setAffiliateLastName(std::string& _affiliateLastName)
	{
		affiliateLastName = _affiliateLastName;
	};
	std::string getAffiliateMobileNumber()
	{
		return affiliateMobileNumber;
	};
	void setAffiliateMobileNumber(std::string& _affiliateMobileNumber)
	{
		affiliateMobileNumber = _affiliateMobileNumber;
	};
	std::string getAffiliateEMail()
	{
		return affiliateEMail;
	};
	void setAffiliateEMail(std::string& _affiliateEMail)
	{
		affiliateEMail = _affiliateEMail;
	};
};
#endif
