#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main() {
    int x = 10;
    float y = 3.14;
    char ch = 'A';
    
    if (x > 5 && y <= 10.0) {
        x += 1;
        y *= 2;
    } else {
        x--;
        y /= 2;
    }
    
    for (int i = 0; i < x; i++) {
        if (i % 2 == 0) {
            printf("Even: %d\n", i);
        }
    }
    
    while (x > 0) {
        x >>= 1;
        y |= 0x01;
    }
    
    return 0;
}