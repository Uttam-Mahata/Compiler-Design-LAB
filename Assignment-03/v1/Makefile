# Makefile for C Language Subset Parser
# Using Flex and Bison (YACC)

CC = gcc
FLEX = flex
BISON = yacc
CFLAGS = -g -Wall

# Target executable
TARGET = parser

# Source files
LEX_FILE = lex.l
YACC_FILE = parse.y
HEADER_FILE = tok_def.h

# Generated files
LEX_C = lex.yy.c
YACC_C = y.tab.c
YACC_H = y.tab.h

# Object files
OBJECTS = y.tab.o

# Default target
all: $(TARGET)

# Build the parser
$(TARGET): $(YACC_C) $(LEX_C)
	$(CC) $(CFLAGS) -o $(TARGET) $(YACC_C) -lfl

# Generate C code from YACC file
$(YACC_C) $(YACC_H): $(YACC_FILE)
	$(BISON) -d $(YACC_FILE)

# Generate C code from Lex file
$(LEX_C): $(LEX_FILE) $(YACC_H)
	$(FLEX) $(LEX_FILE)

# Clean build files
clean:
	rm -f $(TARGET) $(LEX_C) $(YACC_C) $(YACC_H) $(OBJECTS) *.o

# Clean everything including backup files
distclean: clean
	rm -f *~ *.bak

# Test with sample input
test: $(TARGET)
	@echo "Testing parser with sample input..."
	@echo "int main() { int x; x = 5; return 0; }" | ./$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the parser (default)"
	@echo "  clean    - Remove generated files"
	@echo "  distclean- Remove all generated and backup files"
	@echo "  test     - Test with sample input"
	@echo "  help     - Show this help message"

.PHONY: all clean distclean test help