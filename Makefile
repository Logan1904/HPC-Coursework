.PHONY: clean

CC = g++
CXX = g++
CXXFLAGS = -Wall -g
LDLIBS = -lboost_program_options -lblas
LDFLAGS = -g

default: main

main.o: main.cpp 

ProcessArgs.o: ProcessArgs.cpp

SetParameters.o: SetParameters.cpp 

SetInitialConditions.o: SetInitialConditions.cpp

Initialise.o: Initialise.cpp


Write.o: Write.cpp

main: main.o ProcessArgs.o SetParameters.o SetInitialConditions.o Initialise.o Write.o

clean: 
	rm -rf *.o