CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

LIB = my_search_engine.cc page_file.cc word_file.cc simple_browser.cc

all: collect rank search

collect: collect.cc $(LIB)
	$(CXX) $(CXXFLAGS) -o collect collect.cc $(LIB)

rank: rank.cc $(LIB)
	$(CXX) $(CXXFLAGS) -o rank rank.cc $(LIB)

search: search.cc $(LIB)
	$(CXX) $(CXXFLAGS) -o search search.cc $(LIB)

clean:
	rm -f collect rank search pagedisk.txt worddisk.txt pagedisk-ranked.txt
