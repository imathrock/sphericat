CC = g++
CCFLAGS = -std=c++17 -O3 -Wall -mavx2 -mfma 

SOURCE = matrix\matrix.cpp main.cpp clankerfuncs.h

TARGET = main

all:
	$(CC) $(CCFLAGS) $(SOURCE) -o $(TARGET)
clean:
	rm -f main