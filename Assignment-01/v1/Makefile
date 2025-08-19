# Makefile for Lexical Analyzer
# Compiler Design Lab Assignment

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = lexer
OBJS = lex.o main.o

# Default target
all: $(TARGET)

# Build the lexer executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile lex.c to object file
lex.o: lex.c lex.h
	$(CC) $(CFLAGS) -c lex.c -o lex.o

# Compile main.c to object file
main.o: main.c lex.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Clean up compiled files
clean:
	rm -f *.o $(TARGET)

# Test the lexer with test input
test: $(TARGET)
	./$(TARGET) test_input.c

# Test with simple test file
test-simple: $(TARGET)
	./$(TARGET) simple_test.c

# Test semicolon recognition
test-semicolon: $(TARGET)
	./$(TARGET) semicolon_test.c

# Show usage
help:
	@echo "Available targets:"
	@echo "  all       - Build the lexer (default)"
	@echo "  clean     - Remove compiled files"
	@echo "  test      - Run lexer on test_input.c"
	@echo "  test-simple - Run lexer on simple_test.c"
	@echo "  test-semicolon - Run lexer on semicolon_test.c"
	@echo "  help      - Show this help message"

# Phony targets
.PHONY: all clean test test-simple test-semicolon help
