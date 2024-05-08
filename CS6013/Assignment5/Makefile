CXX=c++
CFLAGS= -std=c++11
CCSOURCE= ConcurrentQueueTest.cpp
HEADERS= ConcurrentQueue.h

hw5: $(CCSOURCE) $(HEADERS)
	$(CXX) $(CFLAGS) -o hw5 $(CCSOURCE)

clean:
	rm -f *.o *.out hw5

run: hw5
	./hw5