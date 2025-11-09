CC = gcc
CFLAGS = -Wall -g -std=c99
YACC = bison -d -y
LEX = flex

# Targets
CODEGEN_TARGET = codegen
ICG_TARGET = icg_compiler

# Object files
CODEGEN_OBJS = main.o codegen.o
ICG_OBJS = y.tab.o icg.o symbol_table.o

# Default target - build both
all: $(ICG_TARGET) $(CODEGEN_TARGET)

# Build the ICG compiler
$(ICG_TARGET): $(ICG_OBJS)
	$(CC) $(CFLAGS) -o $(ICG_TARGET) $(ICG_OBJS) -lfl
	@echo "Build complete: $(ICG_TARGET)"

# Build the code generator
$(CODEGEN_TARGET): $(CODEGEN_OBJS)
	$(CC) $(CFLAGS) -o $(CODEGEN_TARGET) $(CODEGEN_OBJS)
	@echo "Build complete: $(CODEGEN_TARGET)"

# Generate parser
y.tab.c y.tab.h: parse.y
	$(YACC) parse.y

# Generate lexer
lex.yy.c: lex.l y.tab.h
	$(LEX) lex.l

# Compile parser (depends on lexer being generated first)
y.tab.o: y.tab.c lex.yy.c
	$(CC) $(CFLAGS) -c y.tab.c

# Compile lexer
lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

# Compile ICG module
icg.o: icg.c icg.h
	$(CC) $(CFLAGS) -c icg.c

# Compile symbol table
symbol_table.o: symbol_table.c symbol_table.h
	$(CC) $(CFLAGS) -c symbol_table.c

# Compile main.c for codegen
main.o: main.c codegen.h
	$(CC) $(CFLAGS) -c main.c

# Compile codegen.c
codegen.o: codegen.c codegen.h
	$(CC) $(CFLAGS) -c codegen.c

# Clean build artifacts
clean:
	rm -f $(CODEGEN_OBJS) $(ICG_OBJS) $(CODEGEN_TARGET) $(ICG_TARGET)
	rm -f y.tab.c y.tab.h lex.yy.c assembly_code.asm three_address_code.txt
	@echo "Clean complete"

# Run ICG compiler with test input
run_icg: $(ICG_TARGET)
	./$(ICG_TARGET) < test_comprehensive.c

# Run code generator with default test
run: $(CODEGEN_TARGET)
	./$(CODEGEN_TARGET)

# Full pipeline: generate TAC then assembly
pipeline: $(ICG_TARGET) $(CODEGEN_TARGET)
	@echo "=== Step 1: Generating Three-Address Code ==="
	./$(ICG_TARGET) < test_comprehensive.c
	@echo ""
	@echo "=== Step 2: Generating Assembly Code ==="
	./$(CODEGEN_TARGET) three_address_code.txt
	@echo ""
	@echo "=== Pipeline Complete ==="
	@echo "Three-Address Code: three_address_code.txt"
	@echo "Assembly Code: assembly_code.asm"

# Run with specific test file
test1: $(CODEGEN_TARGET)
	@echo "=== Testing Assignment Statement ==="
	./$(CODEGEN_TARGET) test1_tac.txt

test2: $(CODEGEN_TARGET)
	@echo "=== Testing Arithmetic Expressions ==="
	./$(CODEGEN_TARGET) test2_tac.txt

test3: $(CODEGEN_TARGET)
	@echo "=== Testing If Statement ==="
	./$(CODEGEN_TARGET) test3_tac.txt

test4: $(CODEGEN_TARGET)
	@echo "=== Testing While Loop ==="
	./$(CODEGEN_TARGET) test4_tac.txt

test5: $(CODEGEN_TARGET)
	@echo "=== Testing Comprehensive ==="
	./$(CODEGEN_TARGET) test5_tac.txt

# Run all tests
test_all: $(CODEGEN_TARGET)
	@echo "\n=== Running All Tests ===\n"
	@make test1
	@echo "\n"
	@make test2
	@echo "\n"
	@make test3
	@echo "\n"
	@make test4
	@echo "\n"
	@make test5

# Test with C source files (full pipeline)
test_assignment: pipeline_test test_assignment.c
test_expression: pipeline_test test_expression.c
test_if: pipeline_test test_if.c
test_while: pipeline_test test_while.c
test_comprehensive: pipeline_test test_comprehensive.c

pipeline_test: $(ICG_TARGET) $(CODEGEN_TARGET)
	@echo "=== Compiling $(filter %.c,$^) ==="
	./$(ICG_TARGET) < $(filter %.c,$^)
	@echo ""
	@echo "=== Generating Assembly ==="
	./$(CODEGEN_TARGET) three_address_code.txt

.PHONY: all clean run run_icg pipeline test1 test2 test3 test4 test5 test_all
.PHONY: test_assignment test_expression test_if test_while test_comprehensive pipeline_test
