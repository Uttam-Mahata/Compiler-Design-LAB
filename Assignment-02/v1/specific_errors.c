// Specific test cases for each error type

// Error Type 1: Identifier length exceeding limit
int this_identifier_is_way_too_long_and_exceeds_the_maximum_allowed_length_of_thirty_one_characters = 100;

// Error Type 2: Numeric constants too long  
int huge_number = 12345678901234567890123456789012345;
float big_float = 123456789012345.123456789012345;

// Error Type 3: Illegal characters
char illegal1 = '@';
int illegal2 = 100$;
float illegal3 = 3.14#;

// Error Type 4: Spelling errors in keywords
itn number1;      // should be 'int'
flot number2;     // should be 'float' 
chr letter;       // should be 'char'
fr (int i = 0; i < 10; i++) { }  // should be 'for'
whle (1) { }      // should be 'while'
fi (1) { }        // should be 'if'
esle { }          // should be 'else'
retrun 0;         // should be 'return'

// Error Type 5: Replacing characters with incorrect ones
int x = 12$34;    // $ instead of proper digit
float y = 45@67;  // @ in the middle of number
int z = 99#88;    // # in the middle of number