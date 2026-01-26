CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g #the gtest I install need to run on c++ 17
LDFLAGS = -lgtest -lgtest_main -pthread

TARGET = test_list_doubly_linked
SOURCES = test_list_doubly_linked.cc
HEADERS = list_doubly_linked.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

