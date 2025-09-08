// Test file for syntax error detection
// Contains various syntax errors that should be caught

int main() {
    // Missing closing brace
    int x = 5;
    if (x > 0) {
        x = x + 1;
    // Missing closing brace

    // Missing semicolon
    int y = 10
    
    // Missing closing parenthesis
    if (x > y {
        x = y;
    }
    
    // Missing opening parenthesis
    if x < y) {
        y = x;
    }
    
    // Missing closing bracket
    int arr[10;
    arr[0 = 5;
    
    // Missing comma in parameter list
    int func(int a int b) {
        return a + b;
    }
    
    // Missing semicolon in for loop
    for (int i = 0 i < 10; i++) {
        arr[i] = i;
    }
    
    // Missing closing parenthesis in function call
    func(1, 2;
    
    return 0;
}