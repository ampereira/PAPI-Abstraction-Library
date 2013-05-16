#!/bin/sh

CXX = g++
CXX_FLAGS = -O3 -Wall -Wextra -fPIC -I/home/cpd19828/boost_1_50_0/ -L/home/cpd19828/boost_1_50_0/stage/lib
PAPI_FLAGS = -lpapi

default: pal_lib

errors.o: errors.cpp errors.hpp
	$(CXX) $(CXX_FLAGS) -c errors.cpp

event.o: event.cpp event.hpp
	$(CXX) $(CXX_FLAGS) -c event.cpp

eventset.o: eventset.cpp eventset.hpp event.hpp errors.hpp
	$(CXX) $(CXX_FLAGS) -c eventset.cpp $(PAPI_FLAGS)

measure.o: measure.cpp measure.hpp eventset.hpp
	$(CXX) $(CXX_FLAGS) -c measure.cpp $(PAPI_FLAGS)

#pal.o: event.o eventset.o errors.o measure.o
#	$(CXX) $(CXX_FLAGS) -c eventset.o event.o errors.o measure.o -o pal.o $(PAPI_FLAGS)

pal: event.o eventset.o errors.o measure.o
	$(CXX) -shared -Wl,-soname,libpal.so.1 -o libpal.so event.o eventset.o errors.o measure.o $(PAPI_FLAGS)

test.o: test.cpp
	$(CXX) -O3 -Wall -Wextra -o test.out test.cpp

test: pal test.o
	$(CXX) $(CXX_FLAGS) -o a.out -L. -lpal test.o

clean:
	rm -f *.o libpal.so*