
//Bryant Wong
//code from CSCI 2421 Homework 8


#include "BST.h"

// Constructor
BST::BST() {
	root = nullptr;
}

// Destructor
BST::~BST() {
	std::cout << "Deleting entire tree pointer" << std::endl;
	if (root != nullptr)
		freeNode(root);
	std::cin.get();
}

// Free the node
void BST::freeNode(Node* leaf)
{
	if (this->Root() == leaf)
	{

	}
	else if (leaf != nullptr)

	{
		freeNode(leaf->Left());
		freeNode(leaf->Right());
		delete leaf;
	}

}

// Add a node
void BST::addNode(std::string key, Entry* entry)
{
	// No elements. Add the root
	if (root == nullptr) {
		Node* n = new Node();
		n->setKey(key);
		n->setEntry(entry);
		root = n;
		//Bryant Wong
		//std::cout << "Root set to " << n->Key() << std::endl;
	}
	else {
		addANode(key, entry, root);
	}
}

// Add a node (private)
void BST::addANode(std::string key, Entry* entry, Node* leaf) 
{
	if (key <= leaf->Key())
	{
		if (leaf->Left() != nullptr)
		{
			addANode(key, entry, leaf->Left());
		}
		else {
			Node* n = new Node();
			n->setKey(key);
			n->setEntry(entry);
			n->setParent(leaf);
			leaf->setLeft(n);
			//Bryant Wong
			//std::cout << "Adding " << n->Key() << std::endl;;
		}
	}
	else
	{
		if (leaf->Right() != nullptr)
			addANode(key, entry, leaf->Right());
		else {
			Node* n = new Node();
			n->setEntry(entry);
			n->setKey(key);
			n->setParent(leaf);
			leaf->setRight(n);
			//Bryant Wong
			//std::cout << "Adding " << n->Key() << std::endl;;
		}
	}
}



//traverses the tree and adds each node to a vector
void BST::toVector(Node* node, std::vector<Node*>& vect)
{
	Node* temp = node;
	if (temp != nullptr)
	{
		vect.push_back(temp);
		toVector(temp->Left(), vect);
		toVector(temp->Right(), vect);
	}
}

//check ID to see if it has been used or not
bool BST::checkId(std::string Id, Node* node)
{
	if (node != nullptr)
	{
		if (node->getEntry()->getId() == Id)
			return false;		//if used, return false
		else
		{
			checkId(Id, node->Left());
			checkId(Id, node->Right());
		}
	}
	return true;  //if tree empty or it has traversed the entire tree and the id is not used, return true
}

// Print the BST
//Bryant Wong
void BST::printPreorder(Node* node)
{
	if (node != nullptr)
	{
		std::cout << node->getEntry()->getId() << std::endl;			//prints the node it is currently at
		printPreorder(node->Left());			//then finds the smallest value in the left tree
		printPreorder(node->Right());			//then the largest value of that subtree
	}
}

//Bryant Wong
void BST::printInorder(Node* node)
{
	if (node != nullptr)		//if the root node exists, i.e. not empty tree
	{
		printInorder(node->Left());		//recurs this function for the left node until no more left nodes (smallest value)
		std::cout << node->getEntry()->getId() << std::endl;		//prints the data in the node
		printInorder(node->Right());		//recurs function for right most node, (highest value in the left most tree)
	}
}

//Bryant Wong
void BST::printPostorder(Node* node)
{
	if (node != nullptr)
	{
		printPostorder(node->Left());		//traverses to the smallest value node 
		printPostorder(node->Right());		//then to the largest value node in that subtree
		std::cout << node->getEntry()->getId() << std::endl;		//prints the data in the current node
	}
}

// Find the node with min key
// Traverse the left sub-BST recursively
// till left sub-BST is empty to get min
Node* BST::min(Node* node)
{
	Node* tempNode = node;
	if (node == nullptr)
		tempNode = nullptr;
	else if (node->Left())
	{
		tempNode = min(node->Left());
	}
	else
		tempNode = node;

	return tempNode;
}

// Find the node with max key
// Traverse the right sub-BST recursively
// till right sub-BST is empty to get max
Node* BST::max(Node* node)
{
	Node * tempNode = node;
	if (node == nullptr)
		tempNode = nullptr;
	else if (node->Right())
		tempNode = max(node->Right());
	else
		tempNode = node;

	return tempNode;
}



void BST::deleteNode(Node* deleteTarget)
{
	if (deleteTarget != nullptr)
	{
		//if it is the root only node in the tree
		if (deleteTarget->Parent() == nullptr && deleteTarget->Right() == nullptr && deleteTarget->Left() == nullptr)
		{
			delete root;			//delete it and the data in it and set it to nullptr
			root = nullptr;
		}
		else deleteANode(deleteTarget); //else run delete method
	}
}

//delete method code from Daniel Kalam; 
//the Homework8 code was not working in all cases: I tested the homework 8 code and it would delete fine if there was only a left or right subtree or no subtrees on the delete target
//but if there were both left and right subtrees, it would not delete anything
//Modified to accept the parameters i passed
void BST::deleteANode(Node* deleteTarget)
{
	//if (deleteTarget != nullptr)		//if it's not null
	//{
		if (deleteTarget->Left() == nullptr && deleteTarget->Right() == nullptr) //if it has no children
		{
			if (deleteTarget->Parent()->Left()==deleteTarget)	//check if the deletetarget is to the left of its parent
			{
				deleteTarget->Parent()->setLeft(nullptr);	//set parent's left to no longer point to deleteTarget
			}
			else if (deleteTarget->Parent()->Right() == deleteTarget)	//check if the deletetarget is to the right of its parent
			{
				deleteTarget->Parent()->setRight(nullptr);
			}
			delete deleteTarget;		//delete it
		}
		else if (deleteTarget->Left() != nullptr&& deleteTarget->Right() != nullptr)		//if both left and right have subtrees
		{
			Node* temp = min(deleteTarget->Right());		//cut itself out, replace it with the next highest valued node in the right subtree
			deleteTarget->setEntry(temp->getEntry());
			deleteTarget->setKey(temp->Key());
			deleteANode(temp);
		}
		//the passed node is a now a misnomer, since we are deleting the temp node 
		else if (deleteTarget->Left() != nullptr)	//if the target only has left subtree
		{
			Node* temp = deleteTarget->Left();			//make a pointer to point to the target's left child
			//replace the data and pointers in the original node with everything from the left child, essentially, cutting the delete target out of the tree
			deleteTarget->setEntry(temp->getEntry());	
			deleteTarget->setKey(temp->Key());
			deleteTarget->setLeft(temp->Left());
			deleteTarget->setRight(temp->Right());
			if (deleteTarget->Right() != nullptr)		//if the original left child has a right subtree
				deleteTarget->Right()->setParent(deleteTarget);		//set the right subtree's parent to point at what the left child was originally pointing at
			if (deleteTarget->Left() != nullptr)			//if the original left child has a left subtree, set the parent to the currentNode
				deleteTarget->Left()->setParent(deleteTarget);
			delete temp;			//delete the node that was cut out
		}
		else if (deleteTarget->Right() != nullptr)  //if it only has a right subtree
		{
			Node* temp = deleteTarget->Right();
			deleteTarget->setEntry(temp->getEntry());
			deleteTarget->setKey(temp->Key());
			deleteTarget->setLeft(temp->Left());
			deleteTarget->setRight(temp->Right());
			if (deleteTarget->Right() != nullptr)		//if the original right child has a right subtree
				deleteTarget->Right()->setParent(deleteTarget);		//set the right subtree's parent to point at what the right child was originally pointing at
			if (deleteTarget->Left() != nullptr)			//if the original right child has a left subtree, set the parent to the currentNode
				deleteTarget->Left()->setParent(deleteTarget);
			delete temp;			//delete the node that was cut out
		}
	//}
}



//void BST::deleteNode(Node* deleteTarget)		//node instead of int
//{
//	//std::cout << "Deleting " << key << std::endl;
//	if (deleteANode(Root(), deleteTarget) == nullptr)
//		setRoot(nullptr);
//}
////deleteNode (Private) 
//Node* BST::deleteNode(Node* root, Node* deleteTarget) 
//{
//	bool isHead = (Root() == root);
//	if (root == nullptr) return root;
//	else if (deleteTarget->Key() < root->Key())
//		root->setLeft(deleteNode(root->Left(), deleteTarget));
//	else if (deleteTarget->Key() > root->Key())
//		root->setRight(deleteNode(root->Right(), deleteTarget));
//	else {	//if key to be deleted is equal to root->key, delete the node
//		if (root->Left() == nullptr && root->Right() == nullptr) 
//		{
//			delete root;
//			root = nullptr;
//		}
//		else if (root->Left() == nullptr) 
//		{
//			Node *temp = root;
//			root = root->Right();
//			delete temp;
//		}
//		else if (root->Right() == nullptr) 
//		{
//			Node *temp = root;
//			root = root->Left();
//			delete temp;
//		}
//		else 
//		{
//			Node *temp = min(root->Right());
//			root->setKey(temp->Key());
//			root->setRight(deleteNode(root->Right(), temp));	
//		}
//	}
//	if (isHead) setRoot(root);
//	return root;
//}
//

// Find a node
//final not used
//Bryant Wong  THIS NEED TO BE MODULAR, int key will be passed root node pointer and the field 
//finds node by ID
//Node* BST::findNode(std::string Id, Node* node /*value of search*/)		//passed root node and value you want to search for
//{
//	Node * temp = node;
//	if (temp == nullptr)		//if tree is empty, return nullptr
//	{
//		//std::cout << "Node " << key << " not found" << std::endl;
//		return nullptr;
//	}
//	while (temp != nullptr)
//	{
//		if (temp->Key().getId() == Id)		//if the value we are searching for is equal to the value in the root node, return the root node
//		{
//			std::cout << Id << " found at address " << temp << std::endl;
//			return temp;
//		}
//		else if (Id > temp->Key().getId())		//if the value is greater than the value we are searching for, traverse right
//		{
//			if (temp->Right() == nullptr)		//if the value in the node is greater than the value we are searching for and there is nothing greater than this node's value, return nullptr because value is not in tree
//			{
//				std::cout << "Entry with ID " << Id << " not found" << std::endl;
//				return nullptr;
//			}
//			else           //else traverse right
//			{
//				temp = temp->Right();
//			}
//		}
//		else if (Id < temp->Key().getId())	//if the value is less than the value we are searching for, traverse left
//		{
//			if (temp->Left() == nullptr)	//if there is nothing to the left of this node and the value is smaller, value is not in tree, return nullptr
//			{
//				std::cout << "Entry with ID " << Id << " not found" << std::endl;
//				return nullptr;
//			}
//			else					//else traverse left
//			{
//				temp = temp->Left();
//			}
//		}
//	}
//}


// Find successor to a node
// Find the node, get the node with max value
// for the right sub-BST to get the successor
//Node* BST::successor(int key, Node *node)
//{
//	Node *successor = nullptr;
//	Node *current = root;
//	if (root == nullptr)
//		return NULL;
//
//	while (current->Key() != key) {
//		/* If node value is greater than the node which are looking for, then go to left sub tree
//		Also when we move left, update the successor pointer to keep track of lst left turn */
//
//		if (current->Key() >key) {
//			successor = current;
//			current = current->Left();
//		}
//		/* Else take right turn and no need to update successor pointer */
//		else
//			current = current->Right();
//	}
//	/*Once we reached at the node for which inorder successor is to be found, check if it has right sub tree, if yes then find the minimum in that right sub tree and return that node
//
//	Else last left turn taken node is already stored in successor pointer and will be returned*/
//	if (current && current->Right()) {
//		successor = min(current->Right());
//	}
//	return successor;
//}

// Find predecessor to a node
// Find the node, get the node with max value
// for the left sub-BST to get the predecessor
//Node* BST::predecessor(int key, Node *node)
//{
//
//	Node* current = findNode(key, node);
//
//	if (current == nullptr)
//	{
//		return nullptr;
//	}
//
//	if (current->Left() != nullptr)
//	{
//		return max(current->Left());
//	}
//	else
//
//	{
//		Node *tempParent = current->Parent();
//		while (tempParent != nullptr) {
//			if (current == tempParent->Right()) {
//				break;
//			}
//			current = tempParent;
//			tempParent = current->Parent();
//		}
//		return tempParent;
//	}
//}