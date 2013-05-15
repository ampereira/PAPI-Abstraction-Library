#!/bin/sh

CXX = g++
CXX_FLAGS = -Wall -Wextra
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

test.o: test.cpp measure.hpp
	$(CXX) $(CXX_FLAGS) -c test.cpp

pal.o: event.o eventset.o errors.o measure.o test.o
	$(CXX) $(CXX_FLAGS) -c -fPIC eventset.o event.o errors.o measure.o test.o -o pal.o $(PAPI_FLAGS)

pal_lib: pal.o
	$(CXX) -shared -Wl,-soname,libpal.so.1 -o libpal.so.1.0.1 pal.o

test: pal_lib main.cpp
	$(CXX) $(CXX_FLAGS) -o main -L. -lpal

clean:
	rm -rf *.o