# Syntax Analysis using YACC/Bison - Assignment 03 v1

## Overview
This document provides comprehensive theoretical documentation for the syntax analyzer (parser) implementation using YACC/Bison in Assignment 03 Version 1. It covers context-free grammars, parse trees, parsing algorithms, and the equivalence between grammar rules and generated code.

## Table of Contents
1. [Introduction to Syntax Analysis](#introduction-to-syntax-analysis)
2. [Context-Free Grammars](#context-free-grammars)
3. [YACC/Bison Fundamentals](#yaccbison-fundamentals)
4. [Parsing Algorithms](#parsing-algorithms)
5. [Grammar Rules to Parse Tree](#grammar-rules-to-parse-tree)
6. [Implementation Details](#implementation-details)
7. [Error Handling and Recovery](#error-handling-and-recovery)
8. [Code-Theory Equivalence](#code-theory-equivalence)

## Introduction to Syntax Analysis

### What is Syntax Analysis?
Syntax analysis (parsing) is the second phase of a compiler that:
- Takes token stream from lexical analyzer
- Checks if tokens conform to language grammar
- Builds parse tree or abstract syntax tree (AST)
- Reports syntax errors

### Compiler Pipeline Position
```
Token Stream → [Syntax Analyzer] → Parse Tree → [Semantic Analyzer]
    ↑                   ↓
Lexical Analyzer    Error Handler
```

### Role in Compiler Design

**Input:** Token sequence from lexer
```
INT_TOK ID_TOK("x") ASSIGN_TOK INTCONST_TOK("10") SEMICOLON_TOK
```

**Output:** Parse tree or syntax error
```
assignment_statement
├── ID_TOK: "x"
├── ASSIGN_TOK
└── expression
    └── INTCONST_TOK: "10"
```

## Context-Free Grammars

### Formal Definition
A Context-Free Grammar (CFG) is a 4-tuple G = (V, T, P, S) where:
- **V**: Set of non-terminal symbols (variables)
- **T**: Set of terminal symbols (tokens)
- **P**: Set of production rules
- **S**: Start symbol (S ∈ V)

### Grammar for C Subset

**Non-terminals (V):**
```
program, main_function, statement, expression, 
declaration, compound_statement, etc.
```

**Terminals (T):**
```
INT_TOK, FLOAT_TOK, ID_TOK, INTCONST_TOK, ASSIGN_TOK,
LPAREN_TOK, RPAREN_TOK, SEMICOLON_TOK, etc.
```

**Production Rules (P):**
```
program → main_function
program → global_declarations main_function
main_function → INT_TOK ID_TOK LPAREN_TOK RPAREN_TOK compound_statement
statement → assignment_statement
statement → conditional_statement
...
```

**Start Symbol (S):**
```
program
```

### Derivation Example

**Grammar:**
```
statement → assignment_statement
assignment_statement → ID_TOK ASSIGN_TOK expression SEMICOLON_TOK
expression → INTCONST_TOK
```

**Derivation for "x = 10;":**
```
statement 
⇒ assignment_statement
⇒ ID_TOK ASSIGN_TOK expression SEMICOLON_TOK
⇒ ID_TOK ASSIGN_TOK INTCONST_TOK SEMICOLON_TOK
⇒ x = 10;
```

### Parse Tree

```
        statement
            |
    assignment_statement
    /      |      |      \
ID_TOK  ASSIGN  expression  SEMICOLON
 "x"      "="       |          ";"
                INTCONST
                  "10"
```

## YACC/Bison Fundamentals

### What is YACC?
YACC (Yet Another Compiler Compiler) is a parser generator that:
- Takes grammar specification
- Generates LALR(1) parser in C
- Handles shift/reduce and reduce/reduce conflicts
- Integrates with Lex/Flex for tokenization

### YACC File Structure

```yacc
%{
/* C declarations */
#include <stdio.h>
%}

/* Token declarations */
%token INT_TOK FLOAT_TOK ID_TOK

/* Grammar rules */
%%
program: main_function { printf("Valid program\n"); }
       ;

main_function: INT_TOK ID_TOK LPAREN_TOK RPAREN_TOK compound_statement
             ;

%%

/* C code */
int main() {
    yyparse();
    return 0;
}
```

### Three Sections

1. **Declarations Section** (`%{ %}`)
   - C headers and declarations
   - Token type definitions
   - Precedence and associativity

2. **Grammar Rules Section** (`%% ... %%`)
   - Production rules
   - Semantic actions in `{ }`

3. **C Code Section** (after second `%%`)
   - Main function
   - Error handlers
   - Utility functions

## Parsing Algorithms

### Bottom-Up Parsing (LR Parsing)

YACC generates an LALR(1) parser, which is a type of LR parser.

**LR Parsing:**
- **L**: Left-to-right scan of input
- **R**: Rightmost derivation in reverse
- **(1)**: One token lookahead

### LALR(1) Parser Components

1. **Parse Stack**: Stores states and grammar symbols
2. **Parse Table**: 
   - ACTION table: shift/reduce decisions
   - GOTO table: next state transitions
3. **Input Buffer**: Remaining tokens

### Parsing Actions

**Four possible actions:**

1. **Shift**: Push token onto stack
2. **Reduce**: Apply production rule (pop RHS, push LHS)
3. **Accept**: Parsing successful
4. **Error**: Syntax error detected

### Parsing Example

**Grammar:**
```
E → E + T
E → T
T → ID
```

**Input:** `x + y`

**Parse Steps:**
```
Stack          Input       Action
------         -----       ------
$              x + y $     shift x
$ x            + y $       reduce by T → ID
$ T            + y $       reduce by E → T
$ E            + y $       shift +
$ E +          y $         shift y
$ E + y        $           reduce by T → ID
$ E + T        $           reduce by E → E + T
$ E            $           accept
```

### Shift/Reduce Conflicts

**Example ambiguous grammar:**
```
statement → IF expr THEN statement
          | IF expr THEN statement ELSE statement
```

**Conflict:** When seeing ELSE, should we:
- **Shift** ELSE (attach to inner IF)
- **Reduce** (attach to outer IF)

**Resolution:** YACC uses precedence rules (shift has priority)

## Grammar Rules to Parse Tree

### Production Rule Format

**YACC Syntax:**
```yacc
non_terminal: symbol1 symbol2 ... symbolN { action }
            | alternative1 alternative2 { action }
            ;
```

**Example:**
```yacc
statement: expression_statement { $$ = $1; }
         | compound_statement   { $$ = $1; }
         | conditional_statement { $$ = $1; }
         ;
```

### Semantic Actions

**Value Stack ($$ and $N):**
- `$$`: Value of LHS non-terminal
- `$1, $2, ..., $N`: Values of RHS symbols

**Example:**
```yacc
expression: expression ADD_TOK term 
          { $$ = create_node("+", $1, $3); }
          ;
```

### Parse Tree Construction

**Grammar:**
```yacc
compound_statement: LBRACE_TOK statement_list RBRACE_TOK
                  { $$ = make_compound($2); }
                  ;

statement_list: statement_list statement
              { $$ = append_statement($1, $2); }
              | /* empty */
              { $$ = NULL; }
              ;
```

**Resulting Tree:**
```
compound_statement
    |
statement_list
├── statement 1
├── statement 2
└── statement 3
```

## Implementation Details

### Token Communication (Lex → Yacc)

**Lex side (lex.l):**
```lex
"int"       { return INT_TOK; }
[a-zA-Z_]+  { yylval.sval = strdup(yytext); return ID_TOK; }
[0-9]+      { yylval.ival = atoi(yytext); return INTCONST_TOK; }
```

**Yacc side (parse.y):**
```yacc
%union {
    int ival;
    char *sval;
}

%token <ival> INTCONST_TOK
%token <sval> ID_TOK
%token INT_TOK
```

### Operator Precedence

**Declaration in YACC:**
```yacc
%left OR_TOK
%left AND_TOK
%left BIT_OR_TOK
%left BIT_XOR_TOK
%left BIT_AND_TOK
%left EQ_TOK NEQ_TOK
%left LT_TOK GT_TOK LE_TOK GE_TOK
%left BIT_LSHIFT_TOK BIT_RSHIFT_TOK
%left ADD_TOK SUB_TOK
%left MUL_TOK DIV_TOK MOD_TOK
%right ASSIGN_TOK
%right NOT_TOK BIT_NOT_TOK
%left INC_TOK DEC_TOK
```

**Precedence Levels (low to high):**
1. Logical OR (||)
2. Logical AND (&&)
3. Bitwise OR (|)
4. Bitwise XOR (^)
5. Bitwise AND (&)
6. Equality (==, !=)
7. Relational (<, >, <=, >=)
8. Shift (<<, >>)
9. Additive (+, -)
10. Multiplicative (*, /, %)
11. Assignment (=, +=, etc.) - right associative
12. Unary (!, ~) - right associative
13. Postfix (++, --)

### Grammar Productions

**Main Function:**
```yacc
main_function: data_type ID_TOK LPAREN_TOK RPAREN_TOK compound_statement
             {
                 printf("SYNTAX OK: Main function definition\n");
                 $$ = create_main_function($1, $2, NULL, $5);
             }
             | data_type ID_TOK LPAREN_TOK parameter_list RPAREN_TOK 
               compound_statement
             {
                 printf("SYNTAX OK: Main function with parameters\n");
                 $$ = create_main_function($1, $2, $4, $6);
             }
             ;
```

**Statements:**
```yacc
statement: expression_statement
         | compound_statement
         | conditional_statement
         | iterative_statement
         | return_statement
         | assignment_statement
         ;

assignment_statement: ID_TOK ASSIGN_TOK expression SEMICOLON_TOK
                    {
                        printf("SYNTAX OK: Assignment statement\n");
                        $$ = create_assignment($1, $3);
                    }
                    ;
```

**Expressions:**
```yacc
expression: expression ADD_TOK expression
          | expression SUB_TOK expression
          | expression MUL_TOK expression
          | expression DIV_TOK expression
          | LPAREN_TOK expression RPAREN_TOK
          | ID_TOK
          | INTCONST_TOK
          ;
```

## Error Handling and Recovery

### Syntax Error Detection

**YACC Error Handling:**
```yacc
statement: error SEMICOLON_TOK
         {
             yyerrok;  // Recover after semicolon
             printf("ERROR: Invalid statement\n");
         }
         ;
```

### Error Recovery Strategies

1. **Panic Mode**: Skip tokens until synchronizing token found
   ```yacc
   statement: error SEMICOLON_TOK { yyerrok; }
   ```

2. **Phrase-Level Recovery**: Modify parse stack or input
   ```yacc
   statement: IF_TOK error THEN_TOK statement
            {
                yyerror("Missing condition in if statement");
            }
   ```

3. **Error Productions**: Explicit grammar rules for errors
   ```yacc
   declaration: data_type error SEMICOLON_TOK
              {
                  yyerror("Invalid declarator");
              }
   ```

### yyerror Function

**Implementation:**
```c
void yyerror(const char *msg) {
    fprintf(stderr, "SYNTAX ERROR (Line %d): %s\n", 
            yylineno, msg);
    syntax_error_count++;
}
```

## Code-Theory Equivalence

### CFG Production → YACC Rule

| Theory | YACC Implementation |
|--------|---------------------|
| `A → α β γ` | `A: alpha beta gamma { action }` |
| `A → α \| β` | `A: alpha \| beta` |
| `A → ε` (empty) | `A: /* empty */ { $$ = NULL; }` |

### Derivation → Parse Actions

**Theory:** Rightmost derivation
```
S ⇒ A ⇒ αβ ⇒ αBc ⇒ αbc
```

**Practice:** Sequence of reduce actions
```
shift b
shift c
reduce B → bc
shift α
reduce A → αBc
reduce S → A
```

### Parse Tree → AST Construction

**Parse Tree (full structure):**
```
statement
└── assignment_statement
    ├── ID_TOK: "x"
    ├── ASSIGN_TOK: "="
    ├── expression
    │   └── INTCONST_TOK: "10"
    └── SEMICOLON_TOK: ";"
```

**AST (simplified):**
```
Assignment
├── Variable: "x"
└── Constant: 10
```

**YACC Implementation:**
```yacc
assignment_statement: ID_TOK ASSIGN_TOK expression SEMICOLON_TOK
                    { $$ = create_ast_node("=", $1, $3); }
                    ;
```

### Grammar Ambiguity → Precedence

**Ambiguous Grammar:**
```
E → E + E | E * E | ID
```

**Problem:** `x + y * z` has two parse trees

**Theory:** Rewrite grammar to be unambiguous
```
E → E + T | T
T → T * F | F
F → ID
```

**YACC Solution:** Use precedence declarations
```yacc
%left ADD_TOK
%left MUL_TOK

expression: expression ADD_TOK expression
          | expression MUL_TOK expression
          | ID_TOK
          ;
```

## Advanced Features

### Actions and Attribute Flow

**Inherited Attributes:**
```yacc
declaration: type_specifier declarator_list
           { set_type($2, $1); }  // Pass type down
           ;
```

**Synthesized Attributes:**
```yacc
expression: expression ADD_TOK expression
          { $$ = $1 + $3; }  // Compute value up
          ;
```

### Mid-Rule Actions

**Capture intermediate values:**
```yacc
compound_statement: LBRACE_TOK 
                  { enter_scope(); }  // Mid-rule action
                  statement_list RBRACE_TOK
                  { exit_scope(); }
                  ;
```

### Symbol Table Integration

```yacc
declaration: data_type ID_TOK SEMICOLON_TOK
           {
               if (lookup_symbol($2)) {
                   yyerror("Redeclaration of variable");
               } else {
                   insert_symbol($2, $1);
               }
           }
           ;
```

## Grammar Structure

### Complete Grammar Hierarchy

```
program
├── global_declarations (optional)
├── main_function (required)
└── user_functions (optional)

main_function
├── return_type
├── identifier
├── parameters (optional)
└── compound_statement

compound_statement
├── local_declarations
└── statement_list

statement
├── expression_statement
├── compound_statement (nested)
├── conditional_statement
├── iterative_statement
├── return_statement
└── assignment_statement

expression
├── binary_expression
├── unary_expression
├── postfix_expression
├── primary_expression
└── function_call
```

## Performance Analysis

### Time Complexity

**LALR(1) Parsing:**
- O(n) where n = number of tokens
- Each token examined once
- Constant time per action (shift/reduce)

### Space Complexity

**Parse Stack:**
- O(d) where d = maximum derivation depth
- Typically small for well-structured programs

**Parse Table:**
- O(s × t) where s = states, t = terminals
- Generated once, stored as constant array

## Testing and Validation

### Valid Input Examples

**Simple Program:**
```c
int main() {
    int x = 10;
    return 0;
}
```

**Complex Program:**
```c
int factorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int result = factorial(5);
    return result;
}
```

### Error Detection Examples

**Missing Semicolon:**
```c
int main() {
    int x = 10  // SYNTAX ERROR: Missing semicolon
    return 0;
}
```

**Unmatched Braces:**
```c
int main() {
    int x = 10;
    // SYNTAX ERROR: Missing closing brace
```

## Summary

This YACC-based syntax analyzer demonstrates:

1. **Context-Free Grammar**: C subset specified as CFG
2. **LALR(1) Parsing**: Efficient bottom-up parsing algorithm
3. **Parse Tree Construction**: Build syntax tree from tokens
4. **Error Handling**: Detect and report syntax errors
5. **Operator Precedence**: Handle expression evaluation correctly
6. **Symbol Table Integration**: Track declarations and scope
7. **Compiler Pipeline**: Connect lexer to semantic analysis

The implementation bridges theoretical parsing concepts with practical compiler construction, showing how formal grammars translate to working parsers.

## References

- Aho, A.V., Lam, M.S., Sethi, R., & Ullman, J.D. (2006). *Compilers: Principles, Techniques, and Tools* (2nd ed.).
- Levine, J.R. (2009). *flex & bison*. O'Reilly Media.
- Knuth, D.E. (1965). "On the translation of languages from left to right". *Information and Control*.
- DeRemer, F.L. (1969). "Practical translators for LR(k) languages". *PhD thesis, MIT*.
