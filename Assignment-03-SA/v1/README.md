# C Language Subset Parser - Assignment 03

## Overview
This project implements a comprehensive YACC (Yet Another Compiler Compiler) specification for parsing a subset of the C programming language. The parser can handle various C language constructs including main functions, user-defined functions, declarations, assignments, control structures, and expressions.

## Features

### Supported Language Constructs

#### 1. Main Function
- Main function with and without parameters
- Return statements with and without values

#### 2. Statements
- **Local/Global Declarations**: Variable declarations at function and global scope
- **Assignment Statements**: All types of assignment operators (=, +=, -=, *=, /=, %=)
- **Conditional Statements**: if, if-else constructs
- **Iterative Statements**: while, for, do-while loops
- **Function Calls**: Function calls with and without arguments

#### 3. User-Defined Functions
- Function declarations and definitions
- Functions with parameters
- Function calls with argument passing

### Supported Data Types
- `int` - Integer type
- `float` - Floating point type  
- `char` - Character type

### Supported Operators
- **Arithmetic**: +, -, *, /, %
- **Relational**: <, >, <=, >=, ==, !=
- **Logical**: &&, ||, !
- **Bitwise**: &, |, ^, ~, <<, >>
- **Assignment**: =, +=, -=, *=, /=, %=
- **Increment/Decrement**: ++, --
- **Ternary**: ? :

### Error Detection
- Syntax error detection with line numbers
- Comprehensive error messages
- Recovery mechanisms for common syntax errors

## File Structure

```
Assignment-03/v1/
├── lex.l              # Lexical analyzer specification
├── parse.y            # YACC parser specification  
├── tok_def.h          # Token definitions header file
├── Makefile           # Build configuration
├── test_simple.c      # Test case: Simple main function
├── test_control.c     # Test case: Control structures
├── test_functions.c   # Test case: User-defined functions
├── test_expressions.c # Test case: Complex expressions
├── test_errors.c      # Test case: Syntax errors
└── README.md          # This file
```

## Prerequisites

To build and run this parser, you need:
- GCC compiler
- Flex (lexical analyzer generator)
- Bison/YACC (parser generator)
- Make utility

### Installation on Ubuntu/Debian:
```bash
sudo apt-get install gcc flex bison make
```

### Installation on CentOS/RHEL:
```bash
sudo yum install gcc flex bison make
```

## Building the Parser

### Using Make:
```bash
# Build the parser
make

# or build everything (default target)
make all
```

### Manual Build:
```bash
# Generate parser from YACC specification
yacc -d parse.y

# Generate lexer from Flex specification  
flex lex.l

# Compile the parser
gcc -o parser y.tab.c -ly -lfl
```

## Running the Parser

### From File Input:
```bash
# Test with a specific file
./parser < test_simple.c

# Test all provided examples
./parser < test_control.c
./parser < test_functions.c
./parser < test_expressions.c
./parser < test_errors.c
```

### Interactive Mode:
```bash
# Run parser and type input directly
./parser
# Type your C code and press Ctrl+D to parse
```

### Quick Test:
```bash
# Run the built-in test
make test
```

## Sample Test Cases

### 1. Simple Main Function (`test_simple.c`)
```c
int main() {
    int x, y;
    float z;
    x = 10;
    y = 20;
    z = 3.14;
    return 0;
}
```

### 2. Control Structures (`test_control.c`)
```c
int main() {
    int i, n, sum;
    
    for(i = 1; i <= n; i++) {
        sum = sum + i;
    }
    
    if(sum > 50) {
        sum = sum * 2;
    } else {
        sum = sum + 1;
    }
    
    while(sum > 0) {
        sum = sum - 1;
    }
    
    return sum;
}
```

### 3. User-Defined Functions (`test_functions.c`)
```c
int add(int a, int b);

int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(5, 3);
    return 0;
}
```

## Parser Output

### Successful Parse:
```
=== C LANGUAGE SUBSET PARSER ===
Parsing input...

SYNTAX OK (Line 2): Local variable declaration
SYNTAX OK (Line 3): Local variable declaration  
SYNTAX OK (Line 4): Assignment statement
SYNTAX OK (Line 5): Assignment statement
SYNTAX OK (Line 6): Assignment statement
SYNTAX OK (Line 7): Return statement with value
SYNTAX OK (Line 8): Compound statement
SYNTAX OK (Line 1): Main function definition
SYNTAX OK (Line 8): Complete C program

=== PARSING COMPLETED SUCCESSFULLY ===
Total syntax errors: 0

=== PARSING SUCCESSFUL ===
No syntax errors found!
```

### Error Detection:
```
SYNTAX ERROR (Line 2): syntax error near 'y'
SYNTAX ERROR (Line 3): syntax error near 'return'

=== PARSING FAILED ===
Syntax errors found at line 3
```

## Grammar Features

### Expression Precedence
The parser implements proper operator precedence and associativity:
1. Assignment operators (right associative)
2. Ternary operator
3. Logical OR
4. Logical AND  
5. Bitwise OR
6. Bitwise XOR
7. Bitwise AND
8. Equality operators
9. Relational operators
10. Shift operators
11. Additive operators
12. Multiplicative operators
13. Unary operators
14. Postfix operators

### Scope Handling
- Global scope for global variables and function declarations
- Local scope tracking for compound statements
- Proper nesting of scopes in nested blocks

### Error Recovery
- Panic mode recovery for syntax errors
- Detailed error messages with line numbers
- Continuation after errors to find multiple syntax issues

## Limitations

### Current Limitations:
1. No semantic analysis (variable declaration checking)
2. Limited to basic C constructs
3. No preprocessor directives support
4. No struct/union/enum support
5. No pointer operations
6. No string manipulation beyond string constants

### Possible Extensions:
1. Symbol table implementation
2. Type checking
3. More C language features
4. Code generation
5. Optimization passes

## Troubleshooting

### Common Build Issues:

1. **Flex/Bison not found:**
   ```bash
   sudo apt-get install flex bison
   ```

2. **Linking errors:**
   ```bash
   gcc -o parser y.tab.c -ly -lfl
   ```

3. **Permission denied:**
   ```bash
   chmod +x parser
   ```

### Common Usage Issues:

1. **Parser hangs waiting for input:**
   - Use file redirection: `./parser < input.c`
   - Or type input and press Ctrl+D to end input

2. **No output:**
   - Check if input file exists and has proper C syntax
   - Verify the parser was built successfully

## Testing

### Automated Testing:
```bash
# Test all examples
for file in test_*.c; do
    echo "Testing $file:"
    ./parser < "$file"
    echo "------------------------"
done
```

### Manual Testing:
Create your own C code files and test them:
```bash
echo "int main() { return 0; }" > simple.c
./parser < simple.c
```

## Assignment Requirements Fulfilled

✅ **Main function**: Support for main function with and without parameters  
✅ **Local/Global declarations**: Variable declarations at multiple scopes  
✅ **Assignment statements**: All assignment operators supported  
✅ **Conditional statements**: if, if-else constructs  
✅ **Iterative statements**: while, for, do-while loops  
✅ **Function calls**: Function calls with arguments  
✅ **User-defined functions**: Function declarations and definitions  
✅ **Variable declaration rules**: Variables declared before use  
✅ **Syntax error detection**: Error detection with line numbers  

## Authors

Developed as part of Compiler Design Lab Assignment 03.

## License

This project is developed for educational purposes as part of coursework.