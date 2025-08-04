# Complete Transition Diagram for Lexical Analyzer

This project implements a complete transition diagram design for a lexical analyzer following the principles of `yylex`, `yytext`, `yyleng`, and `yylineno`.

## Files Overview

### C Implementation Files
- **`transition_diagram_lexer.c`**: Complete C implementation of the transition diagram-based lexer
- **`Makefile_transition`**: Makefile to compile the transition diagram lexer
- **`transition_test.c`**: Simple test file for demonstrating the lexer
- **`compare_lexers.sh`**: Script to compare original and transition diagram lexers

### Documentation Files
- **`transition_diagram_report.tex`**: Complete LaTeX report explaining the theory and implementation
- **`complete_transition_diagram.tex`**: Standalone TikZ diagram showing the complete state machine

### Original Implementation (v1/ directory)
- **`lex.c`**, **`lex.h`**: Original lexer implementation
- **`main.c`**: Original main program
- **`test_input.c`**: Comprehensive test file

## How to Use

### 1. Compile and Run the Transition Diagram Lexer

```bash
# Compile the transition diagram lexer
make -f Makefile_transition

# Run on test file
./transition_lexer transition_test.c

# Run on the comprehensive test
./transition_lexer v1/test_input.c
```

### 2. Compare Both Lexers

```bash
# Run the comparison script
./compare_lexers.sh
```

### 3. Generate Documentation

```bash
# Compile the LaTeX report (requires LaTeX with TikZ)
pdflatex transition_diagram_report.tex

# Generate the standalone transition diagram
pdflatex complete_transition_diagram.tex
```

## Key Features

### Transition Diagram Implementation
- **Explicit State Management**: Each state in the finite automaton is explicitly represented
- **State Transition Logging**: Shows exactly how the lexer moves between states
- **Complete Operator Support**: Handles all arithmetic, relational, logical, bitwise, and assignment operators
- **yylex Compatibility**: Uses the same global variables (`yytext`, `yyleng`, `yylineno`, `yyin`)

### Token Types Recognized
- **Identifiers**: Variable and function names
- **Keywords**: `int`, `float`, `char`, `for`, `while`, `if`, `else`, `return`
- **Integer Constants**: Numeric literals
- **Operators**: All C-style operators including compound assignments
- **Delimiters**: Parentheses, braces, semicolons
- **Error Tokens**: Invalid character sequences

### State Machine States
1. **STATE_START (0)**: Initial state
2. **STATE_IDENTIFIER (1)**: Reading identifiers/keywords
3. **STATE_INTEGER (2)**: Reading integer constants
4. **STATE_PLUS (3)**: Processing `+` variations (`+`, `++`, `+=`)
5. **STATE_MINUS (4)**: Processing `-` variations (`-`, `--`, `-=`)
6. **STATE_MULTIPLY (5)**: Processing `*` variations (`*`, `*=`)
7. **STATE_DIVIDE (6)**: Processing `/` variations (`/`, `/=`)
8. **STATE_MODULO (7)**: Processing `%` variations (`%`, `%=`)
9. **STATE_ASSIGN (8)**: Processing `=` variations (`=`, `==`)
10. **STATE_LESS (9)**: Processing `<` variations (`<`, `<=`, `<<`)
11. **STATE_GREATER (10)**: Processing `>` variations (`>`, `>=`, `>>`)
12. **STATE_NOT (11)**: Processing `!` variations (`!`, `!=`)
13. **STATE_AND (12)**: Processing `&` variations (`&`, `&&`, `&=`)
14. **STATE_OR (13)**: Processing `|` variations (`|`, `||`, `|=`)
15. **STATE_XOR (14)**: Processing `^` variations (`^`, `^=`)
16. **STATE_LSHIFT (15)**: Processing `<<` variations (`<<`, `<<=`)
17. **STATE_RSHIFT (16)**: Processing `>>` variations (`>>`, `>>=`)
18. **STATE_FINAL (17)**: Accept state

## Example Output

For input `int x = 42;`, the transition diagram lexer shows:

```
=== Transition Diagram Execution ===
State 0 --(i)--> State 1
State 1 --(n)--> State 1
State 1 --(t)--> State 1
State IDENTIFIER --(other)--> Final State
Result: Line 1: KEYWORD         'int'

State 0 --(x)--> State 1
State IDENTIFIER --(other)--> Final State
Result: Line 1: IDENTIFIER      'x'

State 0 --(=)--> State 8
State ASSIGN --(other)--> Final State
Result: Line 1: ASSIGNMENT_OP   '='

State 0 --(4)--> State 2
State 2 --(2)--> State 2
State INTEGER --(other)--> Final State
Result: Line 1: INTEGER         '42'

State START --(;)--> Final State
Result: Line 1: SEMICOLON       ';'
```

## Advantages of Transition Diagram Approach

1. **Visual Clarity**: Each state and transition is explicit
2. **Debugging**: Easy to trace execution and find issues
3. **Maintainability**: Clear separation of concerns for each state
4. **Educational**: Perfect for understanding lexical analysis theory
5. **Extensibility**: Easy to add new operators or token types

## Integration with Compiler Design Concepts

This implementation demonstrates:
- **Finite State Automata**: Complete FSA implementation
- **Lexical Analysis Theory**: Practical application of theoretical concepts
- **yylex Interface**: Standard lexer interface compatibility
- **Error Handling**: Proper error state management
- **Memory Management**: Safe buffer and token management

## LaTeX Documentation

The included LaTeX report provides:
- Theoretical foundation of transition diagrams
- Detailed state definitions and transitions
- Mathematical notation for state transitions
- Complete TikZ diagrams of the state machine
- Implementation architecture explanation
- Sample execution traces

This implementation serves as both a practical lexical analyzer and an educational tool for understanding how lexical analysis works at the state machine level.
