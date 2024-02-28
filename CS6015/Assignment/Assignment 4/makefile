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



CXX = g++
CXXFLAGS = -std=c++11

msdscript: main.o cmdline.o exec.o Expr.o parse.o
	$(CXX) $(CXXFLAGS) -o msdscript $^

test_msdscript: test_msdscript.o exec.o
	$(CXX) $(CXXFLAGS) -o test_msdscript $^


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o msdscript test_msdscript

.PHONY: clean

