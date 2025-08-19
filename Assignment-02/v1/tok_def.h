/*Arithmetic operator lexems */
#define ADD_TOK '+'
#define SUB_TOK '-'
#define MUL_TOK '*'
#define DIV_TOK '/'
#define MOD_TOK '%'

/*Relational operator lexems*/
#define LT_TOK '<'
#define GT_TOK '>'
#define LE_TOK 270      // "<="
#define GE_TOK 271      // ">="
#define EQ_TOK 272      // "=="
#define NEQ_TOK 273     // "!="
/*Logical operator lexems*/
#define AND_TOK 274     // "&&"
#define OR_TOK 275      // "||"
#define NOT_TOK '!'

/* Bitwise operator lexems*/
#define BIT_AND_TOK '&'
#define BIT_OR_TOK '|'
#define BIT_XOR_TOK '^'
#define BIT_NOT_TOK '~'
#define BIT_LSHIFT_TOK 276  // "<<"
#define BIT_RSHIFT_TOK 277  // ">>"
/*Assignment operator lexems*/
#define ASSIGN_TOK '='
#define ADD_ASSIGN_TOK 278  // "+="
#define SUB_ASSIGN_TOK 279  // "-="
#define MUL_ASSIGN_TOK 280  // "*="
#define DIV_ASSIGN_TOK 281  // "/="
#define MOD_ASSIGN_TOK 282  // "%="

/*Increment/Decrement operator lexems*/
#define INC_TOK 283     // "++"
#define DEC_TOK 284     // "--"

/*Ternary operator lexems*/
#define TERNARY_TOK '?'
#define COLON_TOK ':'

/*Parenthesis operator lexems*/
#define LPAREN_TOK '('
#define RPAREN_TOK ')'
#define LBRACE_TOK '{'
#define RBRACE_TOK '}'
#define LBRACKET_TOK '['
#define RBRACKET_TOK ']'

#define SEMICOLON_TOK ';'
#define COMMA_TOK ','

/*Reserved Words*/
#define INT_TOK 256
#define FLOAT_TOK 257
#define CHAR_TOK 258
#define WHILE_TOK 259
#define FOR_TOK 260
#define DO_TOK 261
#define IF_TOK 262
#define ELSE_TOK 263
#define RETURN_TOK 264

/*Identifier, Constants*/
#define ID_TOK 350
#define INTCONST_TOK 351
#define FLOATCONST_TOK 352
