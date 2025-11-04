// Test file for expression type checking
// Assignment-04: Type checking in expressions

int main() {
    int a, b, c;
    float x, y, z;
    
    a = 10;
    b = 20;
    x = 1.5;
    y = 2.5;
    
    // Valid: int operations
    c = a + b;
    c = a * b;
    c = a - b;
    
    // Valid: float operations
    z = x + y;
    z = x * y;
    
    // Type Error: mixing int and float in binary operation
    c = a + x;
    
    // Type Error: mixing types in multiplication
    z = b * y;
    
    // Type Error: incompatible types in subtraction
    a = x - y;
    
    // Valid: relational operators with same types
    if (a > b) {
        c = 1;
    }
    
    if (x < y) {
        z = 0.0;
    }
    
    // Type Error: relational with mixed types
    if (a == x) {
        c = 0;
    }
    
    return 0;
}
