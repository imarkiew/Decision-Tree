CXX		= g++
CXXFLAGS	= -std=c++11 

all: main

main: main.o InputDataAlgorithms.o DecisionTreeAlgorithm.o SupportAlgorithms.o
	$(CXX) $(CXXFLAGS) main.o InputDataAlgorithms.o DecisionTreeAlgorithm.o SupportAlgorithms.o -o main

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

InputDataAlgorithms.o: InputDataAlgorithms.cpp InputDataAlgorithms.hpp
	$(CXX) $(CXXFLAGS) -c InputDataAlgorithms.cpp

DecisionTreeAlgorithm.o: DecisionTreeAlgorithm.cpp DecisionTreeAlgorithm.hpp
	$(CXX) $(CXXFLAGS) -c DecisionTreeAlgorithm.cpp

SupportAlgorithms.o: SupportAlgorithms.cpp SupportAlgorithms.hpp
	$(CXX) $(CXXFLAGS) -c SupportAlgorithms.cpp

clean: 
	rm *.o main 
