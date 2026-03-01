CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: prime_factors test_multiset

prime_factors: prime_factors.cc multiset.h
	$(CXX) $(CXXFLAGS) -o prime_factors prime_factors.cc

test_multiset: test_multiset.cc multiset.h
	$(CXX) $(CXXFLAGS) -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main -pthread test_multiset.cc -o test_multiset

test: test_multiset
	./test_multiset

clean:
	rm -f prime_factors test_multiset

.PHONY: all test clean
