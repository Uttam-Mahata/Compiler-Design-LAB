// Test file for nested scopes - levels 0, 1, 2
// Tests proper scope level transitions

int global_var;         // Level 0: Global scope
float global_float;     // Level 0: Global scope

int function1(int param1, int param2) {  // function1: Level 0, params: Level 1
    int local_var1;     // Level 1: Function scope
    int local_var2;     // Level 1: Function scope

    local_var1 = param1 + param2;

    // Nested block - should be Level 2
    {
        int block_var1;  // Level 2: Block scope
        int block_var2;  // Level 2: Block scope

        block_var1 = 10;
        block_var2 = 20;
        local_var2 = block_var1 + block_var2;
    }

    // Another nested block - should be Level 2
    {
        float block_float;  // Level 2: Block scope
        int block_int;      // Level 2: Block scope

        block_float = 3.14;
        block_int = 100;
    }

    return local_var1 + local_var2;
}

int main() {  // main: Level 0
    int main_local1;  // Level 1: Function scope
    int main_local2;  // Level 1: Function scope

    main_local1 = 5;
    main_local2 = 10;

    // Nested block in main - should be Level 2
    {
        int inner1;  // Level 2: Block scope
        int inner2;  // Level 2: Block scope

        inner1 = 1;
        inner2 = 2;

        // Double nested block - should be Level 3
        {
            int deep1;  // Level 3: Deeply nested scope
            int deep2;  // Level 3: Deeply nested scope

            deep1 = inner1 + inner2;
            deep2 = deep1 * 2;
        }

        main_local1 = inner1 + inner2;
    }

    // Another Level 2 block
    {
        float another_block;  // Level 2: Block scope
        another_block = 99.9;
    }

    return 0;
}
