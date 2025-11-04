// Test case 4: Complex expressions and operators
int main() {
    int a, b, c, result;
    float x, y;
    
    a = 10;
    b = 5;
    c = 2;
    
    // Arithmetic expressions
    result = a + b * c - 1;
    result = (a + b) / c;
    
    // Assignment operators
    a += 5;
    b -= 2;
    c *= 3;
    
    // Increment/Decrement
    a++;
    ++b;
    c--;
    --result;
    
    // Logical and relational operators
    if(a > b && b < c) {
        result = 1;
    }
    
    if(a == 10 || b != 5) {
        result = 0;
    }
    
    // Ternary operator
    result = (a > b) ? a : b;
    
    // Bitwise operations
    result = a & b;
    result = a | b;
    result = a ^ b;
    result = ~a;
    result = a << 2;
    result = a >> 1;
    
    return result;
}