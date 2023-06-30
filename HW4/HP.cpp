// Bulent Emin Ustun - 27822
#include "HP.h"
#include <iostream>
// #include <string>
#include <cmath>
/*
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

/*
 * Internal method to return a prime number
 * at least as large as n.  Assumes n > 0.
 */
int nextPrime(int n)
{
    if (n % 2 == 0)
        n++;

    for (; !isPrime(n); n += 2)
        ;

    return n;
}

/*
 * Construct the hash table.
 */
template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj &notFound, int size) : ITEM_NOT_FOUND(notFound), array(nextPrime(size))
{
    currentSize = 0;
}

/*
Clearing the array.
*/
template <class HashedObj>
void HashTable<HashedObj>::clearAll()
{

    while (array.size() != 0)
    {

        array.pop_back();
    }
}

/*
 * Method that performs quadratic probing resolution.
 * Return the position where the search for x terminates.
 */
template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj &x) const
{
    int collisionNum = 0;
    int currentPos = hashHP(x.name + x.surname, array.size());

    while (array[currentPos].info != EMPTY && array[currentPos].element != x)
    {
        currentPos += pow(++collisionNum, 2); // add the difference
        while (currentPos >= array.size())    // perform the mod
            currentPos -= array.size();       // if necessary
    }
    return currentPos;
}

/*
 * Return true if currentPos exists and is active.
 */
template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}



/*
 * Insert item x into the hash table. If the item is
 * already present, then do nothing.
 */
template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj &x)
{
    // Insert x as active
    int currentPos = findPos(x);

    if (isActive(currentPos))
        return; // if the current position is active, return

    array[currentPos] = HashEntry(x, ACTIVE); 

    currentSize++;

    double loadFactor = double(currentSize) / array.size(); // load factor

    // enlarge the hash table if necessary
    if (loadFactor >= 0.90)
        rehash(); // rehash as soon as the table gets  0.80 full
}

/*
 * Expand the hash table.
 */
template <class HashedObj>
void HashTable<HashedObj>::rehash()
{
    std::cout << "rehashed..." << std::endl;
    std::cout << "previous table size: " << array.size() << ", ";

    vector<HashEntry> oldArray = array;

    // Create new double-sized, empty table
    array.resize(nextPrime(2 * oldArray.size())); 
    for (int j = 0; j < array.size(); j++)
        array[j].info = EMPTY;

    // Copy table over
    currentSize = 0;
    for (int i = 0; i < oldArray.size(); i++)
        if (oldArray[i].info == ACTIVE)
            insert(oldArray[i].element);

    double loadFactor = double(currentSize) / array.size();
    std::cout << "new table size: " << array.size() << ", current unique item count: " << currentSize << ", current load factor: " << loadFactor << std::endl;
}

/*
Prints the status of unique word count and current load.
*/
template <class HashedObj>
void HashTable<HashedObj>::status()
{
    double loadFactor = double(currentSize) / array.size();
    std::cout << "After preprocessing, the unique word count is " << currentSize << ". Current load ratio is " << loadFactor << std::endl;
}


/*
Find the position of a searched contact.
If the position is not Empty, implementing probing
*/
template <class HashedObj>
int HashTable<HashedObj>::searchHelper(const std::string & str)
{

    int collisionNum = 0;
    int currentPos = hashHP(str, array.size());

    while (array[currentPos].info != EMPTY && (array[currentPos].element.name + array[currentPos].element.surname) != str)
    {
        currentPos += pow(++collisionNum, 2); // add the difference
        while (currentPos >= array.size())
        { 
            currentPos -= array.size();
           
        }
    }
    return currentPos;
}


/*
Search for a contact.
First find the position, if it exists prints the name, surname, telNo and city. If it does not exist it prints "Name not found!"
*/
template <class HashedObj>
void HashTable<HashedObj>::search(const std::string & str)
{

    int currentPos = searchHelper(str);

    if (isActive(currentPos))
    {
        std::cout << array[currentPos].element.name + " " + array[currentPos].element.surname + " " + array[currentPos].element.number + " " + array[currentPos].element.city << std::endl;
    }
    else
    {
        std::cout << "Name not found!" << std::endl;
    }
}

/*
Deletes a contact.
Firstly searching the position, then change info to DELETED. 
*/
template <class HashedObj>
void HashTable<HashedObj>::deleteContact(const std::string & str)
{

    int currentPos = searchHelper(str);
    if (isActive(currentPos)){
        array[currentPos].info = DELETED;
        currentSize--;
    }

    double loadFactor = double(currentSize) / array.size();

    if (loadFactor <= 0.29){
        rehashForDeleting();

    }

}


template<class HashedObj>
void HashTable<HashedObj>::rehashForDeleting()
{

    

    vector<HashEntry> oldArray = array;

    // Create new double-sized, empty table
    array.resize(nextPrime(2 * currentSize)); 
    for (int j = 0; j < array.size(); j++)
        array[j].info = EMPTY;

    // Copy table over
    currentSize = 0;
    for (int i = 0; i < oldArray.size(); i++)
        if (oldArray[i].info == ACTIVE)
            insert(oldArray[i].element);

   

}



/*
Helps searchTIMING function to count 500 times the search function
*/
template <class HashedObj>
void HashTable<HashedObj>::searchTIMING(const std::string & str)
{

    int currentPos = searchHelper(str);

    if (isActive(currentPos))
    {
        return;
    }
    else
    {
        return;
    }
}

/*
Hash function for strings. Faster than thhe below implementation.
*/

int hashHP(const std::string &key, int tableSize)
 {
     int num = 0;

    for(int i = 0; i < key.length(); i++){
        
         num = (num * 7 + key[i]) % tableSize;

     }

     return (num);

}

/*
int hashHP(const std::string &key, int tableSize) 
{
    int num = 0;

    for (int i = 0; i < key.length(); i++)
    {
        num = num + key[i];
    }

    return (num % tableSize);
}
*/

