# Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++17 -pthread -I include

# Source files
SRCS = $(wildcard src/*.cpp)

# Object files
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

# Executable name
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS) main.o
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.cpp include/%.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f obj/*.o main.o $(EXEC)