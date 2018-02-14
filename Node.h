
//Bryant Wong
//FinalProject

#ifndef NODE_
#define NODE_
#include <iostream>
#include "Entry.h"
using namespace std;

// A generic tree node class

//Placeholder for a composite data type
//will most likely change datatype to class Entry as data for final project
//class Datatype {
//private:
//	//int number;
//	Entry entry;
//
//
//};

//Binary Tree Node
class Node {
private:
	//int key;
	//Datatype data;
	std::string key;	//holds the key
	Entry* entry;		//holds the data
	Node* left;
	Node* right;
	Node* parent;
public:
	Node() {/*entry;*/ left = nullptr; right = nullptr; parent = nullptr; };	//default const
	void setEntry(Entry* aEntry) { entry = aEntry; }
	void setKey(std::string& aKey) { key=aKey; };
	void setLeft(Node* aLeft) { left = aLeft; };
	void setRight(Node* aRight) { right = aRight; };
	void setParent(Node* aParent) { parent = aParent; };
	std::string& Key() { return key; };			//returns the key
	Entry* getEntry() { return entry; };		//returns the entry
	Node* Left() { return left; };
	Node* Right() { return right; };
	Node* Parent() { return parent; };
};
#endif
