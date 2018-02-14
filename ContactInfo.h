//Bryant Wong
//Final Project

#ifndef CONTACT_
#define CONTACT_
#include <iostream>
#include <string>

//class holding the contact info for an entry
class ContactInfo//: public Entry
{
	friend class Entry;
	friend class AddressBook;

private:
	std::string homePhone;		//contact info involving only numbers are being used as strings because Schwab told us "we are not performing any sort of math on these numbers, so they should be strings"
	std::string officePhone;
	std::string eMail;
	std::string mobilePhone;
	std::string streetAddress;
	std::string city;
	std::string state;
	std::string zip;
	std::string country;
	//Entry & parent;		//thought i needed this to access private member fucntions but i do not
public:
	//setters and getters for each variable
	std::string getHomePhone() 
	{ 
		return homePhone; 
	};
	void setHomePhone(std::string& _homePhone) 
	{
		homePhone = _homePhone;
	};
	std::string getOfficePhone()
	{
		return officePhone;
	};
	void setOfficePhone(std::string& _officePhone)
	{
		officePhone = _officePhone;
	};
	std::string getMobilePhone()
	{
		return mobilePhone;
	};
	void setMobilePhone(std::string& _mobilePhone)
	{
		mobilePhone = _mobilePhone;
	};
	std::string getEMail()
	{
		return eMail;
	};
	void setEMail(std::string& _eMail)
	{
		eMail = _eMail;
	};
	std::string getStreetAddress()
	{
		return streetAddress;
	};
	void setStreetAddress(std::string& _streetAddress)
	{
		streetAddress = _streetAddress;
	};
	std::string getCity()
	{
		return city;
	};
	void setCity(std::string& _city)
	{
		city = _city;
	};
	std::string getState()
	{
		return state;
	};
	void setState(std::string& _state)
	{
		state = _state;
	};
	std::string getZip()
	{
		return zip;
	};
	void setZip(std::string& _zip)
	{
		zip = _zip;
	};
	std::string getCountry()
	{
		return country;
	};
	void setCountry(std::string& _country)
	{
		country = _country;
	};

};



#endif
