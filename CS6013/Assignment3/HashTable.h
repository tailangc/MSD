

#ifndef ASSIGNMENT3_HASHTABLE_H
#define ASSIGNMENT3_HASHTABLE_H
#include <cstdio>
#include <sys/mman.h>
#include <iostream>

class HashNode {
public:
    void* ptr;
    size_t size;
    HashNode(void *ptr, size_t size){
        this->ptr = ptr;
        this->size = size;
    };
};

class HashTable {
public:
    int size;
    size_t capacity;
    size_t iniCap = 10;
    HashNode* start;

    HashTable(); //constructor
    ~HashTable(); //destructor

    void insert(HashNode hashNode);
    size_t remove(void *ptr);
    void grow();
    size_t hashFunctor(void *ptr);
};



#endif //ASSIGNMENT3_HASHTABLE_H
