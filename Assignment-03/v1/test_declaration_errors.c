// Test file for declaration errors

// Missing semicolon after global declaration
int global_var

// Invalid data type
invalid_type x;

// Missing data type
y = 5;

int main() {
    // Missing semicolon after local declaration
    float local_var
    
    // Invalid array declaration
    int arr[;
    
    // Missing parameter types
    int func(a, b) {
        return a + b;
    }
    
    // Missing closing parenthesis in function declaration
    void test_func(int x;
    
    return 0;
}