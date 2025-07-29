/*
Implement a lexical analyzer using C program for the following types of tokens:
a) Arithmetic, Relational, Logical, Bitwise and Assignment Operators of C.
*/

#define ADD '+'
#define SUB '-'
#define MUL '*'
#define DIV '/'
#define MOD '%'
#define ASSIGN '='
#define LT '<'
#define GT '>'
#define LE '<='
#define GE '>='
#define EQ '=='
#define NE '!='
#define AND '&&'
#define OR '||'
#define NOT '!'

/*Reserved words*/
#define INT 359
#define FLOAT 360
#define CHAR 361
#define FOR 362
#define WHILE 363
#define IF 364
#define ELSE 365
#define SWITCH 366
#define CASE 367
#define DEFAULT 368
#define BREAK 369
#define CONTINUE 370
#define RETURN 371



/*Identifiers*/
#define ID 400
#define NUM 401
#define FLOAT_NUM 402
#define CHAR_CONST 403
/*Integer Constants*/
#define INT_CONST 404
/*String Constants*/
#define STRING_CONST 405
/*Paranthesis*/
#define LPAREN '('
#define RPAREN ')'
/*Braces*/
#define LBRACE '{'
#define RBRACE '}'
/*Brackets*/
#define LBRACKET '['
#define RBRACKET ']'