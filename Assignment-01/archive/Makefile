# Makefile for Lexical Analyzer

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = lexer
SOURCES = main.c lex.c
HEADERS = lex.h

# Default target
all: $(TARGET)

# Build the lexer
$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

# Clean build artifacts
clean:
	rm -f $(TARGET)

# Test with the provided input file
test: $(TARGET)
	./$(TARGET) input.c

# Test with comprehensive test file
test-all: $(TARGET)
	./$(TARGET) test_input.c

# Rebuild everything
rebuild: clean all

.PHONY: all clean test test-all rebuild
