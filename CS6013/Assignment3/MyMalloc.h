

#ifndef ASSIGNMENT3_MYMALLOC_H
#define ASSIGNMENT3_MYMALLOC_H
#include <stdio.h>
#include "HashTable.h"

class MyMalloc {
public:
    HashTable myHashTable;
    size_t pageSize_ = 4096;

    MyMalloc(); //constructor
//    ~MyMalloc(); //destructor
    void* allocate(size_t bytesToAllocate);
    void deallocate(void* ptr);

};


#endif //ASSIGNMENT3_MYMALLOC_H
