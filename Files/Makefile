all: main

main: main.o InputDataAlgorithms.o DecisionTreeAlgorithm.o SupportAlgorithms.o
	g++ main.o InputDataAlgorithms.o DecisionTreeAlgorithm.o SupportAlgorithms.o -o main

main.o: main.cpp
	g++ -c main.cpp

InputDataAlgorithms.o: InputDataAlgorithms.cpp InputDataAlgorithms.hpp
	g++ -c InputDataAlgorithms.cpp

DecisionTreeAlgorithm.o: DecisionTreeAlgorithm.cpp DecisionTreeAlgorithm.hpp
	g++ -c DecisionTreeAlgorithm.cpp

SupportAlgorithms.o: SupportAlgorithms.cpp SupportAlgorithms.hpp
	g++ -c SupportAlgorithms.cpp

clean: 
	rm *.o main 
