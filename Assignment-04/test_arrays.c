// Test file for array type checking
// Assignment-04: Array declarations and type checking

int main() {
    int arr[10];
    float farr[5];
    int i, value;
    float fval;
    
    // Valid: array subscript with integer
    arr[0] = 100;
    arr[i] = 200;
    
    // Valid: reading from array
    value = arr[0];
    
    // Valid: float array
    farr[0] = 3.14;
    fval = farr[0];
    
    // Type Error: assigning float array to int variable
    value = farr[0];
    
    // Type Error: using integer as pointer (array subscript on non-array)
    value[0] = 10;
    
    return 0;
}
