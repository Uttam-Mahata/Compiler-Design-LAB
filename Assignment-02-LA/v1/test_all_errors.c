// Test file for comprehensive lexical error detection
#include <stdio.h>

int main() {
    // Test 1: Valid tokens
    int x = 10;
    float y = 20.5;
    char ch = 'a';
    
    // Test 2: Identifier too long (over 31 characters)
    int this_is_a_very_long_identifier_name_that_exceeds_limit = 5;
    
    // Test 3: Numeric constants too long (over 10 digits)
    int big_number = 12345678901;
    float big_float = 123456789.12345;
    
    // Test 4: Illegal characters
    int var$name = 10;
    float test@value = 5.5;
    int another#var = 20;
    
    // Test 5: Invalid number formats with illegal characters
    int num1 = 123$45;
    float num2 = 12@34.56;
    int num3 = 456#789;
    
    // Test 6: Spelling errors in keywords
    itn spelling_error1 = 10;
    flot spelling_error2 = 5.5;
    chr spelling_error3 = 'x';
    fi (x > 0) {
        whle (x > 0) {
            x--;
        }
    }
    
    // Test 7: Unmatched strings
    char* str1 = "This is an unmatched string
    char* str2 = "Another unmatched string;
    
    // Test 8: Invalid character constants
    char invalid_char1 = 'abc';
    char invalid_char2 = 'unmatched;
    
    // Test 9: Mixed illegal characters in identifiers
    int var$name@test = 10;
    
    // Test 10: Numbers starting with digits but containing letters
    int mixed1 = 123abc;
    float mixed2 = 456def.789;
    
    return 0;
}