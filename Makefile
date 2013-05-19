#!/bin/sh

CXX = g++
CXX_FLAGS = -O3 -Wall -Wextra 
LIB_FLAGS = -fPIC -I/home/cpd19828/boost_1_50_0/ -L/home/cpd19828/boost_1_50_0/stage/lib
PAPI_FLAGS = -lpapi

BUILD_DIR = build
SRC_DIR = src
LIB_DIR = lib

default: pal_lib

$*.cpp:
	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c -o $(BUILD_DIR)/$*.o $(SRC_DIR)/$*.cpp

#event.o: event.cpp event.hpp
#	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c event.cpp
#
#eventset.o: eventset.cpp eventset.hpp event.hpp errors.hpp
#	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c eventset.cpp $(PAPI_FLAGS)
#
#measure.o: measure.cpp measure.hpp eventset.hpp
#	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c measure.cpp $(PAPI_FLAGS)

#pal.o: event.o eventset.o errors.o measure.o
#	$(CXX) $(CXX_FLAGS) -c eventset.o event.o errors.o measure.o -o pal.o $(PAPI_FLAGS)

pal: event.o eventset.o errors.o measure.o
	$(CXX) -shared -Wl,-soname,libpal.so -o libpal.so event.o eventset.o errors.o measure.o $(PAPI_FLAGS)

test: pal test.cpp
	$(CXX) $(CXX_FLAGS) -o test.out -L. -lpal test.cpp

clean:
	rm -f *.o libpal.so*