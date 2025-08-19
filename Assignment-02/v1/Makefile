CC = gcc
FLEX = flex
CFLAGS = -Wall -g

# Target executable
TARGET = lexer_with_errors

# Source files
LEX_SOURCE = lex.l
LEX_OUTPUT = lex.yy.c

# Default target
all: $(TARGET)

# Build the lexer with error detection
$(TARGET): $(LEX_OUTPUT)
	$(CC) $(CFLAGS) -o $(TARGET) $(LEX_OUTPUT) -lfl

# Generate C code from lex file
$(LEX_OUTPUT): $(LEX_SOURCE)
	$(FLEX) $(LEX_SOURCE)

# Test with error cases
test_errors: $(TARGET)
	@echo "=== Testing with Error Cases ==="
	./$(TARGET) < error_test_cases.c

# Test with correct syntax
test_correct: $(TARGET)
	@echo "=== Testing with Correct Syntax ==="
	./$(TARGET) < correct_test.c

# Test with specific error types
test_specific: $(TARGET)
	@echo "=== Testing Specific Error Types ==="
	./$(TARGET) < specific_errors.c

# Test with original input
test_original: $(TARGET)
	@echo "=== Testing with Original Input ==="
	./$(TARGET) < input.c

# Run all tests
test_all: test_correct test_errors test_specific test_original

# Clean generated files
clean:
	rm -f $(LEX_OUTPUT) $(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all           - Build the lexer with error detection"
	@echo "  test_correct  - Test with correct syntax file"
	@echo "  test_errors   - Test with error cases file"
	@echo "  test_specific - Test with specific error types"
	@echo "  test_original - Test with original input file"
	@echo "  test_all      - Run all tests"
	@echo "  clean         - Remove generated files"
	@echo "  help          - Show this help message"

.PHONY: all test_errors test_correct test_specific test_original test_all clean help