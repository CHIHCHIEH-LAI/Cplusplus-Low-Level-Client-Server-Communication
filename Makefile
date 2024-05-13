# Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11 -pthread

# Source files
SRCS = load_balancer.cpp round_robin_strategy.cpp server.cpp thread_pool.cpp main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)