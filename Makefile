CC = g++
CFLAGS  = -g -Wall -std=c++11
SOURCE	= ./src/VectorArray.cpp ./src/Vector.cpp ./src/Parser.cpp ./src/Distance.cpp ./src/ExactNN.cpp ./src/Manhattan.cpp ./src/LSH.cpp ./src/HashTable.cpp ./src/HashFunction.cpp ./src/HyperCube.cpp ./src/Grids.cpp ./src/DTW.cpp ./src/CurvesParser.cpp ./src/Initialization.cpp ./src/RandomSelection.cpp ./src/Cluster.cpp main.cpp ./src/KMeansInit.cpp ./src/Assignment.cpp ./src/Lloyds.cpp
HEADER  = ./lib/VectorArray.h ./lib/Vector.h ./lib/Parser.h ./lib/Distance.h ./lib/ExactNN.h ./lib/Manhattan.h ./lib/LSH.h ./lib/HashTable.h ./lib/HashFunction.h ./lib/HyperCube.h ./lib/Grids.h ./lib/DTW.h ./lib/CurvesParser.h ./lib/Initialization.h ./lib/RandomSelection.h ./lib/Cluster.h ./lib/KMeansInit.h ./lib/Assignment.h ./lib/Lloyds.h
OBJS 	= VectorArray.o Vector.o Parser.o Distance.o ExactNN.o Manhattan.o LSH.o HashTable.o HashFunction.o HyperCube.o Grids.o DTW.o CurvesParser.o Initialization.o RandomSelection.o Cluster.o main.o KMeansInit.o Assignment.o Lloyds.o
# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#

default: all


all:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o out

# lshPoints:	$(OBJS)
# 	$(CC) $(CFLAGS) ./points/exactLSHPoints.cpp $(OBJS) -o out

VectorArray.o:	./src/VectorArray.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/VectorArray.cpp

Distance.o:		./src/Distance.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/Distance.cpp

Manhattan.o:	./src/Manhattan.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/Manhattan.cpp

Vector.o:		./src/Vector.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/Vector.cpp

Parser.o:		./src/Parser.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/Parser.cpp

ExactNN.o:		./src/ExactNN.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/ExactNN.cpp

LSH.o:		./src/LSH.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/LSH.cpp

HashTable.o:		./src/HashTable.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/HashTable.cpp

HashFunction.o:		./src/HashFunction.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/HashFunction.cpp

HyperCube.o:		./src/HyperCube.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/HyperCube.cpp

Grids.o:		./src/Grids.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/Grids.cpp

DTW.o:		./src/DTW.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/DTW.cpp

CurvesParser.o:		./src/CurvesParser.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/CurvesParser.cpp

Initialization.o:	./src/Initialization.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/Initialization.cpp

RandomSelection.o:	./src/RandomSelection.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/RandomSelection.cpp

KMeansInit.o:	./src/KMeansInit.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/KMeansInit.cpp

Cluster.o:	./src/Cluster.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/Cluster.cpp

Assignment.o:	./src/Assignment.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/Assignment.cpp

Lloyds.o:	./src/Lloyds.cpp $(HEADER)
	$(CC) $(CFLAGS) -c ./src/Lloyds.cpp

count:
	wc $(SOURCE) $(HEADER)

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) out *.o *~
