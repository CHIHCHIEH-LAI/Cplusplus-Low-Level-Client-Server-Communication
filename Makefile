# Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11 -pthread

# Source files
SRCS = server.cpp thread_pool.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = server

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)