

#include "MyMalloc.h"

MyMalloc::MyMalloc() {
    myHashTable = HashTable();
}

void* MyMalloc::allocate(size_t bytesToAllocate) {
    int pagesSize = (bytesToAllocate + (4095)) / pageSize_;
    size_t allocateSize = (size_t) (pagesSize * pageSize_); // get tableSize in pages to allocate
    void *pointer = mmap(nullptr, allocateSize, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, 0, 0); // sys call to get ptr to mapped address region

    if (pointer == MAP_FAILED) { // check that mmap was successful
        perror("mmap failed!");
        exit(1);
    }

    HashNode node = HashNode(pointer, allocateSize); // create a node with the ptr address and the size of the data that we mapped
    myHashTable.insert(node); // put this into the hashtable

    return pointer;
}

void MyMalloc::deallocate(void *ptr) {
    //find the node at the ptr and remove it from the hash table
    size_t sizeOfRemovedNode = myHashTable.remove(ptr); //retrieve the size of the memory block
    if (sizeOfRemovedNode == -1) {
        throw std::runtime_error("error! passed node was not removed!");
    }
    if (munmap(ptr, sizeOfRemovedNode) == -1) { //use munmap sys call to remove info from memory
        perror("munmap failed in deallocate!");
        exit(1);
    }
}