.PHONY: clean

CC = g++

default: main

main.o: main.cpp 

SetParameters.o: SetParameters.cpp 

SetInitialConditions.o: SetInitialConditions.cpp

Write.o: Write.cpp

main: main.o SetParameters.o SetInitialConditions.o Write.o

clean: 
	rm -rf *.o