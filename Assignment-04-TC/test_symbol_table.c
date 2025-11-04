// Test program to verify symbol table implementation
int global_x;
int global_y;
float global_f;

int main() {
    int local_a;
    int local_b;
    float local_c;
    
    local_a = 10;
    local_b = 20;
    local_c = 3.14;
    
    {
        int block_x;
        int block_y;
        block_x = 5;
        block_y = 10;
    }
    
    return 0;
}

int calculate(int x, int y) {
    int result;
    result = x + y;
    return result;
}
