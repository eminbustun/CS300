// Bulent Emin Ustun - 27822
#include "BST.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

/*
 * Construct the tree.
 */
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable &notFound) : ITEM_NOT_FOUND(notFound), root(nullptr) {}

/*
 Check the tree if it is empty
*/
template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const
{ // I wrote it myself

	if (root == nullptr)
		return true;

	else
		return false;
}

/*
 * Internal method to get element field in node t.
 * Return the element field or ITEM_NOT_FOUND if t is NULL.
 */
template <class Comparable>
const Comparable &BinarySearchTree<Comparable>::elementAt(BinaryNode<Comparable> *t) const
{ // if t is equal to NULL, print ITEM_NOT_FOUND, else print t->element

	return t == nullptr ? ITEM_NOT_FOUND : t->element;
}

/*
 * Find item x in the tree.
 * Return the matching item or ITEM_NOT_FOUND if not found.
 */
template <class Comparable>
const Comparable &BinarySearchTree<Comparable>::find(const std::string & x) const
{

	return elementAt(find(x, root));
}

/*
Helping to the find function.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::findHelper(const std::string & _name, BinaryNode<Comparable> *t) const
{

	if (t != NULL)
	{

		std::string fulName = t->element.name + " " + t->element.surname;

		if (fulName.find(_name) == 0)
		{
			std::cout << t->element.name + " " + t->element.surname + " " + t->element.number + " " + t->element.city << std::endl;
		}

		findHelper(_name, t->left);
		findHelper(_name, t->right);
	}

	
}

/*
 * Internal method to find an item in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 * Return node containing the matched item.
 * In Trees1.ppt slide page 86, there is another find that is not recursive.
 */

/*
We go through the tree to find our name (or partial name). when we find some name starting with our search parameter, we go though helper function since
we find some name starts with our search parameter. We start to compare our search parameter with that nodes left and rights in a pre order way.
*/

template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::find(const std::string & _name, BinaryNode<Comparable> *t) const
{

	if (t == nullptr)
	{	
		std::cout <<"Name not found!" << std::endl;
		return nullptr;

	}

	std::string fulName = t->element.name + " " + t->element.surname;

	if (t != nullptr)
	{

		if (fulName.find(_name) == 0)
		{
			findHelper(_name, t);
		}

		else
		{
			if (_name < t->element.name + " " + t->element.surname)
			{
				std::string fulName = t->element.name + " " + t->element.surname;

				return find(_name, t->left);
			}
			else
			{
				std::string fulName = t->element.name + " " + t->element.surname;
				return find(_name, t->right);
			}
		}
	}
}

/*
 * Find the smallest item in the tree.
 * Return smallest item or ITEM_NOT_FOUND if empty.
 */
template <class Comparable>
const Comparable &BinarySearchTree<Comparable>::findMin() const
{
	return elementAt(findMin(root));
}

/*
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable> *t) const
{

	if (t == nullptr)
		return nullptr;

	if (t->left == nullptr)
		return t;

	return findMin(t->left);
}

/*
 * Find the smallest item in the tree.
 * Return smallest item or ITEM_NOT_FOUND if empty.
 */
template <class Comparable>
const Comparable &BinarySearchTree<Comparable>::findMax() const
{

	return elementAt(findMax(root));
}

/*
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMax(BinaryNode<Comparable> *t) const
{

	if (t == nullptr)
		return nullptr;

	if (t->right == nullptr)
		return t;

	return findMax(t->right);

	/*

	if( t != NULL )
	while( t->right != NULL ) // this is non-recursive version.
	t = t->right;
	return t;


	*/
}

template <class Comparable>
int BinarySearchTree<Comparable>::height(BinaryNode<Comparable> *t) const
{
	if (t == NULL)
		return -1;

	return t->height;
}

/*
 * Insert x into the tree; duplicates are ignored.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x)
{

	insert(x, root);
}

/*
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x, BinaryNode<Comparable> *&t) const

{

	if (t == nullptr) //  create a new node at the right place
		t = new BinaryNode<Comparable>(x, nullptr, nullptr);
	else if (x.name + " " + x.surname < t->element.name + " " + t->element.surname)
		insert(x, t->left); // go left if x is smaller than t
	else if (t->element.name + " " + t->element.surname < x.name + " " + x.surname)
		insert(x, t->right); // go right if x is bigger than t
	else
		;

	t->height = max(height(t->left), height(t->right)) + 1; // update the tree height.
}

template <class Comparable>
int BinarySearchTree<Comparable>::max(int lhs, int rhs) const
{
	if (lhs > rhs)
		return lhs;

	return rhs;
}
/*
 * Remove x from the tree. Nothing is done if x is not found.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::remove(const std::string & x)
{

	remove(x, root);
}




/*
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the tree.
 * Set the new root.
 */
int global_variable_is_in_tree; // This global variable returns -1 if what we are deleting is not in the tree.
template <class Comparable>
void BinarySearchTree<Comparable>::remove(const std::string & x, BinaryNode<Comparable> *&t) const
{

	if (t == nullptr)
	{
		std::cout << "Not Found" << std::endl;
		global_variable_is_in_tree = -1;
		return; // Item not found; do nothing
	}

	if (x < t->element.name + " " + t->element.surname)
		remove(x, t->left);

	else if (t->element.name + " " + t->element.surname < x)
		remove(x, t->right);

	else if (t->left != nullptr && t->right != nullptr) // Two children
	{
		t->element = findMin(t->right)->element;
		remove(t->element.name + " " + t->element.surname, t->right);
	}
	else // one or no children
	{
		BinaryNode<Comparable> *oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right; // if t->left is not NULL, then make t = t->left, else make t = t->right
		std::cout << "Deleted successfully . . ." << std::endl;
		delete oldNode;
	}
}



/*
 * Make the tree logically empty.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{

	makeEmpty(root);
}

/*
 * Internal method to make subtree empty.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode<Comparable> *&t) const
{
	if (t != nullptr)
	{

		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}

	t = nullptr;
}


/*
 * Destructor for the tree.
 */
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{

	makeEmpty();
}

/*
 * Copy constructor.
 */
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree<Comparable> &rhs) : root(NULL), ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND)
{

	*this = rhs;
}

/**
 * Internal method to clone subtree.
 */
template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::clone(BinaryNode<Comparable> *t) const
{

	if (t == NULL)
		return NULL;

	else
		return new BinaryNode<Comparable>(t->element, clone(t->left), clone(t->right));
}




template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findTIMING(const std::string & _name, BinaryNode<Comparable> *t) const
{

	if (t == nullptr)
	{	
		
		return nullptr;

	}

	std::string fulName = t->element.name + " " + t->element.surname;

	if (t != nullptr)
	{

		if (fulName.find(_name) == 0)
		{
			return nullptr;
		}

		else
		{
			if (_name < t->element.name + " " + t->element.surname)
			{
				std::string fulName = t->element.name + " " + t->element.surname;

				return findTIMING(_name, t->left);
			}
			else
			{
				std::string fulName = t->element.name + " " + t->element.surname;
				return findTIMING(_name, t->right);
			}
		}
	}
}


template <class Comparable>
void BinarySearchTree<Comparable>::findHelperTIMING(const std::string & _name, BinaryNode<Comparable> *t) const
{

	if (t != NULL)
	{

		std::string fulName = t->element.name + " " + t->element.surname;

		if (fulName.find(_name) == 0)
		{
			return;
		}

		findHelperTIMING(_name, t->left);
		findHelperTIMING(_name, t->right);
	}

	
}


template <class Comparable>
const Comparable &BinarySearchTree<Comparable>::findTIMING(const std::string & x) const
{

	return elementAt(findTIMING(x, root));
}