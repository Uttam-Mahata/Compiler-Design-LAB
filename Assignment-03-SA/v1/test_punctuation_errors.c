// Test file for missing punctuation errors

int main() {
    int x, y z;  // Missing comma between y and z
    
    int a = 5    // Missing semicolon
    int b = 10;  
    
    // Missing closing parenthesis in while
    while (a < b {
        a++;
    }
    
    // Missing opening parenthesis in if
    if a > b) {
        printf("a is greater");
    }
    
    // Missing semicolon in do-while
    do {
        b--;
    } while (b > 0)  // Missing semicolon
    
    // Missing comma in function arguments
    printf("%d %d" a b);  // Missing comma between format and arguments
    
    return 0;
}