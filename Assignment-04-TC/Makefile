CC = gcc
CFLAGS = -Wall -g
YACC = yacc
LEX = flex

# Target executable
TARGET = symbol_parser

# Source files
SOURCES = parse.y lex.l symbol_table.c
OBJECTS = y.tab.o lex.yy.o symbol_table.o

# Default target
all: $(TARGET)

# Build the parser
$(TARGET): y.tab.c lex.yy.c symbol_table.o
	$(CC) $(CFLAGS) -o $(TARGET) y.tab.c symbol_table.o -lfl

# Generate parser from yacc
y.tab.c y.tab.h: parse.y
	$(YACC) -d parse.y

# Generate lexer from lex
lex.yy.c: lex.l y.tab.h
	$(LEX) lex.l

# Compile symbol table
symbol_table.o: symbol_table.c symbol_table.h
	$(CC) $(CFLAGS) -c symbol_table.c

# Clean up generated files
clean:
	rm -f $(TARGET) y.tab.c y.tab.h lex.yy.c *.o

# Test with sample input
test: $(TARGET)
	echo "Testing with sample C program..."
	echo 'int main() { int x, y; float z; x = 10; y = x + 5; return 0; }' | ./$(TARGET)

# Create a sample test file
sample:
	echo 'int global_var;' > test_input.c
	echo 'float another_global;' >> test_input.c
	echo '' >> test_input.c
	echo 'int main() {' >> test_input.c
	echo '    int local_var;' >> test_input.c
	echo '    float local_float;' >> test_input.c
	echo '    {' >> test_input.c
	echo '        int block_var;' >> test_input.c
	echo '        block_var = 5;' >> test_input.c
	echo '        local_var = block_var + 10;' >> test_input.c
	echo '    }' >> test_input.c
	echo '    local_float = 3.14;' >> test_input.c
	echo '    return local_var;' >> test_input.c
	echo '}' >> test_input.c
	echo "Sample test file 'test_input.c' created"

# Test with sample file
test_file: $(TARGET) sample
	./$(TARGET) < test_input.c

.PHONY: all clean test sample test_file