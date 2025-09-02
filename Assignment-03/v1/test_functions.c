// Test case 3: Program with user-defined functions
int add(int a, int b);
int multiply(int x, int y);

int add(int a, int b) {
    return a + b;
}

int multiply(int x, int y) {
    int result;
    result = x * y;
    return result;
}

int main() {
    int num1, num2, sum, product;
    
    num1 = 5;
    num2 = 3;
    
    sum = add(num1, num2);
    product = multiply(num1, num2);
    
    return 0;
}