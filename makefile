# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -std=c++11 -g -Wall

OBJECTS = simulator.o director.o scheduler.o statistician.o queue.o heap.o customer.o
HEADERS := $(shell find . -path ./test -prune -o -name "*.hpp" -print)

main: main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJECTS): $(HEADERS)

clean:
	$(RM) *.o *.gch core main
