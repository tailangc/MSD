#include <iostream>
#include <thread>
#include "ConcurrentQueue.h"


bool testQueue( int num_producers, int num_consumers, int num_ints ) {

    std::vector<std::thread> threadList;
    //reserve space for all producer and consumer threads
    threadList.reserve(num_producers + num_consumers);
    ConcurrentQueue<int> queue;

    //producer threads
    for(int i = 0; i < num_producers; i++){
        //enqueue num_ints ints into the ConcurrentQueue.
        threadList.push_back(std::thread([&queue, num_ints](){
            for(int j = 0; j < num_ints; j++){
                queue.enqueue(j);
            }
        }));
    }
    //consumer threads
    for(int i = 0; i < num_consumers; i++){
        //dequeue num_ints ints from the ConcurrentQueue.
        threadList.push_back(std::thread([&queue, num_ints](){
            for(int j = 0; j < num_ints; j++){
                int value;
                queue.dequeue(&value);
            }
        }));
    }
    for(auto& thread : threadList){
        thread.join();
    }


    // Test if the elements in the queue is inserted and deleted correctly
    return queue.size() == (num_producers - num_consumers) * num_ints;
}

int main(int argc, char** argv){

    //num_producer, num_consumer, num_ints

    std::string argument = argv[1];
    int num_producers = std::stoi(argument);
    argument = argv[2];
    int num_consumers = std::stoi(argument);
    argument = argv[3];
    int num_ints = std::stoi(argument);

    if(testQueue(num_producers, num_consumers, num_ints)) {
        std::cout << "All Tests passed" << std::endl;
    } else {
        std::cout << "Result doesnt match" << std::endl;
    }

    return 0;

}