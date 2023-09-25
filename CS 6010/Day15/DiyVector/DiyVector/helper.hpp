//
//  helper.hpp
//  DiyVector
//
//  Created by Tailang  Cao on 9/12/23.
//

#ifndef helper_hpp
#define helper_hpp
#include <iostream>

#include <stdio.h>
struct myVector {
    int * data;
    size_t size;
    size_t capacity;
};

myVector makeVector(int initialCapacity);
void freeVector(myVector MyVec);
void pushBack(myVector &MyVec, int newData);
int popBack(myVector &MyVec);
int get(myVector MyVec, int index);
void set(myVector &MyVec, int index, int newValue);
void growVector(myVector &MyVec);

#endif /* helper_hpp */
