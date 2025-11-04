#!/bin/bash

# Test script for C Language Subset Parser
# Assignment 03 - Compiler Design Lab

echo "======================================================"
echo "       C LANGUAGE SUBSET PARSER - TEST SUITE"
echo "======================================================"
echo

# Check if parser exists
if [ ! -f "./parser" ]; then
    echo "Error: Parser not found. Please run 'make' first."
    exit 1
fi

# Function to run test and display results
run_test() {
    local test_file=$1
    local test_name=$2
    
    echo "------------------------------------------------------"
    echo "TEST: $test_name"
    echo "FILE: $test_file"
    echo "------------------------------------------------------"
    
    if [ -f "$test_file" ]; then
        echo "INPUT CODE:"
        cat "$test_file"
        echo
        echo "PARSER OUTPUT:"
        ./parser < "$test_file"
    else
        echo "Test file $test_file not found!"
    fi
    
    echo
    echo "Press Enter to continue..."
    read
}

# Test 1: Simple main function
run_test "test_simple.c" "Simple Main Function with Variable Declarations"

# Test 2: Control structures
run_test "test_control.c" "Control Structures (if-else, for, while)"

# Test 3: User-defined functions  
run_test "test_functions.c" "User-Defined Functions and Function Calls"

# Test 4: Complex expressions
run_test "test_expressions.c" "Complex Expressions and Operators"

# Test 5: Syntax errors
run_test "test_errors.c" "Syntax Error Detection"

# Interactive test
echo "------------------------------------------------------"
echo "INTERACTIVE TEST"
echo "------------------------------------------------------"
echo "You can now enter C code directly. Type your code and"
echo "press Ctrl+D when finished to parse it."
echo
echo "Example simple program:"
echo "int main() { int x = 5; return x; }"
echo
echo "Enter your C code:"
./parser

echo "======================================================"
echo "               TEST SUITE COMPLETED"
echo "======================================================"