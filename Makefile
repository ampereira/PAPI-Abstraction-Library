#!/bin/sh

CXX = g++
CXX_FLAGS = -Wall -Wextra
PAPI_FLAGS = -lpapi

default: pal

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

pal: event.o eventset.o errors.o measure.o test.o
	$(CXX) $(CXX_FLAGS) eventset.o event.o errors.o measure.o test.o -o pal $(PAPI_FLAGS)

clean:
	rm -rf *.o