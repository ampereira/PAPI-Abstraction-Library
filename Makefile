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

#pal.o: event.o eventset.o errors.o measure.o
#	$(CXX) $(CXX_FLAGS) -c eventset.o event.o errors.o measure.o -o pal.o $(PAPI_FLAGS)

pal: event.o eventset.o errors.o measure.o
	$(CXX) -shared -Wl,-soname,libpal.so -o libpal.so $(BUILD_DIR)/* $(PAPI_FLAGS)
	@mv libpal.so $(LIB_DIR)/libpal.so

test: pal test.cpp
	$(CXX) $(CXX_FLAGS) -o $(TEST_DIR)/test.out -L $(LIB_DIR) -lpal $(TEST_DIR)/test.cpp

clean:
	rm -f $(BUILD_DIR)/*.o $(LIB_DIR)/*