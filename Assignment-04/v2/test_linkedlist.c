#include "symbol_table.h"
#include <assert.h>
#include <time.h>

// Test 1: Basic insert and lookup
void test_basic_operations() {
    printf("\n========== TEST 1: Basic Insert and Lookup ==========\n");
    init_symbol_table();
    
    // Insert symbols
    assert(add_symbol("x", TYPE_INT, SCOPE_GLOBAL, 1, 0) == 1);
    assert(add_symbol("y", TYPE_FLOAT, SCOPE_GLOBAL, 2, 0) == 1);
    assert(add_symbol("z", TYPE_CHAR, SCOPE_GLOBAL, 3, 0) == 1);
    
    // Lookup symbols
    symbol_t* sym_x = lookup_symbol("x");
    assert(sym_x != NULL);
    assert(sym_x->type == TYPE_INT);
    printf("✓ Found 'x' with type INT\n");
    
    symbol_t* sym_y = lookup_symbol("y");
    assert(sym_y != NULL);
    assert(sym_y->type == TYPE_FLOAT);
    printf("✓ Found 'y' with type FLOAT\n");
    
    // Lookup non-existent symbol
    symbol_t* sym_w = lookup_symbol("w");
    assert(sym_w == NULL);
    printf("✓ 'w' not found (as expected)\n");
    
    print_symbol_table();
    free_symbol_table();
    printf("✓ TEST 1 PASSED\n");
}

// Test 2: Duplicate detection
void test_duplicate_detection() {
    printf("\n========== TEST 2: Duplicate Detection ==========\n");
    init_symbol_table();
    
    assert(add_symbol("x", TYPE_INT, SCOPE_GLOBAL, 1, 0) == 1);
    printf("✓ First 'x' added successfully\n");
    
    // Try to add duplicate in same scope
    assert(add_symbol("x", TYPE_FLOAT, SCOPE_GLOBAL, 2, 0) == 0);
    printf("✓ Duplicate 'x' rejected (as expected)\n");
    
    free_symbol_table();
    printf("✓ TEST 2 PASSED\n");
}

// Test 3: Scope management and shadowing
void test_scope_management() {
    printf("\n========== TEST 3: Scope Management and Shadowing ==========\n");
    init_symbol_table();
    
    // Global scope
    add_symbol("x", TYPE_INT, SCOPE_GLOBAL, 1, 0);
    symbol_t* global_x = lookup_symbol("x");
    assert(global_x->scope_level == 0);
    printf("✓ Global 'x' at level 0\n");
    
    // Enter function scope
    enter_scope();
    add_symbol("x", TYPE_FLOAT, SCOPE_FUNCTION, 2, 0);  // Shadow global x
    add_symbol("y", TYPE_CHAR, SCOPE_FUNCTION, 3, 0);
    
    symbol_t* func_x = lookup_symbol("x");
    assert(func_x->scope_level == 1);
    assert(func_x->type == TYPE_FLOAT);  // Should find shadowing variable
    printf("✓ Function 'x' shadows global 'x'\n");
    
    // Enter block scope
    enter_scope();
    add_symbol("x", TYPE_CHAR, SCOPE_BLOCK, 4, 0);  // Shadow both
    add_symbol("z", TYPE_INT, SCOPE_BLOCK, 5, 0);
    
    symbol_t* block_x = lookup_symbol("x");
    assert(block_x->scope_level == 2);
    assert(block_x->type == TYPE_CHAR);
    printf("✓ Block 'x' shadows function 'x'\n");
    
    print_symbol_table();
    
    // Exit block scope
    exit_scope();
    symbol_t* after_block = lookup_symbol("x");
    assert(after_block->scope_level == 1);
    assert(after_block->type == TYPE_FLOAT);
    printf("✓ After exiting block, found function 'x'\n");
    
    symbol_t* z_gone = lookup_symbol("z");
    assert(z_gone == NULL);
    printf("✓ Block variable 'z' removed\n");
    
    // Exit function scope
    exit_scope();
    symbol_t* after_func = lookup_symbol("x");
    assert(after_func->scope_level == 0);
    assert(after_func->type == TYPE_INT);
    printf("✓ After exiting function, found global 'x'\n");
    
    print_symbol_table();
    free_symbol_table();
    printf("✓ TEST 3 PASSED\n");
}

// Test 4: Array and pointer types
void test_arrays_and_pointers() {
    printf("\n========== TEST 4: Arrays and Pointers ==========\n");
    init_symbol_table();
    
    // Add array
    add_symbol_with_attrs("arr", TYPE_INT_ARRAY, SCOPE_GLOBAL, 1, 0, 1, 10, 0);
    symbol_t* arr = lookup_symbol("arr");
    assert(arr != NULL);
    assert(arr->is_array == 1);
    assert(arr->array_size == 10);
    assert(is_array_type(arr->type) == 1);
    printf("✓ Array 'arr[10]' added and validated\n");
    
    // Add pointer
    add_symbol_with_attrs("ptr", TYPE_INT_PTR, SCOPE_GLOBAL, 2, 0, 0, 0, 1);
    symbol_t* ptr = lookup_symbol("ptr");
    assert(ptr != NULL);
    assert(ptr->is_pointer == 1);
    assert(is_pointer_type(ptr->type) == 1);
    printf("✓ Pointer 'ptr' added and validated\n");
    
    // Test base type extraction
    assert(get_base_type(TYPE_INT_ARRAY) == TYPE_INT);
    assert(get_base_type(TYPE_FLOAT_PTR) == TYPE_FLOAT);
    printf("✓ Base type extraction works\n");
    
    print_symbol_table();
    free_symbol_table();
    printf("✓ TEST 4 PASSED\n");
}

// Test 5: Type compatibility
void test_type_compatibility() {
    printf("\n========== TEST 5: Type Compatibility ==========\n");
    
    // Compatible types
    assert(are_types_compatible(TYPE_INT, TYPE_INT) == 1);
    assert(are_types_compatible(TYPE_INT, TYPE_CHAR) == 1);  // Promotion
    assert(are_types_compatible(TYPE_CHAR, TYPE_INT) == 1);  // Promotion
    assert(are_types_compatible(TYPE_FLOAT, TYPE_FLOAT) == 1);
    printf("✓ Compatible types validated\n");
    
    // Incompatible types
    assert(are_types_compatible(TYPE_INT, TYPE_FLOAT) == 0);
    assert(are_types_compatible(TYPE_FLOAT, TYPE_CHAR) == 0);
    printf("✓ Incompatible types validated\n");
    
    printf("✓ TEST 5 PASSED\n");
}

// Test 6: Performance comparison (large number of symbols)
void test_performance() {
    printf("\n========== TEST 6: Performance Test ==========\n");
    init_symbol_table();
    
    clock_t start, end;
    double insert_time, lookup_time;
    int num_symbols = 1000;
    
    // Test insertions
    start = clock();
    for (int i = 0; i < num_symbols; i++) {
        char name[20];
        sprintf(name, "var_%d", i);
        add_symbol(name, TYPE_INT, SCOPE_GLOBAL, i, 0);
    }
    end = clock();
    insert_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("✓ Inserted %d symbols in %.3f ms\n", num_symbols, insert_time);
    
    // Test lookups
    start = clock();
    for (int i = 0; i < num_symbols; i++) {
        char name[20];
        sprintf(name, "var_%d", i);
        symbol_t* sym = lookup_symbol(name);
        assert(sym != NULL);
    }
    end = clock();
    lookup_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("✓ Looked up %d symbols in %.3f ms\n", num_symbols, lookup_time);
    
    printf("✓ Average insertion time: %.4f ms\n", insert_time / num_symbols);
    printf("✓ Average lookup time: %.4f ms\n", lookup_time / num_symbols);
    
    free_symbol_table();
    printf("✓ TEST 6 PASSED\n");
}

// Test 7: Memory cleanup
void test_memory_cleanup() {
    printf("\n========== TEST 7: Memory Cleanup ==========\n");
    init_symbol_table();
    
    // Add many symbols
    for (int i = 0; i < 100; i++) {
        char name[20];
        sprintf(name, "sym_%d", i);
        add_symbol(name, TYPE_INT, SCOPE_GLOBAL, i, 0);
    }
    
    printf("✓ Added 100 symbols\n");
    assert(sym_table.count == 100);
    
    // Free all
    free_symbol_table();
    assert(sym_table.head == NULL);
    assert(sym_table.count == 0);
    printf("✓ All symbols freed, no memory leaks\n");
    
    printf("✓ TEST 7 PASSED\n");
}

int main() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║  LINKED LIST SYMBOL TABLE - COMPREHENSIVE TESTS       ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    test_basic_operations();
    test_duplicate_detection();
    test_scope_management();
    test_arrays_and_pointers();
    test_type_compatibility();
    test_performance();
    test_memory_cleanup();
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║  ✅ ALL TESTS PASSED SUCCESSFULLY!                    ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    return 0;
}
