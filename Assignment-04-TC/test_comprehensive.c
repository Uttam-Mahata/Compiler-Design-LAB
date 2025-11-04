// Comprehensive test file combining all type checking features
// Assignment-04: Complete type checking demonstration

int global_int;
float global_float;

int compute(int x, int y) {
    int result;
    result = x + y;
    return result;
}

int main() {
    int a, b, c;
    float x, y, z;
    int numbers[10];
    float values[5];
    int i;
    
    // Initialize variables
    a = 10;
    b = 20;
    x = 1.5;
    y = 2.5;
    i = 0;
    
    // Test 1: Valid arithmetic with same types
    c = a + b;
    c = a * b - 5;
    z = x + y;
    z = x * y / 2.0;
    
    // Test 2: TYPE ERROR - mixing int and float
    c = a + x;
    z = b * y;
    
    // Test 3: Valid array operations
    numbers[0] = 100;
    numbers[i] = a;
    values[0] = 3.14;
    values[1] = x;
    
    // Test 4: TYPE ERROR - wrong array assignment type
    numbers[0] = x;
    values[0] = a;
    
    // Test 5: Valid conditionals
    if (a < b) {
        c = a;
    }
    
    if (x > y) {
        z = x;
    }
    
    // Test 6: TYPE ERROR - mixed types in conditionals
    if (a < x) {
        c = 0;
    }
    
    while (a < 100) {
        a = a + 1;
    }
    
    // Test 7: TYPE ERROR - using integer as pointer
    a[0] = 50;
    
    // Test 8: Valid relational operations
    if (a == b) {
        c = 1;
    }
    
    if (x != y) {
        z = 0.0;
    }
    
    // Test 9: TYPE ERROR - mixed types in equality
    if (a == x) {
        c = 0;
    }
    
    // Test 10: Valid function call
    c = compute(a, b);
    
    // Test 11: Logical operations with type checking
    if (a > 0 && b > 0) {
        c = a + b;
    }
    
    // Test 12: TYPE ERROR - logical with mixed types
    if (a && x) {
        c = 0;
    }
    
    return 0;
}
