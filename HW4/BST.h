// Bulent Emin Ustun - 27822
#pragma once
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H


#include <string>



template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
	Comparable element;
	BinaryNode  *left;
	BinaryNode  *right;
	int        	height;
	BinaryNode( const Comparable & theElement, 
		BinaryNode *lt, BinaryNode *rt , int h = 0) // with this constructor, you can create new binary nodes. Also, you can give the which element you want, you decide the element; and left and right node.
		: element( theElement ), left( lt ), right( rt ), height(h) { }

	friend class BinarySearchTree<Comparable>;
};




template <class Comparable>
class BinarySearchTree
{
public:
	explicit BinarySearchTree(const Comparable & notFound); //  In C++, the explicit keyword is used with a constructor to prevent it from performing implicit conversions. For more information --> https://www.youtube.com/watch?v=Rr1NX1lH3oE
	BinarySearchTree(const BinarySearchTree & rhs); // copy constructor
	~BinarySearchTree(); // destructor

	const Comparable & findMin() const; // find minimum in a BST
	const Comparable & findMax() const; // find maximum in a BST
	const Comparable & find(const std::string & fullNameORpartial) const; // find an element in a BST
	bool isEmpty() const;  // return true if the BST is empty
	
	
	void makeEmpty(); // helps destructor, deleting every node
	void insert(const Comparable & x); // inserting an element to BST
	void remove(const std::string & x); // removing an element from the BST
	
	const Comparable & findTIMING(const std::string & fullNameORpartial) const;
	
	

private:
	BinaryNode<Comparable> *root;
	const Comparable ITEM_NOT_FOUND;
	//bool isThataTree(BinaryNode<Comparable> * rt) const; --> I did not use it
	
	const Comparable & elementAt(BinaryNode<Comparable> *t) const; 

	void insert(const Comparable & x, BinaryNode<Comparable> * & t) const; // we change the structure, that's why we use & * , but not only *, inserting an element
	void remove(const std::string & x, BinaryNode<Comparable> * & t) const;  // find minimum
	BinaryNode<Comparable> * findMin(BinaryNode<Comparable> *t) const; // we do not change the structure, that's why we use only *, but not & *
	BinaryNode<Comparable> * findMax(BinaryNode<Comparable> *t) const; 
	BinaryNode<Comparable> * find(const std::string &_name, BinaryNode<Comparable> *t) const;
	void makeEmpty(BinaryNode<Comparable> * & t) const;
	void findHelper(const std::string &_name, BinaryNode<Comparable> *t) const; // helping to the find function.
	int height(BinaryNode<Comparable> *t) const; // get height of a node
	BinaryNode<Comparable> * clone(BinaryNode<Comparable> *t) const; // copying the tree
	int max(int lhs, int rhs) const; 
	
	BinaryNode<Comparable> * findTIMING(const std::string & _name, BinaryNode<Comparable> *t) const;
	void findHelperTIMING(const std::string & _name, BinaryNode<Comparable> *t) const; // helping to the find function.
	

};


#include "BST.cpp"

#endif /*BINARY_SEARCH_TREE_H*/