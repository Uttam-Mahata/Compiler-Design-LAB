// Test file with correct syntax (no errors)

#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 10;
    float y = 20.5;
    char ch = 'a';
    
    printf("Values: x = %d, y = %.2f, ch = %c\n", x, y, ch);
    
    if (x > 5) {
        printf("x is greater than 5\n");
    } else {
        printf("x is not greater than 5\n");
    }
    
    for (int i = 0; i < 3; i++) {
        printf("Loop iteration: %d\n", i);
    }
    
    while (x > 0) {
        x--;
        printf("x = %d\n", x);
    }
    
    return 0;
}