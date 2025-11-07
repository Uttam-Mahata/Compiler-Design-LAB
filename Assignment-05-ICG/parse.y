%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "symbol_table.h"
#include "icg.h"

extern int line_number;
extern int error_count;
extern char* yytext;
extern int yylex();

void yyerror(char *);
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
    if (!is_numeric_type(left) || !is_numeric_type(right)) {
        char msg[256];
        sprintf(msg, "Binary operator '%s' requires numeric operands, got '%s' and '%s'",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }

    if (!are_types_compatible(left, right)) {
        char msg[256];
        sprintf(msg, "Type mismatch in binary operation '%s': '%s' and '%s' are not compatible",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }

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

    return TYPE_INT;
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
        sprintf(msg, "Cannot dereference non-pointer type '%s'",
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
        char* place;  // For holding temporary variable or identifier name
    } expr_info;
    struct {
        int next_list[100];
        int next_count;
        int true_list[100];
        int true_count;
        int false_list[100];
        int false_count;
    } stmt_info;
    struct {
        char* label;
        int quad;
    } marker_info;
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
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE_TOK
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
program: { init_symbol_table(); } translation_unit
         {
           print_syntax_success("C program");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total errors: %d\n", error_count);
           print_symbol_table();
         }
       ;

translation_unit: translation_unit external_declaration
                | external_declaration
                ;

/* External declarations */
external_declaration: global_variable_declaration
                    | function_declaration
                    ;

/* Global variable declarations */
global_variable_declaration: data_type {
                              current_type = token_to_type($1);
                            } init_declarator_list SEMICOLON_TOK
                            { print_syntax_success("Global variable declaration"); }
                           ;

init_declarator_list: init_declarator_list COMMA_TOK init_declarator
                    | init_declarator
                    ;

init_declarator: declarator
               | declarator ASSIGN_TOK assignment_expr
                 { print_syntax_success("Variable initialization"); }
               ;

declarator: ID_TOK
           {
             if (!add_symbol($1, current_type, get_current_scope_type(), line_number, 0)) {
                 error_count++;
             }
             free($1);
           }
         | ID_TOK LBRACKET_TOK INTCONST_TOK RBRACKET_TOK
           {
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
             free($1);
           }
         | ID_TOK LBRACKET_TOK RBRACKET_TOK
           {
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
             free($1);
           }
         ;

/* Function declarations (both prototypes and definitions) */
function_declaration: data_type ID_TOK {
                       if (!add_symbol($2, token_to_type($1), SCOPE_GLOBAL, line_number, 1)) {
                           error_count++;
                       }
                       free($2);
                     } LPAREN_TOK RPAREN_TOK function_tail
                     {
                       print_syntax_success("Function (no parameters)");
                     }
                   | data_type ID_TOK {
                       if (!add_symbol($2, token_to_type($1), SCOPE_GLOBAL, line_number, 1)) {
                           error_count++;
                       }
                       free($2);
                     } LPAREN_TOK parameter_list RPAREN_TOK function_tail
                     {
                       print_syntax_success("Function (with parameters)");
                     }
                   ;

function_tail: SEMICOLON_TOK
               { /* Function prototype */ }
             | { enter_scope(); } compound_statement
               {
                 /* Function definition */
                 exit_scope();
               }
             ;

/* Data types */
data_type: INT_TOK { $$ = INT_TOK; }
         | FLOAT_TOK { $$ = FLOAT_TOK; }
         | CHAR_TOK { $$ = CHAR_TOK; }
         | VOID_TOK { $$ = VOID_TOK; }
         ;

/* Parameter lists */
parameter_list: parameter_list COMMA_TOK parameter
              | parameter
              ;

parameter: data_type ID_TOK
          {
            if (!add_symbol($2, token_to_type($1), SCOPE_FUNCTION, line_number, 0)) {
                error_count++;
            }
            free($2);
          }
         | data_type ID_TOK LBRACKET_TOK RBRACKET_TOK
          {
            data_type_t array_type;
            switch(token_to_type($1)) {
                case TYPE_INT: array_type = TYPE_INT_ARRAY; break;
                case TYPE_FLOAT: array_type = TYPE_FLOAT_ARRAY; break;
                case TYPE_CHAR: array_type = TYPE_CHAR_ARRAY; break;
                default: array_type = token_to_type($1); break;
            }
            if (!add_symbol_with_attrs($2, array_type, SCOPE_FUNCTION,
                                      line_number, 0, 1, 0, 0)) {
                error_count++;
            }
            free($2);
          }
         ;

/* Compound statements */
compound_statement: LBRACE_TOK statement_list RBRACE_TOK
                   { print_syntax_success("Compound statement"); }
                  | LBRACE_TOK RBRACE_TOK
                   { print_syntax_success("Empty compound statement"); }
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
         ;

/* Variable declarations inside functions/blocks */
declaration_statement: data_type {
                        current_type = token_to_type($1);
                      } init_declarator_list SEMICOLON_TOK
                      { print_syntax_success("Local variable declaration"); }
                     ;

/* Expression statements */
expression_statement: expression SEMICOLON_TOK
                     { print_syntax_success("Expression statement"); }
                    | SEMICOLON_TOK
                     { print_syntax_success("Empty statement"); }
                    ;

/* Selection statements */
selection_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement %prec LOWER_THAN_ELSE
                    {
                      check_condition_type($3.type);
                      print_syntax_success("If statement");
                      
                      // Generate code: if (expr == 0) goto after_if
                      // Note: In a full implementation, labels would be generated
                      // with proper backpatching
                      char* false_label = new_label();
                      gen("ifFalse", $3.place, "", false_label);
                      emit_label(false_label);
                    }
                   | IF_TOK LPAREN_TOK expression RPAREN_TOK statement ELSE_TOK statement
                    {
                      check_condition_type($3.type);
                      print_syntax_success("If-else statement");
                      
                      // Generate code for if-else
                      // Note: This is a simplified version
                      // Full implementation would generate:
                      // ifFalse expr goto L_else
                      // ... if_body ...
                      // goto L_end
                      // L_else: ... else_body ...
                      // L_end:
                    }
                   ;

/* Iteration statements */
iteration_statement: WHILE_TOK LPAREN_TOK expression RPAREN_TOK statement
                    {
                      check_condition_type($3.type);
                      print_syntax_success("While loop");
                      
                      // Generate while loop code
                      // Note: Full implementation would generate:
                      // L_begin: ifFalse expr goto L_end
                      // ... loop_body ...
                      // goto L_begin
                      // L_end:
                      char* begin_label = new_label();
                      char* end_label = new_label();
                      gen("label_begin", "", "", begin_label);
                      gen("ifFalse", $3.place, "", end_label);
                      gen("goto", "", "", begin_label);
                      gen("label_end", "", "", end_label);
                    }
                   | FOR_TOK LPAREN_TOK expression_statement expression_statement RPAREN_TOK statement
                    { print_syntax_success("For loop"); }
                   | FOR_TOK LPAREN_TOK expression_statement expression_statement expression RPAREN_TOK statement
                    { print_syntax_success("For loop with increment"); }
                   | DO_TOK statement WHILE_TOK LPAREN_TOK expression RPAREN_TOK SEMICOLON_TOK
                    {
                      check_condition_type($5.type);
                      print_syntax_success("Do-while loop");
                      
                      // Generate: do-while loop structure
                      char* begin_label = new_label();
                      gen("ifTrue", $5.place, "", begin_label);
                    }
                   ;

/* Jump statements */
jump_statement: RETURN_TOK expression SEMICOLON_TOK
               { print_syntax_success("Return statement with value"); }
              | RETURN_TOK SEMICOLON_TOK
               { print_syntax_success("Return statement"); }
              ;



/* Expressions */
expression: assignment_expr
           { $$ = $1; }
          | expression COMMA_TOK assignment_expr
           { $$.type = $3.type; $$.is_lvalue = 0; }
          ;

assignment_expr: ternary_expr
                { $$ = $1; }
               | unary_expr ASSIGN_TOK assignment_expr
                {
                  check_assignment_type($1.type, $3.type, $1.is_lvalue);
                  $$.type = $1.type;
                  $$.is_lvalue = 0;
                  
                  // Generate three-address code: lhs = rhs
                  gen("=", $3.place, "", $1.place);
                  $$.place = $1.place;
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
                
                // Generate: temp = arg1 + arg2
                $$.place = new_temp();
                gen("+", $1.place, $3.place, $$.place);
              }
             | additive_expr SUB_TOK multiplicative_expr
              {
                $$.type = check_binary_op_type($1.type, $3.type, "-");
                $$.is_lvalue = 0;
                
                // Generate: temp = arg1 - arg2
                $$.place = new_temp();
                gen("-", $1.place, $3.place, $$.place);
              }
             ;

multiplicative_expr: unary_expr
                    { $$ = $1; }
                   | multiplicative_expr MUL_TOK unary_expr
                    {
                      $$.type = check_binary_op_type($1.type, $3.type, "*");
                      $$.is_lvalue = 0;
                      
                      // Generate: temp = arg1 * arg2
                      $$.place = new_temp();
                      gen("*", $1.place, $3.place, $$.place);
                    }
                   | multiplicative_expr DIV_TOK unary_expr
                    {
                      $$.type = check_binary_op_type($1.type, $3.type, "/");
                      $$.is_lvalue = 0;
                      
                      // Generate: temp = arg1 / arg2
                      $$.place = new_temp();
                      gen("/", $1.place, $3.place, $$.place);
                    }
                   | multiplicative_expr MOD_TOK unary_expr
                    {
                      $$.type = check_binary_op_type($1.type, $3.type, "%");
                      $$.is_lvalue = 0;
                      
                      // Generate: temp = arg1 % arg2
                      $$.place = new_temp();
                      gen("%", $1.place, $3.place, $$.place);
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
          | SUB_TOK unary_expr %prec UNARY_MINUS
           {
             if (!is_numeric_type($2.type)) {
               char msg[256];
               sprintf(msg, "Unary minus requires numeric operand, got '%s'", type_to_string($2.type));
               print_type_error(msg);
             }
             $$.type = $2.type;
             $$.is_lvalue = 0;
             
             // Generate: temp = - arg
             $$.place = new_temp();
             gen("uminus", $2.place, "", $$.place);
           }
          | ADD_TOK unary_expr %prec UNARY_PLUS
           {
             if (!is_numeric_type($2.type)) {
               char msg[256];
               sprintf(msg, "Unary plus requires numeric operand, got '%s'", type_to_string($2.type));
               print_type_error(msg);
             }
             $$.type = $2.type;
             $$.is_lvalue = 0;
             $$.place = $2.place;  // Unary plus doesn't change value
           }
          | NOT_TOK unary_expr
           {
             if (!is_numeric_type($2.type)) {
               char msg[256];
               sprintf(msg, "Logical NOT requires numeric operand, got '%s'", type_to_string($2.type));
               print_type_error(msg);
             }
             $$.type = TYPE_INT;
             $$.is_lvalue = 0;
             
             // Generate: temp = ! arg
             $$.place = new_temp();
             gen("!", $2.place, "", $$.place);
           }
          | BIT_NOT_TOK unary_expr
           {
             if (!is_numeric_type($2.type)) {
               char msg[256];
               sprintf(msg, "Bitwise NOT requires numeric operand, got '%s'", type_to_string($2.type));
               print_type_error(msg);
             }
             $$.type = $2.type;
             $$.is_lvalue = 0;
             
             // Generate: temp = ~ arg
             $$.place = new_temp();
             gen("~", $2.place, "", $$.place);
           }
          ;

postfix_expr: primary_expr
             { $$ = $1; }
            | postfix_expr LBRACKET_TOK expression RBRACKET_TOK
             {
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
            | postfix_expr LPAREN_TOK RPAREN_TOK
              {
                print_syntax_success("Function call");
                $$.type = TYPE_INT;
                $$.is_lvalue = 0;
              }
            | postfix_expr LPAREN_TOK argument_list RPAREN_TOK
              {
                print_syntax_success("Function call with arguments");
                $$.type = TYPE_INT;
                $$.is_lvalue = 0;
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
             ;

primary_expr: ID_TOK
             {
               if (!is_variable_declared($1)) {
                   printf("ERROR (Line %d): Variable '%s' used before declaration\n", line_number, $1);
                   error_count++;
                   $$.type = TYPE_UNKNOWN;
                   $$.is_lvalue = 0;
                   $$.place = strdup("unknown");
               } else {
                   symbol_node_t* sym = lookup_symbol($1);
                   $$.type = sym->type;
                   $$.is_lvalue = !sym->is_array;
                   $$.place = strdup($1);  // Variable name is its place
               }
               free($1);
             }
            | INTCONST_TOK
             {
               $$.type = TYPE_INT;
               $$.is_lvalue = 0;
               
               // Integer constant - convert to string for place
               char* const_str = (char*)malloc(20);
               sprintf(const_str, "%d", $1);
               $$.place = const_str;
             }
            | FLOATCONST_TOK
             {
               $$.type = TYPE_FLOAT;
               $$.is_lvalue = 0;
               
               // Float constant - convert to string for place
               char* const_str = (char*)malloc(20);
               sprintf(const_str, "%g", $1);
               $$.place = const_str;
             }
            | STRING_TOK
             {
               $$.type = TYPE_CHAR_PTR;
               $$.is_lvalue = 0;
               $$.place = $1;  // Use string literal as place
             }
            | LPAREN_TOK expression RPAREN_TOK
             {
               $$ = $2;  // Parenthesized expression inherits everything
             }
            ;

%%

#include "lex.yy.c"

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
    printf("=== C COMPILER: LEXICAL + SYNTAX + TYPE CHECKING + ICG ===\n");
    printf("Parsing input...\n\n");

    // Initialize intermediate code generation
    init_icg();

    if (yyparse() == 0) {
        printf("\n=== PARSING SUCCESSFUL ===\n");
        if (error_count == 0) {
            printf("No errors found!\n");
        } else {
            printf("Parsing completed with %d error(s).\n", error_count);
        }
        
        // Close ICG and write to file
        close_icg();
        print_quad_array();
    } else {
        printf("\n=== PARSING FAILED ===\n");
        printf("Errors found at line %d\n", line_number);
        close_icg();
    }

    return 0;
}

void yyerror(char *s) {
    printf("SYNTAX ERROR (Line %d): %s near '%s'\n", line_number, s, yytext);
    error_count++;
}
