
#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

int main()
{
	std::string number;
	std::cin >> number;		//array of characters to be ignored includes ()- and space
	//for (int count = 0; count < std::strlen(ignoreChars); count++)
	//{
	//	number.erase(std::remove(number.begin(), number.end(), ignoreChars[count]));	//for each character, erase those characters
	//}


	number.erase(std::remove(number.begin(), number.end(), ')'));
	std::string number2 = number;
	number2.erase(std::remove(number2.begin(), number2.end(), '('));
	std::string number3 = number2;
	number3.erase(std::remove(number3.begin(), number3.end(), '-'));
	std::string number4 = number3;
	//number4.erase(std::remove(number4.begin(), number4.end(), ' '));
	
	std::cout << number4 << std::endl;

		return 0;		//if the entry is okay, return true
}