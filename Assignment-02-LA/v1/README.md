# Lexical Analyzer Implementation Summary

## Assignment Requirements Met:

### a) Arithmetic, Relational, Logical, Bitwise and Assignment Operators of C:

**Arithmetic Operators:**
- `+` (ADD_TOK = '+')
- `-` (SUB_TOK = '-') 
- `*` (MUL_TOK = '*')
- `/` (DIV_TOK = '/')
- `%` (MOD_TOK = '%')

**Relational Operators:**
- `<` (LT_TOK = '<')
- `>` (GT_TOK = '>')
- `<=` (LE_TOK = 270)
- `>=` (GE_TOK = 271)
- `==` (EQ_TOK = 272)
- `!=` (NEQ_TOK = 273)

**Logical Operators:**
- `&&` (AND_TOK = 274)
- `||` (OR_TOK = 275)
- `!` (NOT_TOK = '!')

**Bitwise Operators:**
- `&` (BIT_AND_TOK = '&')
- `|` (BIT_OR_TOK = '|')
- `^` (BIT_XOR_TOK = '^')
- `~` (BIT_NOT_TOK = '~')
- `<<` (BIT_LSHIFT_TOK = 276)
- `>>` (BIT_RSHIFT_TOK = 277)

**Assignment Operators:**
- `=` (ASSIGN_TOK = '=')
- `+=` (ADD_ASSIGN_TOK = 278)
- `-=` (SUB_ASSIGN_TOK = 279)
- `*=` (MUL_ASSIGN_TOK = 280)
- `/=` (DIV_ASSIGN_TOK = 281)
- `%=` (MOD_ASSIGN_TOK = 282)

**Increment/Decrement Operators:**
- `++` (INC_TOK = 283)
- `--` (DEC_TOK = 284)

### b) Reserved words: int, float, char, for, do, while, if and else:
- `int` (INT_TOK = 256)
- `float` (FLOAT_TOK = 257)
- `char` (CHAR_TOK = 258)
- `for` (FOR_TOK = 260)
- `do` (DO_TOK = 261)
- `while` (WHILE_TOK = 259)
- `if` (IF_TOK = 262)
- `else` (ELSE_TOK = 263)
- `return` (RETURN_TOK = 264) - Added for completeness

### c) Identifier:
- Pattern: `[a-zA-Z_][a-zA-Z0-9_]*` (ID_TOK = 350)

### d) Integer Constants:
- Pattern: `[0-9]+` (INTCONST_TOK = 351)

### e) Parentheses, Curly braces:
- `(` (LPAREN_TOK = '(')
- `)` (RPAREN_TOK = ')')
- `{` (LBRACE_TOK = '{')
- `}` (RBRACE_TOK = '}')
- `[` (LBRACKET_TOK = '[')
- `]` (RBRACKET_TOK = ']')

### Additional Features Implemented:
- Float constants: Pattern `[0-9]+\.[0-9]+` (FLOATCONST_TOK = 352)
- Semicolons and commas: `;` and `,`
- Ternary operator: `?` and `:`
- Proper whitespace handling

## Files:
- `lex.l` - Lex source file with pattern definitions
- `tok_def.h` - Token definitions header file
- `input.c` - Sample C program for testing
- `test_all_tokens.c` - Comprehensive test file

## Usage:
1. Compile: `lex lex.l && gcc lex.yy.c -ll -o lexer`
2. Run: `./lexer < input_file.c`

The lexical analyzer successfully tokenizes complete C programs and generates tokens as required by the assignment.