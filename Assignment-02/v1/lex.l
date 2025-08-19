%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tok_def.h"

#define MAX_ID_LENGTH 31
#define MAX_NUM_LENGTH 10
#define MAX_STRING_LENGTH 256

int line_number = 1;
int error_count = 0;

void print_error(char* error_type, char* lexeme) {
    printf("LEXICAL ERROR (Line %d): %s - '%s'\n", line_number, error_type, lexeme);
    error_count++;
}

int check_keyword(char* word) {
    if (strcmp(word, "int") == 0) return INT_TOK;
    if (strcmp(word, "float") == 0) return FLOAT_TOK;
    if (strcmp(word, "char") == 0) return CHAR_TOK;
    if (strcmp(word, "while") == 0) return WHILE_TOK;
    if (strcmp(word, "for") == 0) return FOR_TOK;
    if (strcmp(word, "do") == 0) return DO_TOK;
    if (strcmp(word, "if") == 0) return IF_TOK;
    if (strcmp(word, "else") == 0) return ELSE_TOK;
    if (strcmp(word, "return") == 0) return RETURN_TOK;
    return ID_TOK;
}

int check_spelling_error(char* word) {
    // Check for common spelling errors in keywords
    char* keywords[] = {"int", "float", "char", "while", "for", "do", "if", "else", "return"};
    char* common_errors[] = {"itn", "flot", "chr", "whle", "fr", "od", "fi", "esle", "retrun"};
    int num_keywords = 9;
    
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, common_errors[i]) == 0) {
            printf("SPELLING ERROR (Line %d): '%s' - Did you mean '%s'?\n", line_number, word, keywords[i]);
            error_count++;
            return SPELLING_ERROR;
        }
    }
    return 0;
}
%}

digit [0-9]
letter [a-zA-Z_]
alphanum [a-zA-Z0-9_]
whitespace [ \t]+
newline \n


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

{newline}                           {line_number++;}

{letter}{alphanum}*                 {
                                        if (strlen(yytext) > MAX_ID_LENGTH) {
                                            print_error("Identifier too long", yytext);
                                            return ID_TOO_LONG_ERROR;
                                        }
                                        int spelling_check = check_spelling_error(yytext);
                                        if (spelling_check) return spelling_check;
                                        return check_keyword(yytext);
                                    }

{digit}+                           {
                                        if (strlen(yytext) > MAX_NUM_LENGTH) {
                                            print_error("Integer constant too long", yytext);
                                            return NUM_TOO_LONG_ERROR;
                                        }
                                        return(INTCONST_TOK);
                                    }

{digit}+\.{digit}+                  {
                                        if (strlen(yytext) > MAX_NUM_LENGTH) {
                                            print_error("Float constant too long", yytext);
                                            return NUM_TOO_LONG_ERROR;
                                        }
                                        return(FLOATCONST_TOK);
                                    }

{digit}+[a-zA-Z$@#]+                {
                                        print_error("Invalid number format - contains illegal characters", yytext);
                                        return INVALID_NUM_ERROR;
                                    }

\"[^\"]*\"                          {
                                        if (strlen(yytext) > MAX_STRING_LENGTH) {
                                            print_error("String too long", yytext);
                                            return ERROR_TOK;
                                        }
                                        return STRING_TOK;
                                    }

\"[^\"]*\n                          {
                                        print_error("Unmatched string - newline in string", yytext);
                                        line_number++;
                                        return UNMATCHED_STRING_ERROR;
                                    }

\"[^\"]*$                           {
                                        print_error("Unmatched string - missing closing quote", yytext);
                                        return UNMATCHED_STRING_ERROR;
                                    }

\'[^\']*\'                          {
                                        if (strlen(yytext) == 3) return INTCONST_TOK; // Single character
                                        print_error("Invalid character constant", yytext);
                                        return ERROR_TOK;
                                    }

\'[^\']*$                           {
                                        print_error("Unmatched character constant", yytext);
                                        return ERROR_TOK;
                                    }

[$@#%&]+                            {
                                        print_error("Illegal character(s)", yytext);
                                        return ILLEGAL_CHAR_ERROR;
                                    }

{digit}+[$@#]+{digit}*              {
                                        print_error("Invalid number - contains illegal characters", yytext);
                                        return INVALID_NUM_ERROR;
                                    }

{letter}{alphanum}*[$@#]+{alphanum}* {
                                        print_error("Invalid identifier - contains illegal characters", yytext);
                                        return ERROR_TOK;
                                    }

{whitespace}                        ;

.                                   {
                                        print_error("Unexpected character", yytext);
                                        return ILLEGAL_CHAR_ERROR;
                                    }

%%

int main() {
    int val;
    printf("=== LEXICAL ANALYSIS WITH ERROR DETECTION ===\n");
    printf("Processing input...\n\n");
    
    while((val = yylex()) > 0)
    {
        if (val >= 400) {
            // Error token - already printed error message
            continue;
        }
        printf("Token: %-20s | Token ID: %d\n", yytext, val);
    }
    
    printf("\n=== LEXICAL ANALYSIS COMPLETE ===\n");
    printf("Total lexical errors found: %d\n", error_count);
    
    if (error_count == 0) {
        printf("✓ No lexical errors detected!\n");
    } else {
        printf("✗ %d lexical error(s) need to be fixed.\n", error_count);
    }
    
    return(0);
}