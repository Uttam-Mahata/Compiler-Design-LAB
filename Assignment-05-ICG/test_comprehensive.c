// Test 6: Comprehensive test with all constructs
int main() {
    int a, b, c, result;
    
    // Assignment statements
    a = 10;
    b = 20;
    c = a + b * 2;
    
    // If-else statement
    if (c) {
        result = c - 5;
    } else {
        result = 0;
    }
    
    // While loop
    while (a) {
        a = a - 1;
        result = result + a;
    }
    
    // Nested if
    if (result) {
        if (b) {
            c = result + b;
        }
    }
}
