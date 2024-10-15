# Makefile for kmeans program

# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -lm

# Source files
SRCS = main.c kmeans.c
OBJS = $(SRCS:.c=.o)
EXEC = kmeans

# Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(EXEC)

# Compile each source file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Target to clean objects and executable
clean:
	rm -f $(OBJS) $(EXEC)

# Target to run the program with Valgrind for memory leak detection
valgrind:
	valgrind --leak-check=full --track-origins=yes ./$(EXEC)

# Target to run basic tests (if applicable)
test:
	# Add your test commands here

# Target for debugging with GDB
debug:
	gdb ./$(EXEC)

# Help target for documentation
help:
	@echo "Usage: make [target]"
	@echo "Targets:"
	@echo "  all        : Compile the executable (default)"
	@echo "  clean      : Remove object files and executable"
	@echo "  valgrind   : Run executable with Valgrind for memory leak detection"
	@echo "  debug      : Run executable with GDB for debugging"
	@echo "  test       : Run for basic testing (if applicable)"
	@echo "  help       : Show this help message"

# Phony targets (targets that are not actual files)
.PHONY: all clean valgrind debug test help

