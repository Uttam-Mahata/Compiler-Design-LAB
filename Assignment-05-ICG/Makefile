CC = gcc
CFLAGS = -Wall -g
YACC = yacc
LEX = flex

# Target executable
TARGET = icg_compiler

# Source files
SOURCES = parse.y lex.l symbol_table.c icg.c
OBJECTS = y.tab.o lex.yy.o symbol_table.o icg.o

# Default target
all: $(TARGET)

# Build the compiler
$(TARGET): y.tab.c lex.yy.c symbol_table.o icg.o
	$(CC) $(CFLAGS) -o $(TARGET) y.tab.c symbol_table.o icg.o -lfl

# Generate parser from yacc
y.tab.c y.tab.h: parse.y
	$(YACC) -d parse.y

# Generate lexer from lex
lex.yy.c: lex.l y.tab.h
	$(LEX) lex.l

# Compile symbol table
symbol_table.o: symbol_table.c symbol_table.h
	$(CC) $(CFLAGS) -c symbol_table.c

# Compile ICG module
icg.o: icg.c icg.h
	$(CC) $(CFLAGS) -c icg.c

# Clean up generated files
clean:
	rm -f $(TARGET) y.tab.c y.tab.h lex.yy.c *.o three_address_code.txt y.output

# Test with simple assignment
test_assign: $(TARGET)
	@echo "=== Testing Assignment Statements ==="
	@echo 'int main() { int a, b, c; a = 5; b = 10; c = a + b * 2; }' | ./$(TARGET)

# Test with if statement
test_if: $(TARGET)
	@echo "=== Testing If Statement ==="
	@echo 'int main() { int x; x = 10; if (x) { x = 20; } }' | ./$(TARGET)

# Test with if-else statement
test_ifelse: $(TARGET)
	@echo "=== Testing If-Else Statement ==="
	@echo 'int main() { int x, y; x = 10; if (x) { y = 1; } else { y = 0; } }' | ./$(TARGET)

# Test with while loop
test_while: $(TARGET)
	@echo "=== Testing While Loop ==="
	@echo 'int main() { int i; i = 0; while (i) { i = i + 1; } }' | ./$(TARGET)

# Test all
test: test_assign test_if test_ifelse test_while

.PHONY: all clean test test_assign test_if test_ifelse test_while
