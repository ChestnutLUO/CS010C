# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror
GTEST_FLAGS = -lgtest -pthread

# Default target: build all executables
all: q1-1 q1-2 q2 test_lab_4

# Compile q1-1
q1-1: q1-1.cc stack_vector.h
	$(CXX) $(CXXFLAGS) -o q1-1 q1-1.cc

# Compile q1-2
q1-2: q1-2.cc stack_vector.h
	$(CXX) $(CXXFLAGS) -o q1-2 q1-2.cc

# Compile q2
q2: q2.cc stack_vector.h
	$(CXX) $(CXXFLAGS) -o q2 q2.cc

# Compile test_lab_4 with Google Test
test_lab_4: test_lab_4.cc q1-1.cc q1-2.cc q2.cc stack_vector.h
	$(CXX) $(CXXFLAGS) $(GTEST_FLAGS) -o test_lab_4 test_lab_4.cc

# Clean rule: Remove all compiled files
clean:
	rm -f q1-1 q1-2 q2 test_lab_4
