CXX = g++
CXXFLAGS = -std=c++11
CXXSOURCE = ${wildcard *.cpp}
LIB_DIR = ../Library_MSDScript
LIB_NAME = msdscript
INCLUDE_PATH = ./headers

CXXOBJECTS = main.o

# 编译并生成最终的可执行文件
msdscript: $(CXXOBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(LIB_DIR) -l$(LIB_NAME) -I$(INCLUDE_PATH)

# 通用规则从 .cpp 生成 .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -I$(INCLUDE_PATH)

.PHONY: clean

clean:
	rm -f *.o msdscript


