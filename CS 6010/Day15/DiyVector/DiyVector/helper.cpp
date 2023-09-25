//
//  helper.cpp
//  DiyVector
//
//  Created by Tailang  Cao on 9/12/23.
//

#include "helper.hpp"
#include <iostream>

myVector makeVector(int initialCapacity){
    myVector MyVec;
    MyVec.size = 0;
    MyVec.capacity = initialCapacity;
    MyVec.data = new int;
    return MyVec;
}

void freeVector(myVector MyVec){
    delete [] MyVec.data;
    MyVec.data = nullptr;
    MyVec.size = 0;
    MyVec.capacity = 0;
}

void pushBack(myVector &MyVec, int newData){
    MyVec.data[MyVec.size] = newData;
    MyVec.size += 1;
    if (MyVec.size == MyVec.capacity){
        growVector(MyVec);
    }
}

int popBack(myVector &MyVec){
    int popData = MyVec.data[MyVec.size-1];
    MyVec.size -= 1;
    return popData;
}

int get(myVector MyVec, int index){
    int desNum;
    desNum = MyVec.data[index];
    return  desNum;
}

void set(myVector &MyVec, int index, int newValue){
    MyVec.data[index] = newValue;
}

void growVector(myVector &MyVec){
    int* tempVec = new int [MyVec.capacity*2];
    for(int i =0; i<MyVec.size; i++){
      tempVec[i] = MyVec.data[i];
    }
    delete[] MyVec.data;
    MyVec.data = tempVec;
    MyVec.capacity = MyVec.capacity*2;
    tempVec = nullptr;
}
