CC = g++
CCFLAGS = -std=c++17 -O3 -Wall -mavx2 -mfma 

SOURCE = matrix\matrix.cpp main.cpp
TEST_SOURCE = matrix\matrix.cpp test_eigen.cpp

TARGET = main
TEST_TARGET = test_eigen

all:
	$(CC) $(CCFLAGS) $(SOURCE) -o $(TARGET)

test:
	$(CC) $(CCFLAGS) $(TEST_SOURCE) -o $(TEST_TARGET)
	.\$(TEST_TARGET)

clean:
	del /f main.exe test_eigen.exe 2>nul || echo Clean complete