# Assignment 03: Syntax Analysis (YACC/Bison)

## Overview

This assignment implements a parser using **YACC/Bison** (Yet Another Compiler Compiler), demonstrating syntax analysis through LALR(1) parsing.

## Key Concepts

### Context-Free Grammars (CFG)

A CFG is defined as a 4-tuple G = (V, Σ, P, S):
- **V**: Set of non-terminal symbols
- **Σ**: Set of terminal symbols (tokens)
- **P**: Set of production rules
- **S**: Start symbol

### LALR(1) Parsing

LALR(1) = **L**ook **A**head **L**eft-to-right **R**ightmost derivation with **1** lookahead token.

Key properties:
- Bottom-up parsing (shift-reduce)
- Efficient parse table construction
- Handles most practical grammars

## Grammar Specification

### Basic YACC Grammar

```yacc
%{
#include <stdio.h>
#include <stdlib.h>
%}

%token INT_TOK FLOAT_TOK VOID_TOK
%token ID_TOK INTCONST_TOK FLOATCONST_TOK
%token IF_TOK ELSE_TOK WHILE_TOK FOR_TOK RETURN_TOK
%token PLUS_TOK MINUS_TOK MULT_TOK DIV_TOK
%token ASSIGN_TOK EQ_TOK NE_TOK LT_TOK GT_TOK LE_TOK GE_TOK
%token LPAREN_TOK RPAREN_TOK LBRACE_TOK RBRACE_TOK
%token SEMICOLON_TOK COMMA_TOK

%left PLUS_TOK MINUS_TOK
%left MULT_TOK DIV_TOK

%%

program
    : declaration_list
    ;

declaration_list
    : declaration
    | declaration_list declaration
    ;

declaration
    : type_specifier ID_TOK SEMICOLON_TOK
    | type_specifier ID_TOK ASSIGN_TOK expression SEMICOLON_TOK
    | function_declaration
    ;

type_specifier
    : INT_TOK
    | FLOAT_TOK
    | VOID_TOK
    ;

function_declaration
    : type_specifier ID_TOK LPAREN_TOK parameter_list RPAREN_TOK compound_statement
    ;
%%
```

### Production Rules Summary

#### Statements

| Rule | Production |
|------|------------|
| Statement | `expression_statement \| compound_statement \| selection_statement \| iteration_statement \| return_statement` |
| Compound | `{ statement_list }` |
| Selection | `if ( expression ) statement [else statement]` |
| Iteration | `while ( expression ) statement` |
| Return | `return [expression] ;` |

#### Expressions

| Rule | Production |
|------|------------|
| Expression | `assignment_expression \| expression , assignment_expression` |
| Assignment | `ID = expression` |
| Logical OR | `logical_and \| logical_or \|\| logical_and` |
| Relational | `additive relop additive` |
| Additive | `term \| additive +/- term` |
| Term | `factor \| term */÷ factor` |
| Factor | `( expression ) \| ID \| CONSTANT \| call` |

## Shift-Reduce Parsing

### Parsing Actions

1. **Shift**: Push token onto stack
2. **Reduce**: Replace RHS with LHS of production
3. **Accept**: Parsing complete successfully
4. **Error**: Syntax error detected

### Example Parse

For input: `x = 5 + 3;`

| Stack | Input | Action |
|-------|-------|--------|
| $ | x = 5 + 3 ; $ | Shift x |
| $ x | = 5 + 3 ; $ | Shift = |
| $ x = | 5 + 3 ; $ | Shift 5 |
| $ x = 5 | + 3 ; $ | Reduce: factor → CONST |
| $ x = factor | + 3 ; $ | Reduce: term → factor |
| $ x = term | + 3 ; $ | Reduce: expr → term |
| $ x = expr | + 3 ; $ | Shift + |
| $ x = expr + | 3 ; $ | Shift 3 |
| $ x = expr + 3 | ; $ | Reduce: factor → CONST |
| $ x = expr + factor | ; $ | Reduce: term → factor |
| $ x = expr + term | ; $ | Reduce: expr → expr + term |
| $ x = expr | ; $ | Reduce: assign → ID = expr |
| $ assign | ; $ | Shift ; |
| $ assign ; | $ | Reduce: stmt → assign ; |
| $ stmt | $ | Accept |

## Parse Tree Construction

For `x = a + b * c`:

```
            assignment
           /    |     \
         ID    '='   expression
         |            /   |   \
         x         expr  '+'  term
                    |        /  |  \
                  term    term '*' factor
                    |       |       |
                 factor   factor    ID
                    |       |       |
                   ID      ID       c
                    |       |
                    a       b
```

## Error Handling

### Error Recovery Strategies

```yacc
statement
    : expression_statement
    | compound_statement
    | error SEMICOLON_TOK
        { yyerrok; printf("Recovered from error\n"); }
    ;
```

### Error Types Detected

| Error Type | Example | Message |
|------------|---------|---------|
| Missing semicolon | `int x` | "Expected ';'" |
| Unbalanced parens | `if (x` | "Expected ')'" |
| Missing operand | `x + ;` | "Expected expression" |
| Invalid declaration | `int 123` | "Invalid identifier" |

## Building and Running

### Build the Parser

```bash
cd Assignment-03-SA/v1

# Generate parser
bison -d parse.y
flex lex.l

# Compile
gcc -o parser y.tab.c lex.yy.c -lfl

# Run
./parser < test_input.c
```

### Using Makefile

```bash
make clean
make
./parser < test_input.c
```

## Files

| File | Description |
|------|-------------|
| `v1/parse.y` | YACC grammar specification |
| `v1/lex.l` | Flex lexer for parser |
| `v1/README.md` | Implementation guide |
| `v1/THEORY.md` | Parsing theory |
| `v1/SUMMARY.md` | Production rules catalog |
| `v1/ENHANCED_ERROR_DETECTION.md` | Error handling details |

## Operator Precedence

YACC handles operator precedence with declarations:

```yacc
%left PLUS_TOK MINUS_TOK      /* Lowest precedence */
%left MULT_TOK DIV_TOK        /* Higher precedence */
%right UMINUS                  /* Unary minus */
```

**%left**: Left associative (a + b + c = (a + b) + c)
**%right**: Right associative (a = b = c = a = (b = c))
**%nonassoc**: No chaining allowed

## Learning Outcomes

After completing this assignment, you will understand:
- ✅ Context-free grammar specification
- ✅ LALR(1) parsing algorithm
- ✅ Shift-reduce parsing mechanics
- ✅ Parse tree construction
- ✅ Error recovery strategies
- ✅ Operator precedence handling

## Related Pages

- [Assignment 02: Lexical Analysis (Flex)](Assignment-02-Lexical-Analysis-Flex)
- [Assignment 04: Type Checking](Assignment-04-Type-Checking)
- [Theory Index](Theory-Index)
- [Home](Home)

---

**Previous:** [Assignment 02: Lexical Analysis (Flex)](Assignment-02-Lexical-Analysis-Flex)
**Next:** [Assignment 04: Type Checking](Assignment-04-Type-Checking)
