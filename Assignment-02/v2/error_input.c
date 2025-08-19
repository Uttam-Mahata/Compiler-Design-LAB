

int this_identifier_name_is_way_too_long_and_exceeds_thirtyone_characters;

int x = 12345678901234567890;

float y = 12345678901.123456;

$ @ # illegal characters here

// 5. UNMATCHED STRING - missing closing quote
char* str1 = "This string has no closing quote

// 6. UNMATCHED STRING - newline in string  
char* str2 = "String with
newline";

// 7. SPELLING ERRORS IN KEYWORDS
itn main() {
    flot pi = 3.14;
    chr letter = 'a';
    whle (1) {
        fr (int i = 0; i < 10; i++) {
            od {
                break;
            } whle (0);
        }
    }
    fi (1) {
        retrun 0;
    } esle {
        retrun 1;
    }
}

// 8. INVALID NUMBERS WITH ILLEGAL CHARACTERS
int a = 12$34;
int b = 56@78;  
int c = 90#12;
int d = 123abc456;

// 9. INVALID IDENTIFIERS WITH ILLEGAL CHARACTERS
int var$name = 10;
int var@name = 20;
int var#name = 30;

// 10. UNMATCHED CHARACTER CONSTANTS
char ch1 = 'a;
char ch2 = 'abc';

// 11. MIXED ERRORS
itn very_long_identifier_name_with$illegal@chars# = 123456789012$34;