//Bryant Wong
//CSCI2421 final project

#ifndef BST_
#define	BST_

#include "Node.h"
//#include "Entry.h"		//cyclic including oops
#include <fstream>
//#include "Menu.h"

class BST	//from CSCI 2421 Homework 8
{
	friend class AddressBook;
private:
	Node* root;
	void addANode(std::string key, Entry* entry, Node* leaf);
	//Node* deleteNode(Node* root, Node* deleteTarget);		//for the old BST
	void deleteANode(Node* deleteTarget);	//for the new BST delete function.  this is the recursive function
	void freeNode(Node* leaf);
public:
	BST();
	~BST();
	Node* Root() { return root; }
	void setRoot(Node * _root) { root = _root; }
	void addNode(std::string key, Entry* entry);		//addNode still works after modification
	//only finds by ID
	Node* findNode(std::string Id, Node* parent);		//not used; searching is done elsewhere
	void printPreorder(Node* node);			//not used, but can be used if you want to print every ID in the tree in preorder
	void printInorder(Node* node);
	void printPostorder(Node* node);
	void deleteNode(Node* deleteTarget);		//also make this modular, change to node
	bool checkId(std::string Id, Node* node);
	//void searchTree(std::vector<Entry>, std::string search, Node* parent, int searchField);
	void toVector(Node* node, std::vector<Node*>& vect);

	Node* min(Node* node);
	Node* max(Node* node);
	//Node* successor(int key, Node* parent);
	//Node* predecessor(int key, Node* parent);		
};

#endif