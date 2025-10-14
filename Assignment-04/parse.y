%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "symbol_table.h"

extern int line_number;
extern int error_count;
extern char* yytext;
extern int yylex();

void yyerror(char *);
int scope_level = 0;
int function_declared = 0;
data_type_t current_type = TYPE_UNKNOWN;

void print_syntax_success(char* construct) {
    printf("SYNTAX OK (Line %d): %s\n", line_number, construct);
}

scope_type_t get_current_scope_type() {
    if (sym_table.current_scope_level == 0) return SCOPE_GLOBAL;
    else if (sym_table.current_scope_level == 1) return SCOPE_FUNCTION;
    else return SCOPE_BLOCK;
}
%}

%union {
    int int_val;
    float float_val;
    char* string_val;
    int type_val;
}

/* Token declarations */
%token <type_val> INT_TOK FLOAT_TOK CHAR_TOK VOID_TOK
%token WHILE_TOK FOR_TOK DO_TOK IF_TOK ELSE_TOK RETURN_TOK
%token <string_val> ID_TOK STRING_TOK
%token <int_val> INTCONST_TOK
%token <float_val> FLOATCONST_TOK

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

/* Type declarations */
%type <type_val> data_type

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
program: { init_symbol_table(); } global_declarations main_function user_functions
         { 
           print_syntax_success("Complete C program");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
           print_symbol_table();
         }
       | { init_symbol_table(); } main_function user_functions
         { 
           print_syntax_success("C program with main function");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
           print_symbol_table();
         }
       | { init_symbol_table(); } main_function
         { 
           print_syntax_success("Simple C program with main function only");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
           print_symbol_table();
         }
       ;

/* Global declarations */
global_declarations: global_declarations global_declaration
                   | global_declaration
                   ;

global_declaration: data_type { current_type = $1; } declarator_list SEMICOLON_TOK
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

/* Data types */
data_type: INT_TOK { $$ = TYPE_INT; }
         | FLOAT_TOK { $$ = TYPE_FLOAT; }
         | CHAR_TOK { $$ = TYPE_CHAR; }
         | VOID_TOK { $$ = TYPE_VOID; }
         ;

/* Variable declarators */
declarator_list: declarator_list COMMA_TOK declarator
               | declarator
               | declarator_list error declarator
                {
                  printf("SYNTAX ERROR (Line %d): Missing comma ',' between variable declarations\n", line_number);
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
           {
             // Add variable to symbol table
             if (!add_symbol($1, current_type, get_current_scope_type(), line_number, 0)) {
                 error_count++;
             }
             free($1);
           }
         | ID_TOK LBRACKET_TOK INTCONST_TOK RBRACKET_TOK
           {
             // Add array variable to symbol table
             if (!add_symbol($1, current_type, get_current_scope_type(), line_number, 0)) {
                 error_count++;
             }
             printf("SYNTAX OK: Array declaration '%s[%d]'\n", $1, $3);
             free($1);
           }
         | ID_TOK LBRACKET_TOK RBRACKET_TOK
           {
             // Add array variable to symbol table (no size specified)
             if (!add_symbol($1, current_type, get_current_scope_type(), line_number, 0)) {
                 error_count++;
             }
             printf("SYNTAX OK: Array declaration '%s[]'\n", $1);
             free($1);
           }
         | ID_TOK LBRACKET_TOK INTCONST_TOK error
           {
             printf("SYNTAX ERROR (Line %d): Missing closing bracket ']' in array declaration\n", line_number);
             error_count++;
             yyerrok;
           }
         | ID_TOK LBRACKET_TOK error RBRACKET_TOK
           {
             printf("SYNTAX ERROR (Line %d): Invalid array size\n", line_number);
             error_count++;
             yyerrok;
           }
         ;

/* Main function */
main_function: data_type ID_TOK { 
                 // Add function to symbol table
                 if (!add_symbol($2, $1, SCOPE_GLOBAL, line_number, 1)) {
                     error_count++;
                 }
                 enter_scope();
               } LPAREN_TOK RPAREN_TOK compound_statement
               { 
                 print_syntax_success("Main function definition");
                 function_declared = 1;
                 exit_scope();
                 free($2);
               }
             | data_type ID_TOK { 
                 // Add function to symbol table
                 if (!add_symbol($2, $1, SCOPE_GLOBAL, line_number, 1)) {
                     error_count++;
                 }
                 enter_scope();
               } LPAREN_TOK parameter_list RPAREN_TOK compound_statement
               { 
                 print_syntax_success("Main function with parameters");
                 function_declared = 1;
                 exit_scope();
                 free($2);
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

function_declaration: data_type ID_TOK {
                       // Add function declaration to symbol table
                       if (!add_symbol($2, $1, SCOPE_GLOBAL, line_number, 1)) {
                           error_count++;
                       }
                       free($2);
                     } LPAREN_TOK RPAREN_TOK SEMICOLON_TOK
                     { print_syntax_success("Function declaration"); }
                    | data_type ID_TOK {
                       // Add function declaration to symbol table
                       if (!add_symbol($2, $1, SCOPE_GLOBAL, line_number, 1)) {
                           error_count++;
                       }
                       free($2);
                     } LPAREN_TOK parameter_list RPAREN_TOK SEMICOLON_TOK
                     { print_syntax_success("Function declaration with parameters"); }
                    ;

function_definition: data_type ID_TOK {
                      // Add function to symbol table
                      if (!add_symbol($2, $1, SCOPE_GLOBAL, line_number, 1)) {
                          error_count++;
                      }
                      enter_scope();
                    } LPAREN_TOK RPAREN_TOK compound_statement
                    { 
                      print_syntax_success("Function definition");
                      exit_scope();
                      free($2);
                    }
                   | data_type ID_TOK {
                      // Add function to symbol table
                      if (!add_symbol($2, $1, SCOPE_GLOBAL, line_number, 1)) {
                          error_count++;
                      }
                      enter_scope();
                    } LPAREN_TOK parameter_list RPAREN_TOK compound_statement
                    { 
                      print_syntax_success("Function definition with parameters");
                      exit_scope();
                      free($2);
                    }
                   ;

/* Parameter lists */
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
          {
            // Add parameter to symbol table
            if (!add_symbol($2, token_to_type($1), SCOPE_FUNCTION, line_number, 0)) {
                error_count++;
            }
            free($2);
          }
         | data_type ID_TOK LBRACKET_TOK RBRACKET_TOK
          {
            // Add array parameter to symbol table
            if (!add_symbol($2, token_to_type($1), SCOPE_FUNCTION, line_number, 0)) {
                error_count++;
            }
            printf("SYNTAX OK: Array parameter '%s[]'\n", $2);
            free($2);
          }
         ;

/* Compound statements */
compound_statement: LBRACE_TOK { enter_scope(); } statement_list RBRACE_TOK
                   { 
                     print_syntax_success("Compound statement");
                     exit_scope();
                   }
                  | LBRACE_TOK { enter_scope(); } RBRACE_TOK
                   { 
                     print_syntax_success("Empty compound statement");
                     exit_scope();
                   }
                  | LBRACE_TOK statement_list error
                   {
                     printf("SYNTAX ERROR (Line %d): Missing closing brace '}'\n", line_number);
                     error_count++;
                     yyerrok;
                   }
                  | LBRACE_TOK error RBRACE_TOK
                   {
                     printf("SYNTAX ERROR (Line %d): Invalid statement inside compound statement\n", line_number);
                     error_count++;
                     yyerrok;
                   }
                  ;

/* Statement lists */
statement_list: statement_list statement
              | statement
              ;

/* Statements */
statement: declaration_statement
         | expression_statement
         | compound_statement
         | selection_statement
         | iteration_statement
         | jump_statement
         | error SEMICOLON_TOK
          {
            printf("SYNTAX ERROR (Line %d): Invalid statement\n", line_number);
            error_count++;
            yyerrok;
          }
         ;

/* Variable declarations inside functions/blocks */
declaration_statement: data_type { current_type = token_to_type($1); } declarator_list SEMICOLON_TOK
                      { print_syntax_success("Local variable declaration"); }
                     | data_type declarator_list error
                      {
                        printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after local variable declaration\n", line_number);
                        error_count++;
                        yyerrok;
                      }
                     ;

/* Expression statements */
expression_statement: expression SEMICOLON_TOK
                     { print_syntax_success("Expression statement"); }
                    | SEMICOLON_TOK
                     { print_syntax_success("Empty statement"); }
                    | expression error
                     {
                       printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after expression\n", line_number);
                       error_count++;
                       yyerrok;
                     }
                    ;

/* Selection statements */
selection_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement
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

/* Iteration statements */
iteration_statement: WHILE_TOK LPAREN_TOK expression RPAREN_TOK statement
                    { print_syntax_success("While loop"); }
                   | FOR_TOK LPAREN_TOK expression_statement expression_statement RPAREN_TOK statement
                    { print_syntax_success("For loop"); }
                   | FOR_TOK LPAREN_TOK expression_statement expression_statement expression RPAREN_TOK statement
                    { print_syntax_success("For loop with increment"); }
                   | DO_TOK statement WHILE_TOK LPAREN_TOK expression RPAREN_TOK SEMICOLON_TOK
                    { print_syntax_success("Do-while loop"); }
                   | WHILE_TOK LPAREN_TOK expression error statement
                    {
                      printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in while condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
                   | WHILE_TOK LPAREN_TOK error RPAREN_TOK statement
                    {
                      printf("SYNTAX ERROR (Line %d): Invalid expression in while condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
                   ;

/* Jump statements */
jump_statement: RETURN_TOK expression SEMICOLON_TOK
               { print_syntax_success("Return statement with value"); }
              | RETURN_TOK SEMICOLON_TOK
               { print_syntax_success("Return statement"); }
              | RETURN_TOK expression error
               {
                 printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after return statement\n", line_number);
                 error_count++;
                 yyerrok;
               }
              | RETURN_TOK error SEMICOLON_TOK
               {
                 printf("SYNTAX ERROR (Line %d): Invalid expression in return statement\n", line_number);
                 error_count++;
                 yyerrok;
               }
              ;

/* Expressions */
expression: assignment_expr
          | expression COMMA_TOK assignment_expr
          | expression error assignment_expr
           {
             printf("SYNTAX ERROR (Line %d): Missing comma ',' between expressions\n", line_number);
             error_count++;
             yyerrok;
           }
          | expression COMMA_TOK error
           {
             printf("SYNTAX ERROR (Line %d): Invalid expression after comma\n", line_number);
             error_count++;
             yyerrok;
           }
          ;

assignment_expr: ternary_expr
               | unary_expr ASSIGN_TOK assignment_expr
               | unary_expr ADD_ASSIGN_TOK assignment_expr
               | unary_expr SUB_ASSIGN_TOK assignment_expr
               | unary_expr MUL_ASSIGN_TOK assignment_expr
               | unary_expr DIV_ASSIGN_TOK assignment_expr
               | unary_expr MOD_ASSIGN_TOK assignment_expr
               | unary_expr error assignment_expr
                {
                  printf("SYNTAX ERROR (Line %d): Invalid assignment operator\n", line_number);
                  error_count++;
                  yyerrok;
                }
               | unary_expr ASSIGN_TOK error
                {
                  printf("SYNTAX ERROR (Line %d): Invalid expression after assignment operator\n", line_number);
                  error_count++;
                  yyerrok;
                }
               ;

ternary_expr: logical_or_expr
            | logical_or_expr TERNARY_TOK expression COLON_TOK ternary_expr
            | logical_or_expr TERNARY_TOK expression error ternary_expr
             {
               printf("SYNTAX ERROR (Line %d): Missing ':' in ternary operator\n", line_number);
               error_count++;
               yyerrok;
             }
            | logical_or_expr TERNARY_TOK error COLON_TOK ternary_expr
             {
               printf("SYNTAX ERROR (Line %d): Invalid expression in ternary operator\n", line_number);
               error_count++;
               yyerrok;
             }
            | logical_or_expr error expression COLON_TOK ternary_expr
             {
               printf("SYNTAX ERROR (Line %d): Missing '?' in ternary operator\n", line_number);
               error_count++;
               yyerrok;
             }
            ;

logical_or_expr: logical_and_expr
               | logical_or_expr OR_TOK logical_and_expr
               ;

logical_and_expr: bit_or_expr
                | logical_and_expr AND_TOK bit_or_expr
                ;

bit_or_expr: bit_xor_expr
           | bit_or_expr BIT_OR_TOK bit_xor_expr
           ;

bit_xor_expr: bit_and_expr
            | bit_xor_expr BIT_XOR_TOK bit_and_expr
            ;

bit_and_expr: equality_expr
            | bit_and_expr BIT_AND_TOK equality_expr
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
             {
               // Check if variable is declared before use
               if (!is_variable_declared($1)) {
                   printf("ERROR (Line %d): Variable '%s' used before declaration\n", line_number, $1);
                   error_count++;
               } else {
                   symbol_t* sym = lookup_symbol($1);
                   printf("VARIABLE USE: '%s' (Type: %s, Scope: %s)\n", 
                          $1, type_to_string(sym->type), scope_to_string(sym->scope));
               }
               free($1);
             }
            | INTCONST_TOK
            | FLOATCONST_TOK
            | STRING_TOK { free($1); }
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
    printf("=== C LANGUAGE SUBSET PARSER WITH SYMBOL TABLE ===\n");
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