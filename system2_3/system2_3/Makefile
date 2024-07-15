# Variables
CC = g++
CFLAGS = -std=c++11

# Default target to compile and run
all: catan run

# Compile target
catan: Demo.cpp player.cpp catan.cpp board.cpp
	$(CC) -o catan Demo.cpp player.cpp catan.cpp board.cpp $(CFLAGS)
	./catan


