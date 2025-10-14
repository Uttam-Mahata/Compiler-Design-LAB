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

void print_type_error(char* message) {
    printf("TYPE ERROR (Line %d): %s\n", line_number, message);
    error_count++;
}

// Forward declaration - will be defined after token definitions
data_type_t token_to_type(int token);

scope_type_t get_current_scope_type() {
    if (sym_table.current_scope_level == 0) return SCOPE_GLOBAL;
    else if (sym_table.current_scope_level == 1) return SCOPE_FUNCTION;
    else return SCOPE_BLOCK;
}


// Type checking helper functions
data_type_t check_binary_op_type(data_type_t left, data_type_t right, char* op) {
    // Check if both operands are numeric
    if (!is_numeric_type(left) || !is_numeric_type(right)) {
        char msg[256];
        sprintf(msg, "Binary operator '%s' requires numeric operands, got '%s' and '%s'",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }
    
    // Check type compatibility
    if (!are_types_compatible(left, right)) {
        char msg[256];
        sprintf(msg, "Type mismatch in binary operation '%s': '%s' and '%s' are not compatible",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }
    
    // Return the result type (promote to float if either operand is float)
    if (left == TYPE_FLOAT || right == TYPE_FLOAT) {
        return TYPE_FLOAT;
    }
    return left;
}

data_type_t check_relational_op_type(data_type_t left, data_type_t right, char* op) {
    if (!is_numeric_type(left) || !is_numeric_type(right)) {
        char msg[256];
        sprintf(msg, "Relational operator '%s' requires numeric operands, got '%s' and '%s'",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }
    
    if (!are_types_compatible(left, right)) {
        char msg[256];
        sprintf(msg, "Type mismatch in relational operation '%s': '%s' and '%s' are not compatible",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }
    
    return TYPE_INT; // Relational operators return boolean (represented as int)
}

data_type_t check_logical_op_type(data_type_t left, data_type_t right, char* op) {
    if (!is_numeric_type(left) || !is_numeric_type(right)) {
        char msg[256];
        sprintf(msg, "Logical operator '%s' requires numeric operands, got '%s' and '%s'",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }
    
    if (!are_types_compatible(left, right)) {
        char msg[256];
        sprintf(msg, "Type mismatch in logical operation '%s': '%s' and '%s' are not compatible",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }
    
    return TYPE_INT;
}

void check_assignment_type(data_type_t left_type, data_type_t right_type, int is_lvalue) {
    if (!is_lvalue) {
        print_type_error("Left side of assignment must be an lvalue (variable or array element)");
        return;
    }
    
    // Arrays cannot be assigned directly
    if (is_array_type(left_type)) {
        print_type_error("Cannot assign to an array directly");
        return;
    }
    
    if (!are_types_compatible(left_type, right_type)) {
        char msg[256];
        sprintf(msg, "Type mismatch in assignment: cannot assign '%s' to '%s'",
                type_to_string(right_type), type_to_string(left_type));
        print_type_error(msg);
    }
}

void check_condition_type(data_type_t cond_type) {
    if (!is_numeric_type(cond_type)) {
        char msg[256];
        sprintf(msg, "Condition must be numeric type, got '%s'", type_to_string(cond_type));
        print_type_error(msg);
    }
}

void check_pointer_dereference(data_type_t type) {
    if (!is_pointer_type(type) && !is_array_type(type)) {
        char msg[256];
        sprintf(msg, "Cannot dereference non-pointer type '%s' - attempting to use an integer as a pointer",
                type_to_string(type));
        print_type_error(msg);
    }
}
%}

%union {
    int int_val;
    float float_val;
    char* string_val;
    int type_val;
    struct {
        data_type_t type;
        int is_lvalue;
    } expr_info;
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
%type <expr_info> expression assignment_expr ternary_expr logical_or_expr logical_and_expr
%type <expr_info> bit_or_expr bit_xor_expr bit_and_expr equality_expr relational_expr
%type <expr_info> shift_expr additive_expr multiplicative_expr unary_expr postfix_expr primary_expr

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

global_declaration: data_type { current_type = token_to_type($1); } declarator_list SEMICOLON_TOK
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
data_type: INT_TOK { $$ = INT_TOK; }
         | FLOAT_TOK { $$ = FLOAT_TOK; }
         | CHAR_TOK { $$ = CHAR_TOK; }
         | VOID_TOK { $$ = VOID_TOK; }
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
             // Add array to symbol table with proper array type
             data_type_t array_type;
             switch(current_type) {
                 case TYPE_INT: array_type = TYPE_INT_ARRAY; break;
                 case TYPE_FLOAT: array_type = TYPE_FLOAT_ARRAY; break;
                 case TYPE_CHAR: array_type = TYPE_CHAR_ARRAY; break;
                 default: array_type = current_type; break;
             }
             if (!add_symbol_with_attrs($1, array_type, get_current_scope_type(), 
                                       line_number, 0, 1, $3, 0)) {
                 error_count++;
             }
             printf("SYNTAX OK: Array declaration '%s[%d]'\n", $1, $3);
             free($1);
           }
         | ID_TOK LBRACKET_TOK RBRACKET_TOK
           {
             // Add array without size
             data_type_t array_type;
             switch(current_type) {
                 case TYPE_INT: array_type = TYPE_INT_ARRAY; break;
                 case TYPE_FLOAT: array_type = TYPE_FLOAT_ARRAY; break;
                 case TYPE_CHAR: array_type = TYPE_CHAR_ARRAY; break;
                 default: array_type = current_type; break;
             }
             if (!add_symbol_with_attrs($1, array_type, get_current_scope_type(), 
                                       line_number, 0, 1, 0, 0)) {
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
                 if (!add_symbol($2, token_to_type($1), SCOPE_GLOBAL, line_number, 1)) {
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
                 if (!add_symbol($2, token_to_type($1), SCOPE_GLOBAL, line_number, 1)) {
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
                       if (!add_symbol($2, token_to_type($1), SCOPE_GLOBAL, line_number, 1)) {
                           error_count++;
                       }
                       free($2);
                     } LPAREN_TOK RPAREN_TOK SEMICOLON_TOK
                     { print_syntax_success("Function declaration"); }
                    | data_type ID_TOK {
                       // Add function declaration to symbol table
                       if (!add_symbol($2, token_to_type($1), SCOPE_GLOBAL, line_number, 1)) {
                           error_count++;
                       }
                       free($2);
                     } LPAREN_TOK parameter_list RPAREN_TOK SEMICOLON_TOK
                     { print_syntax_success("Function declaration with parameters"); }
                    ;

function_definition: data_type ID_TOK {
                      // Add function to symbol table
                      if (!add_symbol($2, token_to_type($1), SCOPE_GLOBAL, line_number, 1)) {
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
                      if (!add_symbol($2, token_to_type($1), SCOPE_GLOBAL, line_number, 1)) {
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
                    { 
                      check_condition_type($3.type);
                      print_syntax_success("If statement"); 
                    }
                   | IF_TOK LPAREN_TOK expression RPAREN_TOK statement ELSE_TOK statement
                    { 
                      check_condition_type($3.type);
                      print_syntax_success("If-else statement"); 
                    }
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
                    { 
                      check_condition_type($3.type);
                      print_syntax_success("While loop"); 
                    }
                   | FOR_TOK LPAREN_TOK expression_statement expression_statement RPAREN_TOK statement
                    { print_syntax_success("For loop"); }
                   | FOR_TOK LPAREN_TOK expression_statement expression_statement expression RPAREN_TOK statement
                    { print_syntax_success("For loop with increment"); }
                   | DO_TOK statement WHILE_TOK LPAREN_TOK expression RPAREN_TOK SEMICOLON_TOK
                    { 
                      check_condition_type($5.type);
                      print_syntax_success("Do-while loop"); 
                    }
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
           { $$ = $1; }
          | expression COMMA_TOK assignment_expr
           { $$.type = $3.type; $$.is_lvalue = 0; }
          | expression error assignment_expr
           {
             printf("SYNTAX ERROR (Line %d): Missing comma ',' between expressions\n", line_number);
             error_count++;
             yyerrok;
             $$.type = TYPE_UNKNOWN; $$.is_lvalue = 0;
           }
          | expression COMMA_TOK error
           {
             printf("SYNTAX ERROR (Line %d): Invalid expression after comma\n", line_number);
             error_count++;
             yyerrok;
             $$.type = TYPE_UNKNOWN; $$.is_lvalue = 0;
           }
          ;

assignment_expr: ternary_expr
                { $$ = $1; }
               | unary_expr ASSIGN_TOK assignment_expr
                {
                  check_assignment_type($1.type, $3.type, $1.is_lvalue);
                  $$.type = $1.type;
                  $$.is_lvalue = 0;
                }
               | unary_expr ADD_ASSIGN_TOK assignment_expr
                {
                  check_assignment_type($1.type, $3.type, $1.is_lvalue);
                  check_binary_op_type($1.type, $3.type, "+");
                  $$.type = $1.type;
                  $$.is_lvalue = 0;
                }
               | unary_expr SUB_ASSIGN_TOK assignment_expr
                {
                  check_assignment_type($1.type, $3.type, $1.is_lvalue);
                  check_binary_op_type($1.type, $3.type, "-");
                  $$.type = $1.type;
                  $$.is_lvalue = 0;
                }
               | unary_expr MUL_ASSIGN_TOK assignment_expr
                {
                  check_assignment_type($1.type, $3.type, $1.is_lvalue);
                  check_binary_op_type($1.type, $3.type, "*");
                  $$.type = $1.type;
                  $$.is_lvalue = 0;
                }
               | unary_expr DIV_ASSIGN_TOK assignment_expr
                {
                  check_assignment_type($1.type, $3.type, $1.is_lvalue);
                  check_binary_op_type($1.type, $3.type, "/");
                  $$.type = $1.type;
                  $$.is_lvalue = 0;
                }
               | unary_expr MOD_ASSIGN_TOK assignment_expr
                {
                  check_assignment_type($1.type, $3.type, $1.is_lvalue);
                  check_binary_op_type($1.type, $3.type, "%");
                  $$.type = $1.type;
                  $$.is_lvalue = 0;
                }
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
             { $$ = $1; }
            | logical_or_expr TERNARY_TOK expression COLON_TOK ternary_expr
             {
               if (!are_types_compatible($3.type, $5.type)) {
                 char msg[256];
                 sprintf(msg, "Type mismatch in ternary operator: '%s' and '%s' are not compatible",
                         type_to_string($3.type), type_to_string($5.type));
                 print_type_error(msg);
               }
               $$.type = $3.type;
               $$.is_lvalue = 0;
             }
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
                { $$ = $1; }
               | logical_or_expr OR_TOK logical_and_expr
                {
                  $$.type = check_logical_op_type($1.type, $3.type, "||");
                  $$.is_lvalue = 0;
                }
               ;

logical_and_expr: bit_or_expr
                 { $$ = $1; }
                | logical_and_expr AND_TOK bit_or_expr
                 {
                   $$.type = check_logical_op_type($1.type, $3.type, "&&");
                   $$.is_lvalue = 0;
                 }
                ;

bit_or_expr: bit_xor_expr
            { $$ = $1; }
           | bit_or_expr BIT_OR_TOK bit_xor_expr
            {
              $$.type = check_binary_op_type($1.type, $3.type, "|");
              $$.is_lvalue = 0;
            }
           ;

bit_xor_expr: bit_and_expr
             { $$ = $1; }
            | bit_xor_expr BIT_XOR_TOK bit_and_expr
             {
               $$.type = check_binary_op_type($1.type, $3.type, "^");
               $$.is_lvalue = 0;
             }
            ;

bit_and_expr: equality_expr
             { $$ = $1; }
            | bit_and_expr BIT_AND_TOK equality_expr
             {
               $$.type = check_binary_op_type($1.type, $3.type, "&");
               $$.is_lvalue = 0;
             }
            ;

equality_expr: relational_expr
              { $$ = $1; }
             | equality_expr EQ_TOK relational_expr
              {
                $$.type = check_relational_op_type($1.type, $3.type, "==");
                $$.is_lvalue = 0;
              }
             | equality_expr NEQ_TOK relational_expr
              {
                $$.type = check_relational_op_type($1.type, $3.type, "!=");
                $$.is_lvalue = 0;
              }
             ;

relational_expr: shift_expr
                { $$ = $1; }
               | relational_expr LT_TOK shift_expr
                {
                  $$.type = check_relational_op_type($1.type, $3.type, "<");
                  $$.is_lvalue = 0;
                }
               | relational_expr GT_TOK shift_expr
                {
                  $$.type = check_relational_op_type($1.type, $3.type, ">");
                  $$.is_lvalue = 0;
                }
               | relational_expr LE_TOK shift_expr
                {
                  $$.type = check_relational_op_type($1.type, $3.type, "<=");
                  $$.is_lvalue = 0;
                }
               | relational_expr GE_TOK shift_expr
                {
                  $$.type = check_relational_op_type($1.type, $3.type, ">=");
                  $$.is_lvalue = 0;
                }
               ;

shift_expr: additive_expr
           { $$ = $1; }
          | shift_expr BIT_LSHIFT_TOK additive_expr
           {
             $$.type = check_binary_op_type($1.type, $3.type, "<<");
             $$.is_lvalue = 0;
           }
          | shift_expr BIT_RSHIFT_TOK additive_expr
           {
             $$.type = check_binary_op_type($1.type, $3.type, ">>");
             $$.is_lvalue = 0;
           }
          ;

additive_expr: multiplicative_expr
              { $$ = $1; }
             | additive_expr ADD_TOK multiplicative_expr
              {
                $$.type = check_binary_op_type($1.type, $3.type, "+");
                $$.is_lvalue = 0;
              }
             | additive_expr SUB_TOK multiplicative_expr
              {
                $$.type = check_binary_op_type($1.type, $3.type, "-");
                $$.is_lvalue = 0;
              }
             ;

multiplicative_expr: unary_expr
                    { $$ = $1; }
                   | multiplicative_expr MUL_TOK unary_expr
                    {
                      $$.type = check_binary_op_type($1.type, $3.type, "*");
                      $$.is_lvalue = 0;
                    }
                   | multiplicative_expr DIV_TOK unary_expr
                    {
                      $$.type = check_binary_op_type($1.type, $3.type, "/");
                      $$.is_lvalue = 0;
                    }
                   | multiplicative_expr MOD_TOK unary_expr
                    {
                      $$.type = check_binary_op_type($1.type, $3.type, "%");
                      $$.is_lvalue = 0;
                    }
                   ;

unary_expr: postfix_expr
           { $$ = $1; }
          | INC_TOK unary_expr
           {
             if (!$2.is_lvalue) {
               print_type_error("Increment operator requires an lvalue");
             }
             $$.type = $2.type;
             $$.is_lvalue = 0;
           }
          | DEC_TOK unary_expr
           {
             if (!$2.is_lvalue) {
               print_type_error("Decrement operator requires an lvalue");
             }
             $$.type = $2.type;
             $$.is_lvalue = 0;
           }
          | unary_operator unary_expr
           {
             if (!is_numeric_type($2.type)) {
               char msg[256];
               sprintf(msg, "Unary operator requires numeric operand, got '%s'", type_to_string($2.type));
               print_type_error(msg);
             }
             $$.type = $2.type;
             $$.is_lvalue = 0;
           }
          ;

unary_operator: ADD_TOK %prec UNARY_PLUS
              | SUB_TOK %prec UNARY_MINUS
              | NOT_TOK
              | BIT_NOT_TOK
              ;

postfix_expr: primary_expr
             { $$ = $1; }
            | postfix_expr LBRACKET_TOK expression RBRACKET_TOK
             {
               // Array subscripting
               if (!is_array_type($1.type) && !is_pointer_type($1.type)) {
                 check_pointer_dereference($1.type);
               }
               if (!is_numeric_type($3.type)) {
                 char msg[256];
                 sprintf(msg, "Array index must be numeric type, got '%s'", type_to_string($3.type));
                 print_type_error(msg);
               }
               $$.type = get_base_type($1.type);
               $$.is_lvalue = 1;
             }
            | postfix_expr LBRACKET_TOK expression error
              {
                printf("SYNTAX ERROR (Line %d): Missing closing bracket ']'\n", line_number);
                error_count++;
                yyerrok;
                $$.type = TYPE_UNKNOWN; $$.is_lvalue = 0;
              }
            | postfix_expr LBRACKET_TOK error RBRACKET_TOK
              {
                printf("SYNTAX ERROR (Line %d): Invalid array index expression\n", line_number);
                error_count++;
                yyerrok;
                $$.type = TYPE_UNKNOWN; $$.is_lvalue = 0;
              }
            | postfix_expr LPAREN_TOK RPAREN_TOK
              { 
                print_syntax_success("Function call");
                $$.type = TYPE_INT; // Assume int return type
                $$.is_lvalue = 0;
              }
            | postfix_expr LPAREN_TOK argument_list RPAREN_TOK
              { 
                print_syntax_success("Function call with arguments");
                $$.type = TYPE_INT; // Assume int return type
                $$.is_lvalue = 0;
              }
            | postfix_expr LPAREN_TOK argument_list error
              {
                printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in function call\n", line_number);
                error_count++;
                yyerrok;
                $$.type = TYPE_UNKNOWN; $$.is_lvalue = 0;
              }
            | postfix_expr LPAREN_TOK error RPAREN_TOK
              {
                printf("SYNTAX ERROR (Line %d): Invalid function arguments\n", line_number);
                error_count++;
                yyerrok;
                $$.type = TYPE_UNKNOWN; $$.is_lvalue = 0;
              }
            | postfix_expr INC_TOK
             {
               if (!$1.is_lvalue) {
                 print_type_error("Increment operator requires an lvalue");
               }
               $$.type = $1.type;
               $$.is_lvalue = 0;
             }
            | postfix_expr DEC_TOK
             {
               if (!$1.is_lvalue) {
                 print_type_error("Decrement operator requires an lvalue");
               }
               $$.type = $1.type;
               $$.is_lvalue = 0;
             }
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
                   $$.type = TYPE_UNKNOWN;
                   $$.is_lvalue = 0;
               } else {
                   symbol_t* sym = lookup_symbol($1);
                   printf("VARIABLE USE: '%s' (Type: %s, Scope: %s)\n", 
                          $1, type_to_string(sym->type), scope_to_string(sym->scope));
                   $$.type = sym->type;
                   $$.is_lvalue = !sym->is_array; // Arrays are not lvalues directly
               }
               free($1);
             }
            | INTCONST_TOK
             {
               $$.type = TYPE_INT;
               $$.is_lvalue = 0;
             }
            | FLOATCONST_TOK
             {
               $$.type = TYPE_FLOAT;
               $$.is_lvalue = 0;
             }
            | STRING_TOK 
             { 
               free($1);
               $$.type = TYPE_CHAR_PTR;
               $$.is_lvalue = 0;
             }
            | LPAREN_TOK expression RPAREN_TOK
             {
               $$ = $2;
             }
            | LPAREN_TOK expression error
              {
                printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')'\n", line_number);
                error_count++;
                yyerrok;
                $$.type = TYPE_UNKNOWN;
                $$.is_lvalue = 0;
              }
            | LPAREN_TOK error RPAREN_TOK
              {
                printf("SYNTAX ERROR (Line %d): Invalid expression inside parentheses\n", line_number);
                error_count++;
                yyerrok;
                $$.type = TYPE_UNKNOWN;
                $$.is_lvalue = 0;
              }
            ;

%%

#include "lex.yy.c"

// Define token_to_type function after tokens are defined
data_type_t token_to_type(int token) {
    switch(token) {
        case INT_TOK: return TYPE_INT;
        case FLOAT_TOK: return TYPE_FLOAT;
        case CHAR_TOK: return TYPE_CHAR;
        case VOID_TOK: return TYPE_VOID;
        default: return TYPE_UNKNOWN;
    }
}

int main() {
    printf("=== C LANGUAGE SUBSET PARSER WITH TYPE CHECKING ===\n");
    printf("Parsing input...\n\n");
    
    if (yyparse() == 0) {
        printf("\n=== PARSING SUCCESSFUL ===\n");
        if (error_count == 0) {
            printf("No syntax or type errors found!\n");
        } else {
            printf("Parsing completed with %d error(s).\n", error_count);
        }
    } else {
        printf("\n=== PARSING FAILED ===\n");
        printf("Errors found at line %d\n", line_number);
    }
    
    return 0;
}

void yyerror(char *s) {
    printf("SYNTAX ERROR (Line %d): %s near '%s'\n", line_number, s, yytext);
    error_count++;
}