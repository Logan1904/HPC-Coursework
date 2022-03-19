.PHONY: clean

CC = g++
CXX = g++
CXXFLAGS = -Wall -g -fopenmp
LDLIBS = -lboost_program_options
LDFLAGS = -g -fopenmp

default: main

main.o: main.cpp 

ProcessArgs.o: ProcessArgs.cpp

SetParameters.o: SetParameters.cpp 

SetInitialConditions.o: SetInitialConditions.cpp

Initialise.o: Initialise.cpp

TimeIntegrate.o: TimeIntegrate.cpp

Write.o: Write.cpp

main: main.o ProcessArgs.o SetParameters.o SetInitialConditions.o Initialise.o TimeIntegrate.o Write.o

clean: 
	rm -rf *.o