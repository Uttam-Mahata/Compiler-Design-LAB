# Assignment 02: Lexical Analysis (Flex/Lex)

## Overview

This assignment implements a lexical analyzer using **Flex** (Fast Lexical Analyzer Generator), demonstrating automated lexer generation from regular expression specifications.

## Key Concepts

### Flex/Lex Architecture

Flex converts regular expression patterns into efficient DFA-based C code:

```
┌──────────────┐     ┌──────────────┐     ┌──────────────┐
│  Pattern     │ ──► │    Flex      │ ──► │   C Code     │
│  Spec (.l)   │     │  Generator   │     │  (lex.yy.c)  │
└──────────────┘     └──────────────┘     └──────────────┘
```

### Regular Expression to Automata Pipeline

1. **Thompson's Construction**: RE → NFA
2. **Subset Construction**: NFA → DFA
3. **DFA Minimization**: Optimize states
4. **Code Generation**: DFA → Table-driven lexer

## Pattern Specifications

### Basic Flex Patterns

```lex
%{
#include "tokens.h"
%}

%%
"int"           { return INT_TOK; }
"float"         { return FLOAT_TOK; }
"if"            { return IF_TOK; }
"else"          { return ELSE_TOK; }
"while"         { return WHILE_TOK; }
"return"        { return RETURN_TOK; }

[a-zA-Z_][a-zA-Z0-9_]*  { return ID_TOK; }
[0-9]+                   { return INTCONST_TOK; }
[0-9]+\.[0-9]+           { return FLOATCONST_TOK; }

"+"             { return PLUS_TOK; }
"-"             { return MINUS_TOK; }
"*"             { return MULT_TOK; }
"/"             { return DIV_TOK; }
"="             { return ASSIGN_TOK; }
"=="            { return EQ_TOK; }

[ \t\n]         { /* skip whitespace */ }
.               { return ERROR_TOK; }
%%
```

### Token Categories

| Category | Pattern | Example |
|----------|---------|---------|
| Keywords | Literal strings | `"int"`, `"while"` |
| Identifiers | `[a-zA-Z_][a-zA-Z0-9_]*` | `count`, `_var` |
| Integers | `[0-9]+` | `42`, `0` |
| Floats | `[0-9]+\.[0-9]+` | `3.14` |
| Operators | Single/double chars | `+`, `==` |
| Strings | `\"[^\"]*\"` | `"hello"` |

## Implementation Details

### Flex File Structure

A Flex specification has three sections:

```lex
%{
/* C declarations and includes */
#include <stdio.h>
%}

/* Flex definitions */
DIGIT    [0-9]
LETTER   [a-zA-Z]

%%
/* Rules section */
{DIGIT}+    { return NUMBER; }
{LETTER}+   { return WORD; }
%%

/* User code section */
int main() {
    yylex();
    return 0;
}
```

### The Maximal Munch Principle

Flex uses the **maximal munch** (longest match) rule:
- When multiple patterns match, choose the longest match
- For ties, choose the first pattern listed

Example:
```
Input: "integer"
Pattern 1: "int" → matches "int"
Pattern 2: [a-z]+ → matches "integer"
Winner: Pattern 2 (longer match)
```

## Building and Running

### Generate and Compile

```bash
cd Assignment-02-LA/v1

# Generate C code from Flex spec
flex lex.l

# Compile the generated lexer
gcc -o lexer lex.yy.c -lfl
```

### Using with Makefile

```bash
make clean
make
./lexer < input.c
```

## NFA to DFA Conversion

### Thompson's Construction Example

For pattern `a(b|c)*`:

```
NFA:
    ε         ε──►(b)──ε
(q0)──►(q1)──►|         |──►(q3)──ε──►((q4))
              ε──►(c)──ε
              ▲         │
              └────ε────┘
```

### Subset Construction

Convert NFA states to DFA states by computing ε-closures:

| DFA State | NFA States | On 'a' | On 'b' | On 'c' |
|-----------|------------|--------|--------|--------|
| S0 | {q0} | S1 | - | - |
| S1 | {q1,q3,q4} | - | S2 | S2 |
| S2 | {q1,q3,q4} | - | S2 | S2 |

## Error Handling

### Spelling Error Detection

The lexer can detect potential spelling errors:

```lex
"teh"   { printf("Did you mean 'the'?\n"); }
"recieve" { printf("Did you mean 'receive'?\n"); }
```

### Recovery Strategies

1. **Skip character**: Continue after unknown character
2. **Panic mode**: Skip to next delimiter
3. **Error tokens**: Return special error token

## Files

| File | Description |
|------|-------------|
| `v1/lex.l` | Flex specification |
| `v1/lex.yy.c` | Generated C code |
| `v1/README.md` | Implementation guide |
| `v1/THEORY.md` | Theoretical foundations |
| `v1/THEORY.tex` | LaTeX documentation |

## Learning Outcomes

After completing this assignment, you will understand:
- ✅ Flex/Lex pattern specifications
- ✅ RE → NFA → DFA conversion
- ✅ Thompson's construction algorithm
- ✅ Maximal munch principle
- ✅ Automated lexer generation

## Related Pages

- [Assignment 01: Manual Lexer](Assignment-01-Lexical-Analysis-Manual)
- [Assignment 03: Syntax Analysis](Assignment-03-Syntax-Analysis)
- [Theory Index](Theory-Index)
- [Home](Home)

---

**Previous:** [Assignment 01: Lexical Analysis (Manual)](Assignment-01-Lexical-Analysis-Manual)
**Next:** [Assignment 03: Syntax Analysis](Assignment-03-Syntax-Analysis)
