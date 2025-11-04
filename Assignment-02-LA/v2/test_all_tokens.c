// Test file to verify all required tokens
int main() {
    // a) Arithmetic, Relational, Logical, Bitwise and Assignment Operators
    int a = 5 + 3 - 2 * 4 / 2 % 3;
    float b = 10.5;
    char c;
    
    // Relational operators
    if (a < b && a > 0 && a <= 10 && b >= 5.0 && a == 5 && b != 0) {
        a++;
    }
    
    // Logical operators
    if (a && b || !c) {
        a--;
    }
    
    // Bitwise operators  
    a = a & 7;
    a = a | 8;
    a = a ^ 15;
    a = ~a;
    a = a << 2;
    a = a >> 1;
    
    // Assignment operators
    a += 5;
    a -= 3;
    a *= 2;
    a /= 4;
    a %= 7;
    
    // b) Reserved words: int, float, char, for, do, while, if and else
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            continue;
        } else {
            break;
        }
    }
    
    do {
        a++;
    } while (a < 100);
    
    // c) Identifier - variables like a, b, c, i are identifiers
    // d) Integer Constants - numbers like 5, 3, 2, 4, 10, etc.
    // e) Parentheses, Curly braces - (), {}, []
    
    int array[10];
    array[0] = (a + b) ? a : b;
    
    return 0;
}