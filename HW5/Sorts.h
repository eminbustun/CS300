#pragma once
#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <iostream>

using namespace std;

template <class Comparable>
class Sorts
{

public:


    void insertionSort(vector<Comparable> &a)
    {
        int j;
        // loop over the passes
        for (int p = 1; p < a.size(); p++)
        {
            Comparable tmp = a[p];
            // loop over the elements
            for (j = p; j > 0 && ((tmp.name + " " + tmp.surname) < (a[j - 1].name + " " + a[j - 1].surname)); j--)
                a[j] = a[j - 1];
            a[j] = tmp;
        }
    }
    void heapsort(vector<Comparable> &a)
    {
        // buildHeap
        for (int i = a.size() / 2; i >= 0; i--)
            percDown(a, i, a.size());

        // sort
        for (int j = a.size() - 1; j > 0; j--)
        {
            swapping(a[0], a[j]); // swap max to the last pos.
            percDown(a, 0, j);    // re-form the heap
        }
    }

    void mergeSort(vector<Comparable> &a)
    {

        mergeSortMine(a, 0, a.size() - 1);
    }

    /**
     * Quicksort algorithm (driver).
     */

    void quicksort(vector<Comparable> &a)
    {
        quicksort(a, 0, a.size() - 1);
    }

private:
    inline void swapping(Comparable &obj1, Comparable &obj2)
    {
        Comparable tmp = obj1;
        obj1 = obj2;
        obj2 = tmp;
    }

    inline int leftChild(int i)
    {
        return 2 * i + 1;
    }

    // for deleteMax
    // a is the array, i is the position to percolate down from
    // n is the logical size of the array
    void percDown(vector<Comparable> &a, int i, int n)
    {
        int child;
        Comparable tmp;

        for (tmp = a[i]; leftChild(i) < n; i = child)
        {
            child = leftChild(i);
            if (child != n - 1 && ((a[child].name + " " + a[child].surname) < (a[child + 1].name + " " + a[child + 1].surname)))
                child++;
            if (a[child].name + a[child].surname > tmp.name + tmp.surname)
                a[i] = a[child];
            else
                break;
        }
        a[i] = tmp;
    }

    void mergeSortMine(vector<Comparable> &a, int left, int right)
    {
        if (left < right)
        {
            int center = (left + right) / 2;
            mergeSortMine(a, left, center);
            mergeSortMine(a, center + 1, right);
            mergeSortHelper(a, left, center + 1, right);
        }
    }

    /**
     * a is an array of Comparable items.
     * leftPos is the left-most index of the subarray.
     * rightPos is the index of the start of the second half.
     * rightEnd is the right-most index of the subarray.
     * 
     * I developed this code by looking old merge sort algorithm (From Gulsen Hoca) that uses extra memory and explanation videos of in place merge sort.s
     * 
     */

    void mergeSortHelper(vector<Comparable> &a, int leftPos, int rightPos, int rightEnd)
    {
        // rightEnd = last element of the second array
        // rightPos = first element of the second array
        // leftPos = first element of the first array
        // leftEnd = last element of the second array

        int leftEnd = rightPos - 1;

        int tmpPos = leftPos;

        int numElements = rightEnd - leftPos + 1;

        // Main loop
        while (leftPos <= leftEnd && rightPos <= rightEnd)
            if (a[leftPos].name + " " + a[leftPos].surname <= a[rightPos].name + " " + a[rightPos].surname)
            {
                leftPos++;
            }
            else if (a[leftPos].name + " " + a[leftPos].surname > a[rightPos].name + " " + a[rightPos].surname)
            {
                int tracker = rightPos;
                Comparable tmpNUM = a[rightPos]; // temporary holder for not losing the value
                for (; tracker > leftPos && (tracker >= 0);)
                {

                    a[tracker] = a[tracker - 1]; // move elements to the right
                    tracker--;
                }

                a[leftPos] = tmpNUM; // temporary value is given back to the place

                rightPos++;
                leftPos++;
                leftEnd++;
            }
    }

    /** Return median of left, center, and right.
     *   Order these and hide the pivot.
     */

    const Comparable &median3(vector<Comparable> &a, int left, int right)
    {
        int center = (left + right) / 2;
        if (a[center].name + " " + a[center].surname < a[left].name + " " + a[left].surname)
            swapping(a[left], a[center]);
        if (a[right].name + " " + a[right].surname < a[left].name + " " + a[left].surname)
            swapping(a[left], a[right]);
        if (a[right].name + " " + a[right].surname < a[center].name + " " + a[center].surname)
            swapping(a[center], a[right]);

        // Place pivot at position right - 1
        swapping(a[center], a[right - 1]);
        return a[right - 1];
    }

    /**
     * Internal insertion sort routine for subarrays
     * that is used by quicksort.
     * a is an array of Comparable items.
     * left is the left-most index of the subarray.
     * right is the right-most index of the subarray.
     */

    void insertionSort(vector<Comparable> &a, int left, int right)
    {
        for (int p = left + 1; p <= right; p++)
        {
            Comparable tmp = a[p];
            int j;

            for (j = p; j > left && ((tmp.name + " " + tmp.surname) < (a[j - 1].name + " " + a[j - 1].surname)); j--)
                a[j] = a[j - 1];
            a[j] = tmp;
        }
    }

    /**
     * Internal quicksort method that makes recursive calls.
     * Uses median-of-three partitioning and a cutoff of 10.
     * a is an array of Comparable items.
     * left is the left-most index of the subarray.
     * right is the right-most index of the subarray.
     */

    void quicksort(vector<Comparable> &a, int left, int right)
    {
        if (left + 10 <= right)
        {
            Comparable pivot = median3(a, left, right);
            // Begin partitioning
            int i = left, j = right - 1;
            for (;;)
            {
                while (a[++i].name + " " + a[i].surname < pivot.name + " " + pivot.surname)
                {
                }

                while (pivot.name + " " + pivot.surname < a[--j].name + " " + a[j].surname)
                {
                }

                if (i < j)
                    swapping(a[i], a[j]);
                else
                    break;
            }
            swapping(a[i], a[right - 1]); // Restore pivot

            quicksort(a, left, i - 1);  // Sort small elements
            quicksort(a, i + 1, right); // Sort large elements
        }
        else // Do an insertion sort on the subarray
            insertionSort(a, left, right);
    }
};

#endif /*SORTS_H*/