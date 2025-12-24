CC = g++
CCFLAGS = -std=c++17 -O3 -Wall

SOURCE = main.cpp

TARGET = main

all:
	$(CC) $(CCFLAGS) $(SOURCE) -o $(TARGET)
clean:
	rm -f main