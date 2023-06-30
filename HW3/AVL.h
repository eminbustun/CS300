// Bulent Emin Ustun - 27822
#pragma once
#ifndef AVL_H
#define AVL_H


#include <fstream>
#include <string>

template <class Comparable>
class AvlTree;

template <class Comparable>
class AvlNode
{
	Comparable 	element;
	AvlNode   		*left;
	AvlNode   		*right;
	int        		height;

	AvlNode(const Comparable & theElement, AvlNode *lt, AvlNode *rt, int h = 0):element(theElement), left(lt), right(rt), height(h) {}

	friend class AvlTree<Comparable>;
};



template <class Comparable>
class AvlTree
{

public:

	explicit AvlTree(const Comparable & notFound); // constructor
	AvlTree(const AvlTree & rhs); // copy constructor
	~AvlTree(); // destructor

	const Comparable & findMin() const; // find minimum
	const Comparable & findMax() const; // find maximum
	const Comparable & find(std::string fullNameORpartial) const; // find for a key or partial key
	bool isEmpty() const; // check if the root is empty
	void printTreeInOrder() const; // print tree in order
	void printTreePreOrder() const; // print tree pre order
	void drawTree() const; // draw the tree to a file
	void makeEmpty(); // helping destructor, deleting every node
	void insert(const Comparable & x); // inserting new node
	void remove(std::string x); // removing a node
	void isTreeBalanced(); // Check if tree is balanced
	void numberOfsides(); // Check the number of sides
	const AvlTree & operator=(const AvlTree & rhs); // overloading = operator for copying
	
private:
	
	AvlNode<Comparable> *root;

	const Comparable ITEM_NOT_FOUND;

	const Comparable & elementAt(AvlNode<Comparable> *t) const; 

	void insert(const Comparable & x, AvlNode<Comparable> * & t) const; // internal insert method
	void remove(std::string x, AvlNode<Comparable> * & t) const; // internal remove method

	AvlNode<Comparable> * findMin(AvlNode<Comparable> *t) const; 
	AvlNode<Comparable> * findMax(AvlNode<Comparable> *t) const; 
	AvlNode<Comparable> * find(std::string _name, AvlNode<Comparable> *t) const; // finding a key or partial key

	void findHelper(std::string _name, AvlNode<Comparable> *t) const; // helping to the find method

	void makeEmpty(AvlNode<Comparable> * & t) const; // deleting every node, helping constructor
	void printTree(AvlNode<Comparable> *t) const; // Print tree to a file
	AvlNode<Comparable> * clone(AvlNode<Comparable> *t) const; // copying a tree
	void InOrderAVL(AvlNode<Comparable> * tree, std::ostream &OUT) const; // print to a file in order
	void PreOrderAVL(AvlNode<Comparable> * tree, std::ostream &OUT) const; // print to a file pre order
	void DrawTree(AvlNode<Comparable> * tree, AvlNode<Comparable> * rt, std::ostream &OUT, std::string p) const; // draw tree to a file
	
	// Avl manipulations
	int height(AvlNode<Comparable> *t) const; // calculates height
	int max(int lhs, int rhs) const; 
	void rotateWithLeftChild(AvlNode<Comparable> * & k2) const; 
	void rotateWithRightChild(AvlNode<Comparable> * & k1) const; 
	void doubleWithLeftChild(AvlNode<Comparable> * & k3) const; 
	void doubleWithRightChild(AvlNode<Comparable> * & k1) const; 

};


#include "AVL.cpp"

#endif