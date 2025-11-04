// Test file for conditional type checking
// Assignment-04: Type checking in conditional statements

int main() {
    int a, b;
    float x, y;
    
    a = 10;
    b = 20;
    x = 1.5;
    y = 2.5;
    
    // Valid: numeric condition
    if (a < b) {
        a = a + 1;
    }
    
    // Valid: numeric condition
    while (a < 100) {
        a = a + 1;
    }
    
    // Type Error: comparing int and float
    if (a < x) {
        b = 0;
    }
    
    // Type Error: mixing types in condition
    if (a && x) {
        b = 0;
    }
    
    // Valid: same types
    if (x < y) {
        x = 0.0;
    }
    
    return 0;
}
