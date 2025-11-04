// Test case 2: Main function with conditional and iterative statements
int main() {
    int i, n, sum;
    
    n = 10;
    sum = 0;
    
    // For loop
    for(i = 1; i <= n; i++) {
        sum = sum + i;
    }
    
    // If-else statement
    if(sum > 50) {
        sum = sum * 2;
    } else {
        sum = sum + 1;
    }
    
    // While loop
    while(sum > 0) {
        sum = sum - 1;
    }
    
    return sum;
}