# Simplified Lexical Analyzer (v1)

## Overview
This is a simplified lexical analyzer implementation that satisfies the assignment requirements for recognizing:
- Arithmetic, Relational, Logical, Bitwise and Assignment Operators
- Reserved words: int, float, char, for, while, if, else
- Identifiers
- Integer Constants
- Parentheses and Curly braces

## Token Types Recognized

### 1. Keywords
- `int`, `float`, `char`, `for`, `while`, `if`, `else`

### 2. Operators
- **Arithmetic**: `+`, `-`, `*`, `/`, `%`, `++`, `--`
- **Relational**: `<`, `>`, `<=`, `>=`, `==`, `!=`
- **Logical**: `&&`, `||`, `!`
- **Bitwise**: `&`, `|`, `^`, `~`, `<<`, `>>`
- **Assignment**: `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=`, `^=`, `<<=`, `>>=`

### 3. Delimiters
- **Parentheses**: `(`, `)`
- **Braces**: `{`, `}`

### 4. Other Tokens
- **Identifiers**: Variable names, function names (starting with letter or underscore)
- **Integer Constants**: Decimal numbers

## Transition Diagram

```
START → Character Input
   ↓
   ├─ [a-zA-Z_] → Identifier/Keyword State
   │   ↓
   │   └─ [a-zA-Z0-9_]* → Check if keyword → Return KEYWORD/IDENTIFIER
   │
   ├─ [0-9] → Number State
   │   ↓
   │   └─ [0-9]* → Return INTEGER
   │
   ├─ '+' → Check next character
   │   ├─ '+' → Return ARITHMETIC_OP (++)
   │   ├─ '=' → Return ASSIGNMENT_OP (+=)
   │   └─ other → Return ARITHMETIC_OP (+)
   │
   ├─ '-' → Check next character
   │   ├─ '-' → Return ARITHMETIC_OP (--)
   │   ├─ '=' → Return ASSIGNMENT_OP (-=)
   │   └─ other → Return ARITHMETIC_OP (-)
   │
   ├─ '*', '/', '%' → Check for '='
   │   ├─ '=' → Return ASSIGNMENT_OP
   │   └─ other → Return ARITHMETIC_OP
   │
   ├─ '=' → Check next character
   │   ├─ '=' → Return RELATIONAL_OP (==)
   │   └─ other → Return ASSIGNMENT_OP (=)
   │
   ├─ '<', '>' → Check next character
   │   ├─ '=' → Return RELATIONAL_OP
   │   ├─ same char → Check for '='
   │   │   ├─ '=' → Return ASSIGNMENT_OP (<<=, >>=)
   │   │   └─ other → Return BITWISE_OP (<<, >>)
   │   └─ other → Return RELATIONAL_OP
   │
   ├─ '!' → Check next character
   │   ├─ '=' → Return RELATIONAL_OP (!=)
   │   └─ other → Return LOGICAL_OP (!)
   │
   ├─ '&' → Check next character
   │   ├─ '&' → Return LOGICAL_OP (&&)
   │   ├─ '=' → Return ASSIGNMENT_OP (&=)
   │   └─ other → Return BITWISE_OP (&)
   │
   ├─ '|' → Check next character
   │   ├─ '|' → Return LOGICAL_OP (||)
   │   ├─ '=' → Return ASSIGNMENT_OP (|=)
   │   └─ other → Return BITWISE_OP (|)
   │
   ├─ '^' → Check next character
   │   ├─ '=' → Return ASSIGNMENT_OP (^=)
   │   └─ other → Return BITWISE_OP (^)
   │
   ├─ '~' → Return BITWISE_OP
   │
   ├─ '(' → Return LPAREN
   ├─ ')' → Return RPAREN
   ├─ '{' → Return LBRACE
   ├─ '}' → Return RBRACE
   │
   ├─ [space, tab, newline] → Skip and continue
   │
   ├─ EOF → Return TOKEN_EOF
   │
   └─ other → Return TOKEN_ERROR
```

## Global Variables (lex conventions)
- `yytext`: Points to the current token text
- `yyleng`: Length of current token
- `yylineno`: Current line number
- `yyin`: Input file pointer

## Compilation and Usage

```bash
# Compile
make

# Run with test file
make test

# Or run manually
./lexer test_input.c

# Clean build files
make clean
```

## Example Output
```
=== SIMPLIFIED LEXICAL ANALYZER ===
Analyzing file: test_input.c
=====================================
Line 1: KEYWORD         'int'
Line 1: IDENTIFIER      'main'
Line 1: LPAREN          '('
Line 1: RPAREN          ')'
Line 1: LBRACE          '{'
Line 2: KEYWORD         'int'
Line 2: IDENTIFIER      'x'
Line 2: ASSIGNMENT_OP   '='
Line 2: INTEGER         '10'
...
```

## Features
- Complete finite state automaton implementation
- Proper error handling
- Memory management for dynamic token storage
- Line number tracking
- Follows lex/yacc conventions
