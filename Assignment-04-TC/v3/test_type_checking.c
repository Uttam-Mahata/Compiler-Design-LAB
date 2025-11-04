// Test file for type checking
// Assignment-04: Type Checking

// Test 1: Basic type compatibility
int main() {
    int a, b, c;
    float x, y;
    
    // Valid: same types
    a = 10;
    b = 20;
    c = a + b;
    
    x = 3.14;
    y = 2.5;
    
    // Type Error: mixing int and float
    a = x + y;
    
    // Valid: int to int assignment
    c = a;
    
    return 0;
}
