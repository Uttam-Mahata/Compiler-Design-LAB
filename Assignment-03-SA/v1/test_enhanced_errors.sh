#!/bin/bash

echo "=== ENHANCED SYNTAX ERROR DETECTION TESTS ==="
echo

# Test 1: Missing semicolon
echo "Test 1: Missing semicolon after declaration"
echo "int main() { int x = 5 return 0; }" | ./parser
echo

# Test 2: Missing closing parenthesis
echo "Test 2: Missing closing parenthesis in if statement"
echo "int main() { if (x > 5 { x = 10; } return 0; }" | ./parser
echo

# Test 3: Missing opening parenthesis
echo "Test 3: Missing opening parenthesis in if statement"
echo "int main() { if x > 5) { x = 10; } return 0; }" | ./parser
echo

# Test 4: Missing comma in declaration
echo "Test 4: Missing comma in variable declaration"
echo "int main() { int x, y z; return 0; }" | ./parser
echo

# Test 5: Missing semicolon in assignment
echo "Test 5: Missing semicolon after assignment"
echo "int main() { int x; x = 5 return 0; }" | ./parser
echo

# Test 6: Missing closing bracket
echo "Test 6: Missing closing bracket in array access"
echo "int main() { int arr[10]; arr[0 = 5; return 0; }" | ./parser
echo

# Test 7: Invalid operator context
echo "Test 7: Invalid assignment operator"
echo "int main() { int x; x == 5; return 0; }" | ./parser
echo

# Test 8: Missing semicolon in for loop
echo "Test 8: Missing semicolon in for loop"
echo "int main() { for (int i = 0 i < 10; i++) { } return 0; }" | ./parser
echo

echo "=== ALL TESTS COMPLETED ==="