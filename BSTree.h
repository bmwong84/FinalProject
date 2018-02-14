#ifndef BSTREE_
#define BSTREE_
#include <iostream>
using namespace std;
#include "Node.h"

// Binary Search Tree class
class BSTree {
private:
    Node* root;
    void addNode(int key, Node* leaf);
    Node* deleteNode(Node* node, int key);
    void freeNode(Node* leaf);
public:
    BSTree();
    ~BSTree();
    Node* Root() { return root; }
    void setRoot(Node * _root) {root = _root;}
    void addNode(int key);
    Node* findNode(int key, Node* parent);
    void printPreorder(Node* node);
    void printInorder(Node* node);
    void printPostorder(Node* node);
    

    void deleteNode(int key);

    Node* min(Node* node);
    Node* max(Node* node);
    Node* successor(int key, Node* parent);
    Node* predecessor(int key, Node* parent);

};
#endif  //BST
