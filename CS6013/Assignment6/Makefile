CXX= /opt/homebrew/opt/llvm/bin/clang++
CXXFLAGS=-std=c++11 
LDFLAGS=-fopenmp

SRC=main.cpp
OBJ=$(SRC:.cpp=.o)
EXEC=parallel_sum

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -fopenmp  -o $(EXEC)  $(OBJ) 

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -fopenmp  $(SRC) 

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
