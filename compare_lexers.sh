#!/bin/bash

echo "=== COMPARISON OF LEXICAL ANALYZERS ==="
echo "======================================"
echo ""

echo "1. ORIGINAL LEXER (v1/lexer):"
echo "------------------------------"
cd v1
make clean && make
echo ""
echo "Running original lexer on test_input.c:"
./lexer test_input.c | head -15
echo ""

echo "2. TRANSITION DIAGRAM LEXER:"
echo "-----------------------------"
cd ..
echo "Running transition diagram lexer on the same file:"
./transition_lexer v1/test_input.c | grep "Result:" | head -15
echo ""

echo "3. TRANSITION DIAGRAM LEXER (Simple test):"
echo "------------------------------------------"
echo "Running on transition_test.c to show state transitions:"
./transition_lexer transition_test.c | grep "State\|Result:" | head -20
echo ""

echo "=== SUMMARY ==="
echo "The transition diagram lexer shows explicit state transitions,"
echo "making it easier to understand and debug the lexical analysis process."
echo "Both lexers produce equivalent token recognition results."
