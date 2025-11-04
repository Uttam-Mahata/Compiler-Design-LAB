// Test file for pointer and memory errors
// Assignment-04: Detecting illegal pointer operations

int main() {
    int a, b;
    int arr[10];
    
    a = 10;
    b = 20;
    
    // Valid: array access
    arr[0] = 100;
    arr[1] = 200;
    
    // Type Error: attempting to use integer as pointer
    // Trying to subscript a non-array/non-pointer variable
    a[0] = 50;
    
    // Type Error: attempting to use integer as pointer
    b[5] = 100;
    
    // Valid: normal integer operations
    a = b + 10;
    
    return 0;
}
