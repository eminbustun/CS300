// Bulent Emin Ustun - 27822
#pragma once
#ifndef HP_H
#define HP_H

#include <vector>
#include <string>

using namespace std;

template <class HashedObj>
class HashTable
{
public:
	explicit HashTable(const HashedObj &notFound, int size = 53); // constructor

    void clearAll(); // clear the vector

    void insert(const HashedObj &x); // insert a contact

	void search(const std::string & str); // searching for a contact

	void deleteContact(const std::string & str); // deleting a contact

    void searchTIMING(const std::string & str); // I wrote it for timing of the search function

    void status(); // print the status
  

    enum EntryType
    {
        ACTIVE,
        EMPTY,
        DELETED
    };

private:

    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj &e = HashedObj(),
                  EntryType i = EMPTY)
            : element(e), info(i) {}
    };
	
    vector<HashEntry> array; 
    int currentSize;
    const HashedObj ITEM_NOT_FOUND;


	int searchHelper(const std::string & str); // hepling the search function
    bool isActive(int currentPos) const; // check if the position is active or not
    int findPos(const HashedObj &x) const; // find the position of an object
    void rehash(); // rehashing when the load factor bigger than or equal to 0.80(current size / array size)
    void rehashForDeleting();
};


int hashHP (const string & key, int tableSize); // hash function

#include "HP.cpp"

#endif
