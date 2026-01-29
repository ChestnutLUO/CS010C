CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11

TARGET = sighting_search
SOURCES = sighting_search.cc

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f  $(TARGET)
	rm -f *.dat
	rm -f *.o
