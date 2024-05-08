#include <iostream>
#include <vector>
#include <chrono>
#include "MyMalloc.h"



void tests() {
    //initialzie malloc
    MyMalloc testMalloc = MyMalloc();
    std::cout << "CONFIRM VALUES AFTER MALLOC INITIALIZATION:" << std::endl;
    std::cout << "Check table size to be 0: " << testMalloc.myHashTable.size << std::endl;
    std::cout << "Check capacity to be 10: " << testMalloc.myHashTable.capacity << std::endl;
    std::cout << "Check address to not be null: " << testMalloc.myHashTable.start << std::endl << std::endl;

    //confirm with asserts
    assert(testMalloc.myHashTable.size == 0);
    assert(testMalloc.myHashTable.capacity == 10);
    assert(testMalloc.myHashTable.start != nullptr);

    // test insertion and deletion of one byte
    void* ptrOfAdded = testMalloc.allocate(1);
    size_t indexOfAdded = testMalloc.myHashTable.hashFunctor(ptrOfAdded);
    std::cout << "CONFIRM VALUES AFTER ONE BYTE ALLOCATED:" << std::endl;
    std::cout << "ptr address of allocated byte: " << ptrOfAdded << std::endl;
    std::cout << "ptr address stored in the table: " << testMalloc.myHashTable.start[indexOfAdded].ptr << std::endl;
    std::cout << "Check table size: " << testMalloc.myHashTable.size << std::endl << std::endl;

    // now deallocate!
    testMalloc.deallocate(ptrOfAdded);
    std::cout << "CONFIRM VALUES AFTER ONE BYTE DELLOCATED:" << std::endl;
    std::cout << "ptr address should now indicate lazy delete: " << testMalloc.myHashTable.start[indexOfAdded].ptr << std::endl;
    std::cout << "Check table size: " << testMalloc.myHashTable.size << std::endl << std::endl;

    // allocate large memory and print the hash table
    void* ptrsOfAllocated[3000];
    for (int i = 0; i < 3000; i++) {
        ptrsOfAllocated[i] = nullptr;
    }
    std::cout << "ALLOCATING 1000 BYTES ONE AT A TIME:" << std::endl;
    for (int i = 0; i < 1000; i++) {
        ptrsOfAllocated[i] = testMalloc.allocate(i+1);
    }
    std::cout << "table size should be 1000: " << testMalloc.myHashTable.size << std::endl << std::endl;

    //now allocate more stuff
    std::cout << "NOW ALLOCATING 2000 MORE BYTES ONE AT A TIME:" << std::endl;
    for (int i = 1000; i < 3000; i++) {
        ptrsOfAllocated[i] = testMalloc.allocate(i);
    }
    std::cout << "table size should be 3000: " << testMalloc.myHashTable.size << std::endl << std::endl;

    // now test partial deallocation
    std::cout << "NOW DEALLOCATING 333 BYTES ONE AT A TIME:" << std::endl;
    for (int i = 0; i < 333; i++) {
        testMalloc.deallocate(ptrsOfAllocated[i]);
    }
    std::cout << "table size should be 2667: " << testMalloc.myHashTable.size << std::endl << std::endl;

    std::cout << "NOW DEALLOCATING REMAINING BYTES ONE AT A TIME:" << std::endl;
    for (int i = 333; i < 3000; i++) {
        testMalloc.deallocate(ptrsOfAllocated[i]);
    }
    std::cout << "table size should be 0: " << testMalloc.myHashTable.size << std::endl << std::endl;

    std::cout << "NOW TRYING TO DEALLOCATE SAME 2667 BYTES (SHOULD GET ERROR):" << std::endl;
    std::cout << "ERROR SHOULD SAY: 'error! passed node was not removed!': " << std::endl;
    try {
        for (int i = 333; i < 3000; i++) {
            testMalloc.deallocate(ptrsOfAllocated[i]);
        }
    } catch (std::runtime_error e) {
        std::cout << "Error message: " << e.what() << std::endl << std::endl;
    }

    std::cout << "TEST INSERT" << std::endl;

    HashNode nodeToInsert = HashNode(ptrOfAdded, 4096);
    testMalloc.myHashTable.insert(nodeToInsert);
    std::cout << "AFTER FIRST INSERT table size should be 1: " << testMalloc.myHashTable.size << std::endl;
    std::cout << "Insert again, should get an error" << std::endl;
    try {
        testMalloc.myHashTable.insert(nodeToInsert);
    } catch (std::runtime_error e) {
        std::cout << "Error message: " << e.what() << std::endl << std::endl;
    }

    std::cout << "before removing table size should be 1: " << testMalloc.myHashTable.size << std::endl;
    std::cout << "TEST REMOVING:" << std::endl;
    void* ptr = nodeToInsert.ptr;
    testMalloc.myHashTable.remove(ptr);
    std::cout << "after removing table size should be 0: " << testMalloc.myHashTable.size << std::endl;
};

void benchmarkTests() {
    MyMalloc mallocTest = MyMalloc();
    const int iterations = 1000;
    long totalMyMallocTime = 0;
    long totalRealMallocTime = 0;
    long totalMyDeallocateTime = 0;
    long totalRealFreeTime = 0;

    for (int j = 0; j < iterations; j++) {
        void* ptrsOfAllocated[1000];
        for (int i = 0; i < 1000; i++) {
            ptrsOfAllocated[i] = nullptr;
        }
        auto realMallocStart = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; i++) {
            ptrsOfAllocated[i] = malloc(i+1);
        }
        auto realMallocEnd = std::chrono::high_resolution_clock::now();

        void* ptrsOfAllocatedMyMalloc[1000];
        for (int i = 0; i < 1000; i++) {
            ptrsOfAllocatedMyMalloc[i] = nullptr;
        }
        auto myMallocStart = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; i++) {
            ptrsOfAllocatedMyMalloc[i] = mallocTest.allocate(i+1);
        }
        auto myMallocEnd = std::chrono::high_resolution_clock::now();

        long myTime = std::chrono::duration_cast<std::chrono::nanoseconds>(myMallocEnd-myMallocStart).count();
        long realTime = std::chrono::duration_cast<std::chrono::nanoseconds>(realMallocEnd-realMallocStart).count();

        totalMyMallocTime += myTime;
        totalRealMallocTime += realTime;

        auto realFreeStart = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; i++) {
            free(ptrsOfAllocated[i]);
        }
        auto realFreeEnd = std::chrono::high_resolution_clock::now();

        auto myDeallocateStart = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; i++) {
            mallocTest.deallocate(ptrsOfAllocatedMyMalloc[i]);
        }
        auto myDeallocateEnd = std::chrono::high_resolution_clock::now();

        long myDeallocateTime = std::chrono::duration_cast<std::chrono::nanoseconds>(myDeallocateEnd-myDeallocateStart).count();
        long realFreeTime = std::chrono::duration_cast<std::chrono::nanoseconds>(realFreeEnd-realFreeStart).count();

        totalMyDeallocateTime += myDeallocateTime;
        totalRealFreeTime += realFreeTime;
    }

    long averageMyMallocTime = totalMyMallocTime / iterations;
    long averageRealMallocTime = totalRealMallocTime / iterations;
    long averageMyDeallocateTime = totalMyDeallocateTime / iterations;
    long averageRealFreeTime = totalRealFreeTime / iterations;

    std::cout << "Average MY ALLOCATED/MALLOC time in nanoseconds was: " << averageMyMallocTime << std::endl;
    std::cout << "Average REAL malloc time in nanoseconds was: " << averageRealMallocTime << std::endl;
    std::cout << "Average MY DEALLOCATE/FREE time in nanoseconds was: " << averageMyDeallocateTime << std::endl;
    std::cout << "Average REAL free time in nanoseconds was: " << averageRealFreeTime << std::endl;
}



int main() {
    std::cout << "_______________________________" << std::endl;
    std::cout << "*****BENCH MARK TESTS*****" << std::endl << std::endl;
    benchmarkTests();
    std::cout << "--------------------------------" << std::endl;
    std::cout << std::endl << std::endl << std::endl;
    std::cout << "_______________________________" << std::endl;
    std::cout << "*****TEST OF ALLOCATION AND DEALLOCATION*****" << std::endl << std::endl;
    tests();
    std::cout << "-----------------------------------" << std::endl;
    std::cout << std::endl << std::endl << std::endl;

    return 0;
}