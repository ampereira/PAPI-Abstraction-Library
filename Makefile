#!/bin/sh

CXX = g++
CXX_FLAGS = -O3 -Wall -Wextra 
LIB_FLAGS = -fPIC -I/home/cpd19828/boost_1_50_0/ -L/home/cpd19828/boost_1_50_0/stage/lib
PAPI_FLAGS = -lpapi

BUILD_DIR = build
SRC_DIR = src
LIB_DIR = lib
TEST_DIR = examples

default: pal

errors.o: $(SRC_DIR)/errors.cpp $(SRC_DIR)/errors.hpp
	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c -o $(BUILD_DIR)/errors.o $(SRC_DIR)/errors.cpp

event.o: $(SRC_DIR)/event.cpp $(SRC_DIR)/event.hpp
	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c -o $(BUILD_DIR)/event.o $(SRC_DIR)/event.cpp

eventset.o: $(SRC_DIR)/eventset.cpp $(SRC_DIR)/eventset.hpp $(SRC_DIR)/event.hpp $(SRC_DIR)/errors.hpp
	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c -o $(BUILD_DIR)/eventset.o $(SRC_DIR)/eventset.cpp $(PAPI_FLAGS)

measure.o: $(SRC_DIR)/measure.cpp $(SRC_DIR)/measure.hpp $(SRC_DIR)/eventset.hpp
	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c -o $(BUILD_DIR)/measure.o $(SRC_DIR)/measure.cpp $(PAPI_FLAGS)

pal.o: $(SRC_DIR)/pal.cpp $(SRC_DIR)/pal.hpp $(SRC_DIR)/measure.hpp
	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c -o $(BUILD_DIR)/pal.o $(SRC_DIR)/pal.cpp $(PAPI_FLAGS)

pal: event.o eventset.o errors.o measure.o pal.o
	$(CXX) -shared -Wl,-soname,libpal.so -o libpal.so $(BUILD_DIR)/pal.o $(BUILD_DIR)/event.o $(BUILD_DIR)/eventset.o $(BUILD_DIR)/errors.o $(BUILD_DIR)/measure.o $(PAPI_FLAGS)
	@mv libpal.so $(LIB_DIR)/libpal.so

test: pal $(TEST_DIR)/test.cpp
	$(CXX) -O3 -Wall -Wextra -o examples/test.out -L /home/cpd19828/PAPI-Abstraction-Library/lib -lpal examples/test.cpp

#test2: pal.o event.o errors.o eventset.o measure.o $(TEST_DIR)/test.cpp
#	$(CXX) -g -Wall -Wextra -o examples/test.out build/pal.o build/event.o build/eventset.o build/errors.o build/measure.o examples/test.cpp -lpapi

clean:
	rm -f $(BUILD_DIR)/*.o $(LIB_DIR)/*