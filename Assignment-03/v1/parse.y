%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern int line_number;
extern int error_count;
extern char* yytext;
extern int yylex();

void yyerror(char *);
int scope_level = 0;
int function_declared = 0;

void print_syntax_success(char* construct) {
    printf("SYNTAX OK (Line %d): %s\n", line_number, construct);
}
%}

/* Token declarations */
%token INT_TOK FLOAT_TOK CHAR_TOK
%token WHILE_TOK FOR_TOK DO_TOK IF_TOK ELSE_TOK RETURN_TOK
%token ID_TOK INTCONST_TOK FLOATCONST_TOK STRING_TOK

/* Operators */
%token ADD_TOK SUB_TOK MUL_TOK DIV_TOK MOD_TOK
%token LT_TOK GT_TOK LE_TOK GE_TOK EQ_TOK NEQ_TOK
%token AND_TOK OR_TOK NOT_TOK
%token BIT_AND_TOK BIT_OR_TOK BIT_XOR_TOK BIT_NOT_TOK
%token BIT_LSHIFT_TOK BIT_RSHIFT_TOK
%token ASSIGN_TOK ADD_ASSIGN_TOK SUB_ASSIGN_TOK MUL_ASSIGN_TOK DIV_ASSIGN_TOK MOD_ASSIGN_TOK
%token INC_TOK DEC_TOK
%token TERNARY_TOK COLON_TOK

/* Punctuation */
%token LPAREN_TOK RPAREN_TOK LBRACE_TOK RBRACE_TOK LBRACKET_TOK RBRACKET_TOK
%token SEMICOLON_TOK COMMA_TOK

/* Error tokens */
%token ERROR_TOK ID_TOO_LONG_ERROR NUM_TOO_LONG_ERROR ILLEGAL_CHAR_ERROR
%token UNMATCHED_STRING_ERROR SPELLING_ERROR INVALID_NUM_ERROR

/* YACC error token for syntax error recovery */
%token error

/* Operator precedence and associativity */
%right ASSIGN_TOK ADD_ASSIGN_TOK SUB_ASSIGN_TOK MUL_ASSIGN_TOK DIV_ASSIGN_TOK MOD_ASSIGN_TOK
%right TERNARY_TOK COLON_TOK
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
%right NOT_TOK BIT_NOT_TOK INC_TOK DEC_TOK UNARY_MINUS UNARY_PLUS
%left LPAREN_TOK RPAREN_TOK LBRACKET_TOK RBRACKET_TOK

%start program

%%

/* Program structure */
program: global_declarations main_function user_functions
         { 
           print_syntax_success("Complete C program");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
         }
       | main_function user_functions
         { 
           print_syntax_success("C program with main function");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
         }
       | main_function
         { 
           print_syntax_success("Simple C program with main function only");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
         }
       ;

/* Global declarations */
global_declarations: global_declarations global_declaration
                   | global_declaration
                   ;

global_declaration: data_type declarator_list SEMICOLON_TOK
                   { print_syntax_success("Global variable declaration"); }
                  | function_declaration
                   { print_syntax_success("Function declaration"); }
                  | data_type declarator_list error
                   {
                     printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after variable declaration\n", line_number);
                     error_count++;
                     yyerrok;
                   }
                  | data_type error SEMICOLON_TOK
                   {
                     printf("SYNTAX ERROR (Line %d): Invalid variable declarator list\n", line_number);
                     error_count++;
                     yyerrok;
                   }
                  | error declarator_list SEMICOLON_TOK
                   {
                     printf("SYNTAX ERROR (Line %d): Invalid or missing data type in declaration\n", line_number);
                     error_count++;
                     yyerrok;
                   }
                  ;

/* Main function */
main_function: data_type ID_TOK LPAREN_TOK RPAREN_TOK compound_statement
               { 
                 print_syntax_success("Main function definition");
                 function_declared = 1;
               }
             | data_type ID_TOK LPAREN_TOK parameter_list RPAREN_TOK compound_statement
               { 
                 print_syntax_success("Main function with parameters");
                 function_declared = 1;
               }
             ;

/* User defined functions */
user_functions: user_functions user_function
              | user_function
              | /* empty */
              ;

user_function: function_declaration
             | function_definition
             ;

function_declaration: data_type ID_TOK LPAREN_TOK RPAREN_TOK SEMICOLON_TOK
                     { print_syntax_success("Function declaration"); }
                    | data_type ID_TOK LPAREN_TOK parameter_list RPAREN_TOK SEMICOLON_TOK
                     { print_syntax_success("Function declaration with parameters"); }
                    | data_type ID_TOK LPAREN_TOK RPAREN_TOK error
                     {
                       printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after function declaration\n", line_number);
                       error_count++;
                       yyerrok;
                     }
                    | data_type ID_TOK LPAREN_TOK parameter_list error SEMICOLON_TOK
                     {
                       printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in function declaration\n", line_number);
                       error_count++;
                       yyerrok;
                     }
                    | data_type ID_TOK error RPAREN_TOK SEMICOLON_TOK
                     {
                       printf("SYNTAX ERROR (Line %d): Missing opening parenthesis '(' in function declaration\n", line_number);
                       error_count++;
                       yyerrok;
                     }
                    ;

function_definition: data_type ID_TOK LPAREN_TOK RPAREN_TOK compound_statement
                    { print_syntax_success("Function definition"); }
                   | data_type ID_TOK LPAREN_TOK parameter_list RPAREN_TOK compound_statement
                    { print_syntax_success("Function definition with parameters"); }
                   ;

/* Parameter list */
parameter_list: parameter_list COMMA_TOK parameter
              | parameter
              | parameter_list error parameter
               {
                 printf("SYNTAX ERROR (Line %d): Missing comma ',' between parameters\n", line_number);
                 error_count++;
                 yyerrok;
               }
              | parameter_list COMMA_TOK error
               {
                 printf("SYNTAX ERROR (Line %d): Invalid parameter after comma\n", line_number);
                 error_count++;
                 yyerrok;
               }
              ;

parameter: data_type ID_TOK
         | data_type ID_TOK LBRACKET_TOK RBRACKET_TOK
         ;

/* Data types */
data_type: INT_TOK
         | FLOAT_TOK
         | CHAR_TOK
         ;

/* Declaration statements */
declarator_list: declarator_list COMMA_TOK declarator
               | declarator
               | declarator_list error declarator
                {
                  printf("SYNTAX ERROR (Line %d): Missing comma ',' between declarators\n", line_number);
                  error_count++;
                  yyerrok;
                }
               | declarator_list COMMA_TOK error
                {
                  printf("SYNTAX ERROR (Line %d): Invalid declarator after comma\n", line_number);
                  error_count++;
                  yyerrok;
                }
               ;

declarator: ID_TOK
          | ID_TOK LBRACKET_TOK INTCONST_TOK RBRACKET_TOK
          | ID_TOK ASSIGN_TOK expression
          ;

/* Compound statement (block) */
compound_statement: LBRACE_TOK 
                    { scope_level++; }
                    local_declarations statement_list 
                    { scope_level--; }
                    RBRACE_TOK
                    { print_syntax_success("Compound statement"); }
                  | LBRACE_TOK 
                    { scope_level++; }
                    local_declarations statement_list 
                    { scope_level--; }
                    error
                    { 
                      printf("SYNTAX ERROR (Line %d): Missing closing brace '}'\n", line_number);
                      error_count++;
                      yyerrok;
                    }
                  | LBRACE_TOK error RBRACE_TOK
                    {
                      printf("SYNTAX ERROR (Line %d): Invalid content inside braces\n", line_number);
                      error_count++;
                      yyerrok;
                    }
                  ;

/* Local declarations */
local_declarations: local_declarations local_declaration
                  | /* empty */
                  ;

local_declaration: data_type declarator_list SEMICOLON_TOK
                  { print_syntax_success("Local variable declaration"); }
                 | data_type declarator_list error
                  {
                    printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after local declaration\n", line_number);
                    error_count++;
                    yyerrok;
                  }
                 | data_type error SEMICOLON_TOK
                  {
                    printf("SYNTAX ERROR (Line %d): Invalid local variable declarator\n", line_number);
                    error_count++;
                    yyerrok;
                  }
                 | error declarator_list SEMICOLON_TOK
                  {
                    printf("SYNTAX ERROR (Line %d): Invalid data type in local declaration\n", line_number);
                    error_count++;
                    yyerrok;
                  }
                 ;

/* Statement list */
statement_list: statement_list statement
              | /* empty */
              ;

/* Statements */
statement: expression_statement
         | compound_statement
         | conditional_statement
         | iterative_statement
         | return_statement
         | assignment_statement
         ;

expression_statement: expression SEMICOLON_TOK
                     { print_syntax_success("Expression statement"); }
                    | SEMICOLON_TOK
                    | expression error
                     {
                       printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after expression\n", line_number);
                       error_count++;
                       yyerrok;
                     }
                    ;

/* Assignment statements */
assignment_statement: ID_TOK ASSIGN_TOK expression SEMICOLON_TOK
                     { print_syntax_success("Assignment statement"); }
                    | ID_TOK ADD_ASSIGN_TOK expression SEMICOLON_TOK
                     { print_syntax_success("Add-assignment statement"); }
                    | ID_TOK SUB_ASSIGN_TOK expression SEMICOLON_TOK
                     { print_syntax_success("Sub-assignment statement"); }
                    | ID_TOK MUL_ASSIGN_TOK expression SEMICOLON_TOK
                     { print_syntax_success("Mul-assignment statement"); }
                    | ID_TOK DIV_ASSIGN_TOK expression SEMICOLON_TOK
                     { print_syntax_success("Div-assignment statement"); }
                    | ID_TOK MOD_ASSIGN_TOK expression SEMICOLON_TOK
                     { print_syntax_success("Mod-assignment statement"); }
                    | ID_TOK LBRACKET_TOK expression RBRACKET_TOK ASSIGN_TOK expression SEMICOLON_TOK
                     { print_syntax_success("Array assignment statement"); }
                    | ID_TOK ASSIGN_TOK expression error
                     {
                       printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after assignment\n", line_number);
                       error_count++;
                       yyerrok;
                     }
                    | ID_TOK ASSIGN_TOK error SEMICOLON_TOK
                     {
                       printf("SYNTAX ERROR (Line %d): Invalid expression in assignment\n", line_number);
                       error_count++;
                       yyerrok;
                     }
                    | ID_TOK error expression SEMICOLON_TOK
                     {
                       printf("SYNTAX ERROR (Line %d): Invalid assignment operator\n", line_number);
                       error_count++;
                       yyerrok;
                     }
                    ;

/* Conditional statements */
conditional_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement
                      { print_syntax_success("If statement"); }
                     | IF_TOK LPAREN_TOK expression RPAREN_TOK statement ELSE_TOK statement
                      { print_syntax_success("If-else statement"); }
                     | IF_TOK LPAREN_TOK expression error statement
                      {
                        printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in if condition\n", line_number);
                        error_count++;
                        yyerrok;
                      }
                     | IF_TOK LPAREN_TOK error RPAREN_TOK statement
                      {
                        printf("SYNTAX ERROR (Line %d): Invalid expression in if condition\n", line_number);
                        error_count++;
                        yyerrok;
                      }
                     | IF_TOK error expression RPAREN_TOK statement
                      {
                        printf("SYNTAX ERROR (Line %d): Missing opening parenthesis '(' in if statement\n", line_number);
                        error_count++;
                        yyerrok;
                      }
                     ;

/* Iterative statements */
iterative_statement: WHILE_TOK LPAREN_TOK expression RPAREN_TOK statement
                    { print_syntax_success("While loop"); }
                   | FOR_TOK LPAREN_TOK for_init SEMICOLON_TOK for_condition SEMICOLON_TOK for_update RPAREN_TOK statement
                    { print_syntax_success("For loop"); }
                   | DO_TOK statement WHILE_TOK LPAREN_TOK expression RPAREN_TOK SEMICOLON_TOK
                    { print_syntax_success("Do-while loop"); }
                   | WHILE_TOK LPAREN_TOK expression error statement
                    {
                      printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in while condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
                   | WHILE_TOK error expression RPAREN_TOK statement
                    {
                      printf("SYNTAX ERROR (Line %d): Missing opening parenthesis '(' in while loop\n", line_number);
                      error_count++;
                      yyerrok;
                    }
                   | FOR_TOK LPAREN_TOK for_init SEMICOLON_TOK for_condition SEMICOLON_TOK for_update error statement
                    {
                      printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in for loop\n", line_number);
                      error_count++;
                      yyerrok;
                    }
                   | FOR_TOK LPAREN_TOK for_init error for_condition SEMICOLON_TOK for_update RPAREN_TOK statement
                    {
                      printf("SYNTAX ERROR (Line %d): Missing semicolon ';' in for loop initialization\n", line_number);
                      error_count++;
                      yyerrok;
                    }
                   | FOR_TOK LPAREN_TOK for_init SEMICOLON_TOK for_condition error for_update RPAREN_TOK statement
                    {
                      printf("SYNTAX ERROR (Line %d): Missing semicolon ';' in for loop condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
                   | DO_TOK statement WHILE_TOK LPAREN_TOK expression RPAREN_TOK error
                    {
                      printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after do-while loop\n", line_number);
                      error_count++;
                      yyerrok;
                    }
                   ;

for_init: assignment_expression
        | declaration_expression
        | /* empty */
        ;

for_condition: expression
             | /* empty */
             ;

for_update: assignment_expression
          | /* empty */
          ;

declaration_expression: data_type ID_TOK ASSIGN_TOK expression
                       { print_syntax_success("For loop variable declaration"); }
                      | data_type ID_TOK
                      ;

assignment_expression: ID_TOK ASSIGN_TOK expression
                     | ID_TOK ADD_ASSIGN_TOK expression
                     | ID_TOK SUB_ASSIGN_TOK expression
                     | ID_TOK MUL_ASSIGN_TOK expression
                     | ID_TOK DIV_ASSIGN_TOK expression
                     | ID_TOK MOD_ASSIGN_TOK expression
                     | ID_TOK INC_TOK
                     | ID_TOK DEC_TOK
                     | INC_TOK ID_TOK
                     | DEC_TOK ID_TOK
                     ;

/* Return statement */
return_statement: RETURN_TOK SEMICOLON_TOK
                 { print_syntax_success("Return statement"); }
                | RETURN_TOK expression SEMICOLON_TOK
                 { print_syntax_success("Return statement with value"); }
                | RETURN_TOK expression error
                 {
                   printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after return statement\n", line_number);
                   error_count++;
                   yyerrok;
                 }
                | RETURN_TOK error
                 {
                   printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after return\n", line_number);
                   error_count++;
                   yyerrok;
                 }
                ;

/* Expressions */
expression: assignment_expr
          ;

assignment_expr: conditional_expr
               | ID_TOK ASSIGN_TOK assignment_expr
               | ID_TOK ADD_ASSIGN_TOK assignment_expr
               | ID_TOK SUB_ASSIGN_TOK assignment_expr
               | ID_TOK MUL_ASSIGN_TOK assignment_expr
               | ID_TOK DIV_ASSIGN_TOK assignment_expr
               | ID_TOK MOD_ASSIGN_TOK assignment_expr
               ;

conditional_expr: logical_or_expr
                | logical_or_expr TERNARY_TOK expression COLON_TOK conditional_expr
                ;

logical_or_expr: logical_and_expr
               | logical_or_expr OR_TOK logical_and_expr
               ;

logical_and_expr: bitwise_or_expr
                | logical_and_expr AND_TOK bitwise_or_expr
                ;

bitwise_or_expr: bitwise_xor_expr
               | bitwise_or_expr BIT_OR_TOK bitwise_xor_expr
               ;

bitwise_xor_expr: bitwise_and_expr
                | bitwise_xor_expr BIT_XOR_TOK bitwise_and_expr
                ;

bitwise_and_expr: equality_expr
                | bitwise_and_expr BIT_AND_TOK equality_expr
                ;

equality_expr: relational_expr
             | equality_expr EQ_TOK relational_expr
             | equality_expr NEQ_TOK relational_expr
             ;

relational_expr: shift_expr
               | relational_expr LT_TOK shift_expr
               | relational_expr GT_TOK shift_expr
               | relational_expr LE_TOK shift_expr
               | relational_expr GE_TOK shift_expr
               ;

shift_expr: additive_expr
          | shift_expr BIT_LSHIFT_TOK additive_expr
          | shift_expr BIT_RSHIFT_TOK additive_expr
          ;

additive_expr: multiplicative_expr
             | additive_expr ADD_TOK multiplicative_expr
             | additive_expr SUB_TOK multiplicative_expr
             ;

multiplicative_expr: unary_expr
                   | multiplicative_expr MUL_TOK unary_expr
                   | multiplicative_expr DIV_TOK unary_expr
                   | multiplicative_expr MOD_TOK unary_expr
                   ;

unary_expr: postfix_expr
          | INC_TOK unary_expr
          | DEC_TOK unary_expr
          | unary_operator unary_expr
          ;

unary_operator: ADD_TOK %prec UNARY_PLUS
              | SUB_TOK %prec UNARY_MINUS
              | NOT_TOK
              | BIT_NOT_TOK
              ;

postfix_expr: primary_expr
            | postfix_expr LBRACKET_TOK expression RBRACKET_TOK
            | postfix_expr LBRACKET_TOK expression error
              {
                printf("SYNTAX ERROR (Line %d): Missing closing bracket ']'\n", line_number);
                error_count++;
                yyerrok;
              }
            | postfix_expr LBRACKET_TOK error RBRACKET_TOK
              {
                printf("SYNTAX ERROR (Line %d): Invalid array index expression\n", line_number);
                error_count++;
                yyerrok;
              }
            | postfix_expr LPAREN_TOK RPAREN_TOK
              { print_syntax_success("Function call"); }
            | postfix_expr LPAREN_TOK argument_list RPAREN_TOK
              { print_syntax_success("Function call with arguments"); }
            | postfix_expr LPAREN_TOK argument_list error
              {
                printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in function call\n", line_number);
                error_count++;
                yyerrok;
              }
            | postfix_expr LPAREN_TOK error RPAREN_TOK
              {
                printf("SYNTAX ERROR (Line %d): Invalid function arguments\n", line_number);
                error_count++;
                yyerrok;
              }
            | postfix_expr INC_TOK
            | postfix_expr DEC_TOK
            ;

argument_list: argument_list COMMA_TOK expression
             | expression
             | argument_list error expression
              {
                printf("SYNTAX ERROR (Line %d): Missing comma ',' between function arguments\n", line_number);
                error_count++;
                yyerrok;
              }
             | argument_list COMMA_TOK error
              {
                printf("SYNTAX ERROR (Line %d): Invalid expression after comma in argument list\n", line_number);
                error_count++;
                yyerrok;
              }
             ;

primary_expr: ID_TOK
            | INTCONST_TOK
            | FLOATCONST_TOK
            | STRING_TOK
            | LPAREN_TOK expression RPAREN_TOK
            | LPAREN_TOK expression error
              {
                printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')'\n", line_number);
                error_count++;
                yyerrok;
              }
            | LPAREN_TOK error RPAREN_TOK
              {
                printf("SYNTAX ERROR (Line %d): Invalid expression inside parentheses\n", line_number);
                error_count++;
                yyerrok;
              }
            ;

%%

#include "lex.yy.c"

int main() {
    printf("=== C LANGUAGE SUBSET PARSER ===\n");
    printf("Parsing input...\n\n");
    
    if (yyparse() == 0) {
        printf("\n=== PARSING SUCCESSFUL ===\n");
        if (error_count == 0) {
            printf("No syntax errors found!\n");
        } else {
            printf("Parsing completed with %d error(s).\n", error_count);
        }
    } else {
        printf("\n=== PARSING FAILED ===\n");
        printf("Syntax errors found at line %d\n", line_number);
    }
    
    return 0;
}

void yyerror(char *s) {
    printf("SYNTAX ERROR (Line %d): %s near '%s'\n", line_number, s, yytext);
    error_count++;
}

