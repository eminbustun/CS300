/**
 * Bulent Emin Ustun - 27822
 * 
 * This homework is coded on Visual Studio Code
 * 
 * 
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <fstream>

#include "Sorts.h"
//#include "sorts.cpp"

using namespace std;



/**
 * Struct for keeping contacts
*/
class Contacts{

public:
    std::string name;
    std::string surname;
    std::string number;
    std::string city;
};




string Uppercase(string &); // Uppercase function prototype



/**
 * Sequential Search function
 * 
 * When one of the contact include our searched string, we print the name of this person and make the counter 1. 
 * If the searched string and the contact is the same, break the loop and return counter.
 * If the searched string is not same as the one of the contact, resume searching, if one of the contact include our searched string we print the name of this person and keep going, 
 * otherwise stop the function.
*/
int sequentialSearch(string &searching, vector<Contacts> &contacts)
{

    int counter = 0;
    bool flag = true;

    for (int i = 0; i < contacts.size(); i++)
    {

        if ((contacts[i].name + " " + contacts[i].surname).find(searching) == 0)
        {

            cout << contacts[i].name + " " + contacts[i].surname + " " + contacts[i].number + " " + contacts[i].city << endl;
            counter = 1;
            if ((contacts[i].name + " " + contacts[i].surname) == searching)
            {
                break;
            }

            flag = false; // cheching the for loop
        }

        else if (flag == false)
        {
            break;
        }
    }

    return counter;
}


/**
 * I implemented this function to count the time. Algorithm is the same as sequentialSearch.
*/
int sequentialSearchTIMING(string &searching, vector<Contacts> &contacts)
{

    int counter = 0;
    bool flag = true;
    // searching = Uppercase(searching);

    for (int i = 0; i < contacts.size(); i++)
    {

        if ((contacts[i].name + " " + contacts[i].surname).find(searching) == 0)
        {

            counter = 1;
            if ((contacts[i].name + " " + contacts[i].surname) == searching)
            {
                break;
            }

            flag = false;
        }

        else if (flag == false)
        {
            break;
        }
    }

    return counter;
}



/**
 * Binary search function
 * 
 * if searched element bigger than middle, go to [first, middle - 1]
 * otherwise go to [middle + 1, last],
 * 
 * 
 * When we find our contact in the list, we go down since we want to print the function as an alphabetical order. That's why we decrease center, and when we find the last
 * element that include our searched string, we starts to print the contacts.
 * 
 * However, if the searched string and the contact is exactly the same, it means we found exactly who we want.
*/
int binarySearch(string &searching, vector<Contacts> &contacts)
{

    int counter = 0;
    int first = 0;
    int last = contacts.size() - 1;

    while (first <= last)
    {

        int center = (first + last) / 2; // determining the center

        if ((contacts[center].name + " " + contacts[center].surname).find(searching) == 0) // when contact include our searched string ...
        {

            
            counter = 1;
            if (contacts[center].name + " " + contacts[center].surname == searching) // if searced string and the contact exactly the same, we found it, break the loop . . .
            {
                cout << contacts[center].name + " " + contacts[center].surname + " " + contacts[center].number + " " + contacts[center].city << endl;
                break;
            }

            int center2 = center; 
            
            // go to down until we find the last element that includes our searched string
            while (center2 >= 0 && (contacts[center2].name + " " + contacts[center2].surname).find(searching) == 0)
            {
                center2--;
            }

            center2++; // when we find our searched string, increase by one

            // print as an alphabetical order
            while (center2 >= 0 && (contacts[center2].name + " " + contacts[center2].surname).find(searching) == 0) 
            {
                cout << contacts[center2].name + " " + contacts[center2].surname + " " + contacts[center2].number + " " + contacts[center2].city << endl;
                center2++;
            }

            break;
        }

        else if (contacts[center].name + " " + contacts[center].surname > searching) // if searched < middle
        {

            last = center - 1;
        }

        else if (contacts[center].name + " " + contacts[center].surname < searching) // if searched > middle
        {

            first = center + 1;
        }
    }

    return counter;
}


/**
 * I implemented this function to count the time of binarySearch function.
 * 
 * The algorithm is the same as binarySearch.
*/
int binarySearchTIMING(string &searching, vector<Contacts> &contacts)
{

    // searching = Uppercase(searching);

    int counter = 0;
    int first = 0;
    int last = contacts.size() - 1;

    while (first <= last)
    {

        int center = (first + last) / 2;

        if ((contacts[center].name + " " + contacts[center].surname).find(searching) == 0)
        {

            counter = 1;
            if (contacts[center].name + " " + contacts[center].surname == searching)
            {
                break;
            }

            int center2 = center;

            while (center2 >= 0 && (contacts[center2].name + " " + contacts[center2].surname).find(searching) == 0)
            {
                center2--;
            }

            center2++;
            while (center2 >= 0 && (contacts[center2].name + " " + contacts[center2].surname).find(searching) == 0)
            {
                
                center2++;
            }

            break;
        }

        else if (contacts[center].name + " " + contacts[center].surname > searching)
        {

            last = center - 1;
        }

        else if (contacts[center].name + " " + contacts[center].surname < searching)
        {

            first = center + 1;
        }
    }

    return counter;
}

/**
 * Turn a string to all uppercase letters.
 * 
*/
string Uppercase(string &str){

    int length = str.length();

    for (int k = 0; k < length; k++)
    {

        str[k] = toupper(str[k]);
    }

    return str;
}

// Open 4 vectors for different sorting algorithms

int main()
{

    string fileName;

    cout << "Please enter the contact file name: " << endl;

    getline(cin, fileName);

    fstream inputFile;

    inputFile.open(fileName);

    string line;


    // vectors for different sorting algorithms 
    vector<Contacts> insertionSortedVector;
    vector<Contacts> quickSortedVector;
    vector<Contacts> mergeSortedVector;
    vector<Contacts> heapSortedVector;


    // add contacts to the vectors
    while (getline(inputFile, line))
    {

        Contacts contact;

        string _name, _surname, _number, _city;

        istringstream oneByOne(line);

        oneByOne >> _name >> _surname >> _number >> _city;

        contact.name = Uppercase(_name);
        contact.surname = Uppercase(_surname);
        contact.number = _number;
        contact.city = _city;

        insertionSortedVector.push_back(contact);
        quickSortedVector.push_back(contact);
        mergeSortedVector.push_back(contact);
        heapSortedVector.push_back(contact);
    }

    cin.clear();
   // cin.seekg(0);

    string searching;
    cout << "Please enter the word to be queried: " << endl;
    getline(cin, searching);

    cout << endl
         << "Sorting the vector copies" << endl;
    cout << "==============================" << endl;

    
    Sorts<Contacts> sorting;


    // time of insertion sort
    auto startInsertionSort = std::chrono::high_resolution_clock::now();
    sorting.insertionSort(insertionSortedVector);
    auto timeInsertionSort = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startInsertionSort);

    // time of merge sort
    auto startMergeSort = std::chrono::high_resolution_clock::now();
    sorting.mergeSort(mergeSortedVector);
    auto timeMergeSort = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startMergeSort);

    // time of heap sort
    auto startHeapSort = std::chrono::high_resolution_clock::now();
    sorting.heapsort(heapSortedVector);
    auto timeHeapSort = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startHeapSort);

    // time of quick sort
    auto startQuickSort = std::chrono::high_resolution_clock::now();
    sorting.quicksort(quickSortedVector);
    auto timeQuickSort = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startQuickSort);


    cout << "Quick Sort Time: " << timeQuickSort.count() << " Nanoseconds" << endl;
    cout << "Insertion Sort Time: " << timeInsertionSort.count() << " Nanoseconds" << endl;
    cout << "Merge Sort Time: " << timeMergeSort.count() << " Nanoseconds" << endl;
    cout << "Heap Sort Time: " << timeHeapSort.count() << " Nanoseconds" << endl
         << endl;

    cout << "Searching for " << searching << endl;
    cout << "=================================" << endl;
    searching = Uppercase(searching);

    int binarySearchReturn = binarySearch(searching, insertionSortedVector);

    auto startBinarySearch = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++) // counting the binary search time
    {
        int a = binarySearchTIMING(searching, insertionSortedVector);
    }
    auto timeBinarySearch = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startBinarySearch);

    double timeBS = timeBinarySearch.count() / 100;

    if (binarySearchReturn == 0) // if searched do not exist in the vector
    {
        cout << searching << " does NOT exist in the dataset" << endl;
    }
    cout << endl
         << "Binary Search Time: " << timeBS << " Nanoseconds" << endl
         << endl;
    ;

    cout << "Search results for Sequential Search: " << endl;

    int sequentialSearchReturn = sequentialSearch(searching, insertionSortedVector);

    auto startSequentialSearch = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++) // counting the sequential search time
    {
        int b = sequentialSearchTIMING(searching, insertionSortedVector);
    }
    auto timeSequentialSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startSequentialSearch);

    double timeSS = timeSequentialSearch.count() / 100;

    if (sequentialSearchReturn == 0) // if searched do not exist in the vector
    {
        cout << searching << " does NOT exist in the dataset" << endl;
    }
    cout << endl
         << "Sequential Search Time: " << timeSS << " Nanoseconds" << endl
         << endl;

    cout << "SpeedUp between Search Algorithms" << endl;
    cout << "=====================================" << endl;
    double speedUpSearches = timeSS / timeBS;
    cout << "(Sequential Search / Binary Search) SpeedUp = " << speedUpSearches << endl
         << endl;

    // SpeedUp between Sorting Algorithms
    cout << "SpeedUp between Sorting Algorithms" << endl;
    cout << "======================================" << endl;

    double InsertionOverQuick = double(timeInsertionSort.count()) / timeQuickSort.count();
    double MergeOverQuick = double(timeMergeSort.count()) / timeQuickSort.count();
    double HeapOverQuick = double(timeHeapSort.count()) / timeQuickSort.count();


    // speedUp times of Sorts
    cout << "(Insertion Sort / Quick Sort) SpeedUp = " << InsertionOverQuick << endl;
    cout << "(Merge Sort / Quick Sort) SpeedUp = " << MergeOverQuick << endl;
    cout << "(Heap Sort / Quick Sort) SpeedUp = " << HeapOverQuick << endl << endl;  


    inputFile.close();

    return 0;
}