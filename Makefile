# Makefile
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

# 源文件
SRC := src/graph_mat.cpp
TEST_MAIN := test/test_graph_mat.cpp

# 输出可执行文件
TARGET := test_mat

all: $(TARGET)

$(TARGET): $(SRC) $(TEST_MAIN)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST_MAIN) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
