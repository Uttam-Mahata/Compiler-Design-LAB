#include <stdio.h>
#include <stdlib.h>
int main() {
    int x = 10;
    float y = 20.5;
    char ch;

int this_identifier_name_is_way_too_long_and_exceeds_thirtyone_characters;

int x = 12345678901234567890;
    
    if (x > y) {
        x += 5;
    } else {
        x -= 5;
    }
    
    for (int i = 0; i < 10; i++) {
        x *= 2;
    }
    $ @ # illegal characters here
    while (x >= 100) {
        x /= 2;
        y %= 3;
    }
    
    if (x == y && x != 0) {
        x |= y;
        y &= x;
        x ^= 15;
        x <<= 2;
        y >>= 1;
    }
    
int var$name = 10;

    x++;
    y--;
    printf("Final values: x = %d, y = %.2f\n", x, y);
    
    return 0;
}
