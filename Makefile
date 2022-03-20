.PHONY: clean

CC = g++
CXX = g++
CXXFLAGS = -Wall -g -fopenmp
LDLIBS = -lboost_program_options -lblas
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

test1: main
	   ./main --np 1 --dt 0.001 --T 100.0 --Nx 101 --Ny 101 --a 0.75 --b 0.06 --mu1 5.0 --mu2 0.0 --eps 50.0
		
test2: main
	   ./main --np 1 --dt 0.001 --T 100.0 --Nx 251 --Ny 251 --a 0.75 --b 0.06 --mu1 5.0 --mu2 0.0 --eps 13.0

test3: main
	   ./main --np 1 --dt 0.001 --T 100.0 --Nx 101 --Ny 101 --a 0.5 --b 0.1 --mu1 5.0 --mu2 0.0 --eps 50.0

test4: main
	   ./main --np 1 --dt 0.001 --T 100.0 --Nx 151 --Ny 81 --a 0.75 --b 0.0001 --mu1 1.0 --mu2 0.01 --eps 12.5

clean: 
	rm -rf *.o