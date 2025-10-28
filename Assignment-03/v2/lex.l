%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"  // Token definitions from parser.y
int line_number = 1;
%}

/* Exclusive state for strings */
%x IN_STRING

digit      [0-9]+
id         [a-zA-Z_][a-zA-Z0-9_]*
floatnum   [0-9]+\.[0-9]+

%%

/* Whitespace */
[ \t]+              ; /* ignore spaces/tabs */
\n                  { line_number++; }

/* Keywords */
"int"               { return INT_TOK; }
"float"             { return FLOAT_TOK; }
"char"              { return CHAR_TOK; }
"while"             { return WHILE_TOK; }
"for"               { return FOR_TOK; }
"do"                { return DO_TOK; }
"if"                { return IF_TOK; }
"else"              { return ELSE_TOK; }
"return"            { return RETURN_TOK; }

/* Operators */
"="                 { return ASSIGN_TOK; }
"+="                { return ADD_ASSIGN_TOK; }
"-="                { return SUB_ASSIGN_TOK; }
"*="                { return MUL_ASSIGN_TOK; }
"/="                { return DIV_ASSIGN_TOK; }
"%="                { return MOD_ASSIGN_TOK; }
"++"                { return INC_TOK; }
"--"                { return DEC_TOK; }
"+"                 { return ADD_TOK; }
"-"                 { return SUB_TOK; }
"*"                 { return MUL_TOK; }
"/"                 { return DIV_TOK; }
"%"                 { return MOD_TOK; }
"=="                { return EQ_TOK; }
"!="                { return NEQ_TOK; }
"<="                { return LE_TOK; }
">="                { return GE_TOK; }
"<"                 { return LT_TOK; }
">"                 { return GT_TOK; }
"&&"                { return AND_TOK; }
"||"                { return OR_TOK; }
"!"                 { return NOT_TOK; }
"&"                 { return BIT_AND_TOK; }
"|"                 { return BIT_OR_TOK; }
"^"                 { return BIT_XOR_TOK; }
"~"                 { return BIT_NOT_TOK; }
"<<"                { return BIT_LSHIFT_TOK; }
">>"                { return BIT_RSHIFT_TOK; }
"?"                 { return TERNARY_TOK; }
":"                 { return COLON_TOK; }

/* Punctuation */
"("                 { return LPAREN_TOK; }
")"                 { return RPAREN_TOK; }
"{"                 { return LBRACE_TOK; }
"}"                 { return RBRACE_TOK; }
"["                 { return LBRACKET_TOK; }
"]"                 { return RBRACKET_TOK; }
";"                 { return SEMICOLON_TOK; }
","                 { return COMMA_TOK; }

/* Constants */
{id}                { yylval = strdup(yytext); return ID_TOK; }
{digit}             { yylval = strdup(yytext); return INTCONST_TOK; }
{floatnum}          { yylval = strdup(yytext); return FLOATCONST_TOK; }

/* Strings */
\"                  { BEGIN(IN_STRING); yylval = strdup(""); }
<IN_STRING>[^\"\n]+ { /* consume string characters */ }
<IN_STRING>\"       { BEGIN(INITIAL); return STRING_TOK; }
<IN_STRING>\n       { fprintf(stderr,"Unterminated string at line %d\n", line_number); line_number++; BEGIN(INITIAL); }

/* Comments */
"//".*              ; /* ignore single line comment */
"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*"*+"/" ; /* ignore multi-line comment */

/* Illegal characters */
.                   { fprintf(stderr,"Illegal character '%s' at line %d\n", yytext, line_number); }

%%

int yywrap() { return 1; }

int main(int argc, char* argv[]) {
    if(argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if(!f) { perror("fopen"); return 1; }
        yyin = f;
    }
    yylex();
    return 0;
}