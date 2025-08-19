// Test file containing various lexical errors

#include <stdio.h>

// 1. Identifier too long (exceeds 31 characters)
int this_is_a_very_very_very_long_identifier_name_that_exceeds_limit = 10;

// 2. Numeric constant too long
int big_number = 12345678901234567890;

// 3. Illegal characters in code
int x = 12$34;
float y = 45@67;
char z = 'a#';

// 4. Spelling errors in keywords
itn main() {
    flot value = 3.14;
    chr character;
    
    // 5. Unmatched strings
    printf("This is an unmatched string
    char* message = "Another unmatched string;
    
    // 6. Invalid number formats
    int bad1 = 123abc;
    float bad2 = 45.67xyz;
    int bad3 = 999$$$;
    
    // 7. More illegal characters
    int result = x & y @ z;
    
    // 8. Unmatched character constants
    char bad_char = 'unclosed;
    
    // 9. Mixed illegal characters in identifiers
    int var$name = 10;
    float my@variable = 20.5;
    
    whle (x > 0) {  // Spelling error: 'while' misspelled as 'whle'
        x--;
    }
    
    retrun 0;  // Spelling error: 'return' misspelled as 'retrun'
}