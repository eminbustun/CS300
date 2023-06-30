// Bulent Emin Ustun - 27822
#include "AVL.h"
#include <iostream>
#include <chrono>

/*
* Construct the tree.
*/
template <class Comparable>
AvlTree<Comparable>::AvlTree(const Comparable & notFound):ITEM_NOT_FOUND(notFound), root(nullptr){}


/*
* Check if the tree is balanced adn report it
*/
template <class Comparable>
void AvlTree<Comparable>::isTreeBalanced()
{
	if (abs(root->right->height - root->left->height) <= 1){
		std::cout << "The tree is balanced." << std::endl;
	}
	else {
		std::cout << "The tree is not balanced." << std::endl;
	}
}

/*
* Calculates the number of sides
*/
template <class Comparable>
void AvlTree<Comparable>::numberOfsides()
{

	std::cout << "The heights of AVL are for left: " << root->left->height + 1 << " and right: " << 
		root->right->height + 1 << std::endl;

}


/*
* Return the height of node t, or -1, if NULL.
*/
template <class Comparable>
int AvlTree<Comparable>::height(AvlNode<Comparable> *t) const
{
	if (t == NULL)
		return -1;

	return t->height;
}


/*
* Return maximum of lhs and rhs.
*/
template <class Comparable>
int AvlTree<Comparable>::max(int lhs, int rhs) const
{
	if (lhs > rhs)
		return lhs;

	return rhs;            
}

/*
* Insert x into the tree; duplicates are ignored.
*/
template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable & x){

	insert(x, root);
}



/*
* Inserting a node to a tree, however, it should balance it for protecting the AVL Tree feature which is difference of height of root->left and root->right
* must be smaller than 2
*/
template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable & x, AvlNode<Comparable> * & t) const
{
	if ( t == NULL )
		t = new AvlNode<Comparable>( x, NULL, NULL );

	else if ( x.name + " " + x.surname < t->element.name + " "+ t->element.surname ) {
		// X should be inserted to the left tree!
		insert( x, t->left );

		// Check if the left tree is out of balance (left subtree grew in height!)
		if ( height( t->left ) - height( t->right ) == 2 )
			if ( x.name + " " + x.surname < t->left->element.name + " " + t->left->element.surname )  // X was inserted to the left-left subtree!
				rotateWithLeftChild( t );
			else			     // X was inserted to the left-right subtree!
				doubleWithLeftChild( t );
	}

	else if( t->element.name + " " + t->element.surname < x.name + " " + x.surname )
	{    // Otherwise X is inserted to the right subtree
		insert( x, t->right );
		if ( height( t->right ) - height( t->left ) == 2 )
			// height of the right subtree increased
				if ( t->right->element.name +" " + t->right->element.surname  < x.name + " " + x.surname )
					// X was inserted to right-right subtree
						rotateWithRightChild( t );
				else // X was inserted to right-left subtree
					doubleWithRightChild( t );
	}
	else
		;  // Duplicate; do nothing

	// update the height the node
	t->height = max( height( t->left ), height( t->right ) ) + 1;
}


///////////////////////////////////////////////////////////////////////////////////////
/*
* Rotate binary tree node with left child.
* For AVL trees, this is a single rotation for case 1.
* Update heights, then set new root.
* There is more on slides.
*/
template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(AvlNode<Comparable> * & k2) const
{
	AvlNode<Comparable> *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->left ), k2->height ) + 1;
	k2 = k1;
}



/*
* Rotate binary tree node with right child.
* For AVL trees, this is a single rotation for case 4.
* Update heights, then set new root.
*/
template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild(AvlNode<Comparable> * & k1) const
{
	AvlNode<Comparable> *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
	k2->height = max( height( k2->right ), k1->height ) + 1;
	k1 = k2;
}


/*
* Double rotate binary tree node: first left child.
* with its right child; then node k3 with new left child.
* For AVL trees, this is a double rotation for case 2.
* Update heights, then set new root.
*/
template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const
{
	rotateWithRightChild( k3->left );
	rotateWithLeftChild( k3 );
}


/*
* Double rotate binary tree node: first right child.
* with its left child; then node k1 with new right child.
* For AVL trees, this is a double rotation for case 3.
* Update heights, then set new root.
*/
template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild( AvlNode<Comparable> * & k1 ) const
{
	rotateWithLeftChild( k1->right );
	rotateWithRightChild( k1 );
}

///////////////////////////////////////////////////////////////////////////////////////

/*
* Removing a node
*/
template<class Comparable>
void AvlTree<Comparable>::remove(std::string x)
{

	remove(x,root);



}

/*
Internal remove function, working recursively.
not sure if it is working correctly.
*/
template<class Comparable>
void AvlTree<Comparable>::remove(std::string x, AvlNode<Comparable> * & t) const
{
	
	if (t == nullptr){
		 // If the node we are looking for is not in tree print this.
		
		return;
	}

	else if (x < t->element.name + " " + t->element.surname){ 

		remove(x, t->left);

		if ( height( t->left ) - height( t->right ) == -2 ){ // when there is no t->left, the height of t->left will be -1 (check height function)
															 // so, there is a node in t->right, therefore, -1 - (+1) = -2

			if ( t->right && (height( t->right->left ) - height( t->right->right)) >= 0  ){  // for cases such as   10
																							 //                      \
																							 //                      70
																							 //                      /
																							 //                     60   

				doubleWithRightChild( t );

			}

			else  {			     															// For such cases as   70
																						    //                      \
																			                //                       80
																							//                         \
																							//                          90
				rotateWithRightChild( t );
			}
			t->height = max( height( t->left ), height( t->right ) ) + 1; // update the height the node when we balance the node.
		}
		
	}

	else if (x > t->element.name + " " + t->element.surname){

		remove(x, t->right);

		if ( height( t->left ) - height( t->right ) == 2 ){ // when there is no t->right, the height of t->right will be -1 (check height function)
															 // so, there is a node in t->left, therefore, +1 - (-1) = 2
			
			if ( t->left && (height( t->left->left ) - height( t->left->right )) <= 0){ // for such cases as   50
																						//                    /
																						//                   20
																						//                  /  \
																						//                 10   30 
				
				doubleWithLeftChild( t );
			}

			else{ 																		// for such cases as    80
																						//                     /
																						//                    50
																						//                    /
																						//                   10

				rotateWithLeftChild( t );
			}

			t->height = max( height( t->left ), height( t->right ) ) + 1; // update the height the node when we balance the node.
		}
		
	}

	// if x is equal to t we are going below for deleting the node. Then we will go above for balancing the tree to protect the AVL tree feature.


	else if (t->left != nullptr && t->right != nullptr) { // two children

		t->element = findMin(t->right)->element;
		remove(t->element.name + " " + t->element.surname, t->right);


	}

	else // one or no children
	{
		AvlNode<Comparable> *oldNode = t;
		t = ( t->left != nullptr ) ? t->left : t->right; // if t->left is not NULL, then make t = t->left, else make t = t->right
		delete oldNode;

	}

	if (t){
		t->height = max( height( t->left ), height( t->right ) ) + 1; // update the height the node
	}

	
}


/*
* Internal method to get element field in node t.
* Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template <class Comparable>
const Comparable & AvlTree<Comparable>::elementAt(AvlNode<Comparable> *t) const{ // if t is equal to NULL, print ITEM_NOT_FOUND, else print t->element

	return t == nullptr ? ITEM_NOT_FOUND : t->element;
}

/*
* Find item x in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template <class Comparable>
const Comparable & AvlTree<Comparable>::find(std::string x) const{

	return elementAt(find(x, root));
}


/*
* Helper function of find
*/
template <class Comparable>
void AvlTree<Comparable>::findHelper(std::string _name, AvlNode<Comparable> *t) const
{

	if (t!=NULL){



		std::string fulName = t->element.name +" " + t->element.surname;

		if (fulName.find(_name) == 0){
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
template <class Comparable>
AvlNode<Comparable> *AvlTree<Comparable>::find(std::string _name, AvlNode<Comparable> * t) const{


	if (t == nullptr){
		return nullptr;
	}

	std::string fulName = t->element.name +" " + t->element.surname;

	if (t != nullptr) {

		if (fulName.find(_name) == 0){ // if we find something that involves our _name in their beginning, go the to helper function to traverse the rest of the words starts with _name
			findHelper(_name, t);
		}

		else{
			if(_name < t->element.name +" " +t->element.surname){
				std::string fulName = t->element.name + " " + t->element.surname;
				
				return find(_name, t->left);
			}
			else{
				std::string fulName = t->element.name +" " + t->element.surname;
				
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
const Comparable & AvlTree<Comparable>::findMin() const
{
	return elementAt(findMin(root));
}


/*
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template <class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::findMin(AvlNode<Comparable> *t) const{

	if(t == nullptr)
		return nullptr;

	if(t->left == nullptr)
		return t;

	return findMin(t->left);

}



/*
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable>
const Comparable & AvlTree<Comparable>::findMax() const{

	return elementAt(findMax(root));

}



/*
* Internal method to find the largest item in a subtree t.
* Return node containing the largest item.
*/
template<class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::findMax(AvlNode<Comparable> *t) const{

	if (t == nullptr)
		return nullptr;

	if (t->right == nullptr)
		return t;

	return findMax(t->right);

}


template <class Comparable>
void AvlTree<Comparable>::makeEmpty(){

	makeEmpty(root);
}


template<class Comparable>
bool AvlTree<Comparable>::isEmpty() const{ // Check if root is empty

	if(root == nullptr)
		return true;

	else 
		return false;

}


/*
* Internal method to make subtree empty.
*/
template <class Comparable>
void AvlTree<Comparable>::makeEmpty(AvlNode<Comparable> * & t) const
{
	if( t != nullptr ){

		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}

	t = nullptr;
}



/*
* Print the tree contents in sorted order.
*/
template <class Comparable>
void AvlTree<Comparable>::printTreeInOrder() const
{
	if(isEmpty())
		std::cout << "Empty tree" << std::endl;

	else{
		
		std::ofstream OUT2("phonebookInOrderAVL.txt"); 
		auto start = std::chrono::high_resolution_clock::now();
		InOrderAVL(root, OUT2);
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		std::cout << "Printing in order to file from AVL Tree took " << duration.count() <<" milliseconds. . ." << std::endl;

		
	}
}


/*
* Print the tree contents in pre order.
*/
template <class Comparable>
void AvlTree<Comparable>::printTreePreOrder() const
{
	if(isEmpty())
		std::cout << "Empty tree" << std::endl;

	else{
		
		std::ofstream OUTP("phonebookPreOrderAVL.txt");
		auto start = std::chrono::high_resolution_clock::now();
		PreOrderAVL(root, OUTP);
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Printing pre order to file from AVL Tree took " << duration.count() <<" milliseconds. . ." << std::endl;

		
	}
}


template <class Comparable>
void AvlTree<Comparable>::InOrderAVL(AvlNode<Comparable> * tree, std::ostream &OUT) const
{



	if (tree != NULL)
	{
		InOrderAVL( tree->left, OUT );
		OUT << tree->element.name + " " + tree->element.surname + " "+ tree->element.number + " " + tree->element.city << std::endl;
		InOrderAVL( tree->right, OUT );
	}


}

template <class Comparable>
void AvlTree<Comparable>::PreOrderAVL(AvlNode<Comparable> * tree ,std::ostream &OUT) const{


	if (tree != NULL)
	{
		OUT << tree->element.name + " " + tree->element.surname + " "+ tree->element.number + " " + tree->element.city << std::endl;
		PreOrderAVL( tree->left, OUT );
		PreOrderAVL( tree->right, OUT );
	}


}

/*
Copy Constructor
*/
template <class Comparable>
AvlTree<Comparable>::AvlTree(const AvlTree<Comparable> & rhs):root(NULL), ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND){ 

	*this = rhs;
}



/**
* Internal method to clone subtree.
*/
template <class Comparable>
AvlNode<Comparable> *AvlTree<Comparable>::clone( AvlNode<Comparable> * t ) const{

	if (t == NULL)
		return NULL;

	else
		return new AvlNode<Comparable> (t->element, clone( t->left ), clone( t->right ));
}


/*
* Destructor for the tree.
*/
template <class Comparable>
AvlTree<Comparable>::~AvlTree(){

	makeEmpty();
}



template <class Comparable>
void AvlTree<Comparable>::drawTree() const
{
	if (isEmpty())
		std::cout << "Empty tree" << std::endl;

	else {

		std::ofstream OUT2("phonebookTreeAVL.txt");
		DrawTree(root,root,OUT2,"");

	}

}

int TAB_NUMBER2 = 0; // To keep the deepness


template<class Comparable>
void AvlTree<Comparable>::DrawTree(AvlNode<Comparable> * tree,AvlNode<Comparable> * rt, std::ostream & OUTP, std::string p) const
{

	if (tree == NULL)
	{
		return;
	}

	if (tree == rt){
		p = "|__ ";
		
	}


	OUTP <<p << tree->element.name + " " + tree->element.surname << std::endl;
	TAB_NUMBER2++; // getting deep every time
	std::string a = ""; 

	for (int i = 0; i < TAB_NUMBER2; i++)
	{

		a = a + "    |";


	}


	DrawTree(tree->left,rt,OUTP,a+"-- ");


	DrawTree(tree->right,rt,OUTP, a+"__ ");


	TAB_NUMBER2--; // decrease the deep when there is no way to go


}

