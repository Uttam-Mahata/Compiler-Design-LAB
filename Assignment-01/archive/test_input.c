// Test file for lexical analyzer
#include <stdio.h>

int main() {
    // Variable declarations
    int a = 42;
    float b = 3.14159;
    char c = 'X';
    char str[] = "Hello World!";
    
    // Arithmetic operators
    int result = a + 5 - 2 * 3 / 4 % 2;
    a++; b--; a += 10; b -= 5; a *= 2; b /= 3;
    
    // Relational operators
    if (a > b && a >= 10 && b < 20 && b <= 15 && a == 42 && b != 0) {
        printf("Relational operators work!\n");
    }
    
    // Logical operators
    if ((a > 0) && (b > 0) || !(a < 0)) {
        printf("Logical operators work!\n");
    }
    
    // Bitwise operators
    int x = 0xFF;
    x = x << 2;
    x = x >> 1;
    x = x & 0x0F;
    x = x | 0xF0;
    x = x ^ 0xAA;
    x = ~x;
    
    // Assignment operators with bitwise
    x <<= 1;
    x >>= 2;
    x &= 0xFF;
    x |= 0x0F;
    x ^= 0xF0;
    
    // Parentheses, braces, brackets
    int arr[10] = {1, 2, 3, 4, 5};
    arr[0] = (a + b) * 2;
    
    // Loop constructs
    for (int i = 0; i < 10; i++) {
        if (arr[i] % 2 == 0) {
            continue;
        } else {
            break;
        }
    }
    
    while (a > 0) {
        a--;
    }
    
    do {
        b++;
    } while (b < 100);
    
    return 0;
}

