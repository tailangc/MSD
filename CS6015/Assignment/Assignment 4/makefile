#CXX = g++
#CXXFLAGS = -std=c++11
#CXXSOURCE = ${wildcard *.cpp}
#
#all: msdscript
#
#%.o: %.cpp %.h
#	$(CXX) $(CXXFLAGS) -c $< -o $@
#
#OBJECTS = $(CXXSOURCE:.cpp=.o)
#
#msdscript: $(OBJECTS)
#	$(CXX) $(CXXFLAGS) -o msdscript $(OBJECTS)
#
#.PHONY: clean
#clean:
#	rm -f *.o msdscript
#
#test_msdscript: test_msdscript.o exec.o
#	$(CXX) $(CXXFLAGS) -o test_msdscript $^
#
#doc: msdscript
#		cd documentation && doxygen


CC=c++
CFLAGS=-std=c++14
#SRC=$(wildcard *.cpp)
#OBJ=$(patsubst %.cpp, %.o, $(SRC))
MSD_OBJ=main.o Expr.o parse.o cmdline.o Val.o
TEST_OBJ= exec.o Expr.o Val.o
GEN_OBJ=  Expr.o

.PHONY: clean test interp print pretty-print doc open_doc run fuzz_test
msdscript: $(MSD_OBJ)
	$(CC) $(CFLAGS) $^ -o $@
test_msdscript:$(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@
test_generator:$(GEN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.h
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
run:
	./msdscript
test:
	./msdscript --test
interp:
	./msdscript --interp
print:
	./msdscript --print
pretty-print:
	./msdscript --pretty-print
clean:
	rm -rf *.o msdscript test_msdscript test_generator
doc:
	cd documentation && doxygen
open_doc:
	open documentation/html/index.html

