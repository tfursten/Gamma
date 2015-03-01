CFLAGS=-Wall -O2
CXXFLAGS=-Wall -O2 -std=c++11

all: gamma

gamma: main.o gamma.o rnormal.o rexp.o
	$(CXX) -o gamma main.o gamma.o rnormal.o rexp.o -lm -lgsl -lgslcblas

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp

gamma.o: gamma.cpp gamma.h 
	$(CXX) -c $(CXXFLAGS) gamma.cpp 

rnormal.o: rnormal.cpp rnormal.h
	$(CXX) -c $(CXXFLAGS) rnormal.cpp

rexp.o: rexp.cpp rexp.h
	$(CXX) -c $(CXXFLAGS) rexp.cpp

clean:
	rm *.o