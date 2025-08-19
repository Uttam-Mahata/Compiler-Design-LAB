%{
#include<stdio.h>
#include<stdlib.h>
#include "tok_def.h"
%}

digit [0-9]+
id [a-zA-Z_][a-zA-Z0-9_]*
floatnum [0-9]+\.[0-9]+
whitespace [ \t\n]+


%%
"<<"                                {return(BIT_LSHIFT_TOK);}
">>"                                {return(BIT_RSHIFT_TOK);}
"+="                                {return(ADD_ASSIGN_TOK);}
"-="                                {return(SUB_ASSIGN_TOK);}
"*="                                {return(MUL_ASSIGN_TOK);}
"/="                                {return(DIV_ASSIGN_TOK);}
"%="                                {return(MOD_ASSIGN_TOK);}
"<="                                {return(LE_TOK);}
">="                                {return(GE_TOK);}
"=="                                {return(EQ_TOK);}
"!="                                {return(NEQ_TOK);}
"&&"                                {return(AND_TOK);}
"||"                                {return(OR_TOK);}
"++"                                {return(INC_TOK);}
"--"                                {return(DEC_TOK);}
"int"                               {return(INT_TOK);}
"float"                             {return(FLOAT_TOK);}
"char"                              {return(CHAR_TOK);}
"while"                             {return(WHILE_TOK);}
"for"                               {return(FOR_TOK);}
"do"                                {return(DO_TOK);}
"if"                                {return(IF_TOK);}
"else"                              {return(ELSE_TOK);}
"return"                            {return(RETURN_TOK);}
"+"                                 {return(ADD_TOK);}
"-"                                 {return(SUB_TOK);}
"*"                                 {return(MUL_TOK);}
"/"                                 {return(DIV_TOK);}
"%"                                 {return(MOD_TOK);}
"<"                                 {return(LT_TOK);}
">"                                 {return(GT_TOK);}
"!"                                 {return(NOT_TOK);}
"&"                                 {return(BIT_AND_TOK);}
"|"                                 {return(BIT_OR_TOK);}
"^"                                 {return(BIT_XOR_TOK);}
"~"                                 {return(BIT_NOT_TOK);}
"="                                 {return(ASSIGN_TOK);}
"?"                                 {return(TERNARY_TOK);}
":"                                 {return(COLON_TOK);}
"("                                 {return(LPAREN_TOK);}
")"                                 {return(RPAREN_TOK);}
"{"                                 {return(LBRACE_TOK);}
"}"                                 {return(RBRACE_TOK);}
"["                                 {return(LBRACKET_TOK);}
"]"                                 {return(RBRACKET_TOK);}
";"                                 {return(SEMICOLON_TOK);}
","                                 {return(COMMA_TOK);}
{floatnum}                          {return(FLOATCONST_TOK);}
{digit}                             {return(INTCONST_TOK);}
{id}                                {return(ID_TOK);}
{whitespace}                        ;
%%

int main() {
    int val;
    while((val = yylex()) > 0)
    {
        printf("Token ===%s; Token ID ====%d\n", yytext, val);
    }
    
    return(0);

}