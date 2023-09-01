/*
  Author: Daniel Kopta and ??
  July 2017
  
  CS 6010 Fall 2019
  Vector util library definitions
  Complete the functions defined in this file.
  Some basic tests for your library are provided in VectorTest.cpp.
  Compile the tests together with your library using the following command:
  clang++ -std=c++11 VectorTest.cpp VectorUtil.cpp
  Most of the provided tests will fail until you have provided correct 
  implementations for the VectorUtil library functions.
  You will need to provide more thorough tests.
*/
#include<iostream>
#include "VectorUtil.h"
/*
 * Determines whether or not a vector contains a certain item.
 *
 * Parameters:
 *   input -- The vector to search
 *   lookFor -- The item to look for
 *
 * Returns:
 *   Whether or not the item is contained in the vector
 */
bool Contains( vector<int> input, int lookFor )
{
    for (int i : input){
        if (i == lookFor){
            return true;
        }
    }
        return false;
    }


/*
 * Determines the minimum value in a vector.
 *
 * Assumes the vector is non-empty.
 *
 * Parameters:
 *   input -- A vector of integers
 *
 * Returns:
 *   The smallest item in the vector
 */
int FindMin( vector<int> input )
{
    if(input.size()==0){
        return -1;
    }
    
    int min = input[0];
    for (int i=1; i<input.size()-1; i++){ 
        if (input[i] < min){
            min = input[i];
        }
    }
    return min;
}

/*
 * Determines the maximum value in a vector.
 *
 * Assumes the vector is non-empty
 *
 * Parameters:
 *   input -- A vector of integers
 *
 * Returns:
 *   The largest item in the vector
 */
    
int FindMax( vector<int> input )
{
    if(input.size()==0){
        return -1;
    }
    int max = input[0];
    for (int i=1; i<input.size()-1; i++){
        if (input[i] > max){
            max = input[i];
        }
    }
    
  return max;
}

/*
 * Determines the average of all values in a vector
 *
 * Assumes the vector is non-empty
 *
 * Parameters:
 *   input -- A vector of integers
 *
 * Returns:
 *   The (integer) average of all values in the vector
 */
int Average( vector<int> input )
{
    if(input.size()==0){
        return -1;
    }
    int sum = 0, avg = 0;
    for (int i : input){
        sum += i;
    }
    avg = sum / input.size();
  return avg;
}


/*
 * Determines whether or not the items in a vector are in non-descending order
 *
 * Non-descending order is similar to ascending order, except that it allows for 
 * duplicate items to appear next to each other.
 * i.e., no item appearing at a lower index than another item is greater than that
 * other item.
 * 
 * Examples:
 *  {1, 2, 2, 15, 70} is sorted
 *  {2, 3, 0} is not sorted
 *
 * Parameters:
 *   input -- A vector of integers
 *
 * Returns:
 *   True if the vector is sorted in non-descending order, false otherwise
 *   An empty vector is considered sorted, since there are no items out of order
 *   A single-item vector is considered sorted, since there are no items out of order
 */
bool IsSorted( vector<int> input )
{
    if(input.size()==0){
        return false;
    }
    
    for (int i=0; i < input.size()-1; i++){
        if (input[i] > input[i+1]){
            return false;
        }
    }
  return true;
}
