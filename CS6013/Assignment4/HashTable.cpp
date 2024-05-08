

#include "HashTable.h"


HashTable::~HashTable() {
    this->start = nullptr;
}

HashTable::HashTable() {
    this->capacity = iniCap; // Set the table to hold 10 values initially
    this->size = 0; // hash table should be empty
    start = (HashNode*) mmap(nullptr, capacity * sizeof(HashNode), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    if (start == MAP_FAILED) { // check that mmap was successful
        perror("start mmap failed!");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < capacity; i++) { // initialize each of the 10 slots (each of which are a hashnode) with empty data indicating no memory has been mapped
        start[i].ptr = nullptr;
        start[i].size = 0;
    }
}

void HashTable::insert(HashNode hashNode) {
    if (size >= capacity / 2) { // if the size > capacity we need to grow so we do not go out of bounds of our array
        grow();
    }

    int index = hashFunctor(hashNode.ptr);
    // confirm that where we are trying to insert does not contain data or a lazy delete
    while (start[index].ptr != nullptr && start[index].ptr != hashNode.ptr && start[index].ptr != (void*)-1) {
        index++;
        index %= capacity;
    }

    if (start[index].ptr == hashNode.ptr) {
        throw std::runtime_error("Cannot use the same address twice"); //error of double inserting
    }

    start[index] = hashNode;
    size++;

}

size_t HashTable::remove(void *ptr) {
    size_t index = hashFunctor(ptr);
    size_t sizeToReturn = -1;
    while (true) {
        if (start[index].ptr == nullptr) {
            return sizeToReturn;
        } else if (start[index].ptr == ptr) { // gives us the node we want to remove
            start[index].ptr = (void *) -1; // indicates lazy delete
            sizeToReturn = start[index].size;
            start[index].size = -1;
            size--;
            return sizeToReturn;
        }
        index++;
        index %= capacity;
    }
}

    void HashTable::grow() {
        int oldCapcity = capacity; //store old capacity to use for copying values
        capacity *= 2; // double capcity so we can create a new table twice the size

        // initialize new table with twice the capacity
        HashNode *newBiggerTable = (HashNode *) mmap(nullptr, capacity * sizeof(HashNode), PROT_READ | PROT_WRITE,
                                                     MAP_ANON | MAP_PRIVATE, -1, 0);

        if (newBiggerTable == MAP_FAILED) { // check that mmap was successful
            perror("newBiggerTable mmap failed in grow!");
            exit(EXIT_FAILURE);
        }

        for (int i = 0;
             i < this->capacity; i++) { // initialize new table with empty data indicating no memory has been mapped
            newBiggerTable[i].ptr = nullptr;
            newBiggerTable[i].size = 0;

        }

        for (int i = 0; i < oldCapcity; i++) { // for the size of the old table
            if (start[i].ptr != (void *) -1 &&
                start[i].ptr != nullptr) { // if the data has not been lazy deleted or is nullptr
                size_t index = hashFunctor(start[i].ptr); // get index of the value in the old table
                while (newBiggerTable[index].ptr !=
                       nullptr) { // as we loop through, don't want to copy to a place we've already copied to
                    index++;
                }
                newBiggerTable[index].ptr = start[i].ptr; // and use that as the index in the new table to copy the data to
                newBiggerTable[index].size = start[i].size;
            }
        }

        std::swap(start, newBiggerTable);
        if (munmap(newBiggerTable, oldCapcity * sizeof(HashNode)) == -1) { // release old memory
            perror("munmap of old table failed!");
            exit(EXIT_FAILURE);
        }
    }


size_t HashTable::hashFunctor(void *ptr) {
    size_t hashSize = reinterpret_cast<size_t>(ptr);
    return (long) hashSize % capacity;
}

