#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Just include the linked list implementation
#include "symbol_table.h"

// Test configuration
#define NUM_TESTS 5

typedef struct {
    double insert_time;
    double lookup_time;
    double scope_exit_time;
} PerformanceMetrics;

// Test with linked list implementation
PerformanceMetrics test_linkedlist_implementation(int num_symbols) {
    PerformanceMetrics metrics = {0, 0, 0};
    clock_t start, end;
    
    init_symbol_table();
    
    // Test insertions
    start = clock();
    for (int i = 0; i < num_symbols; i++) {
        char name[32];
        sprintf(name, "var_%d", i);
        add_symbol(name, TYPE_INT, SCOPE_GLOBAL, i, 0);
    }
    end = clock();
    metrics.insert_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    
    // Test lookups
    start = clock();
    for (int i = 0; i < num_symbols; i++) {
        char name[32];
        sprintf(name, "var_%d", i);
        lookup_symbol(name);
    }
    end = clock();
    metrics.lookup_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    
    // Test scope management
    enter_scope();
    for (int i = 0; i < 100; i++) {
        char name[32];
        sprintf(name, "local_%d", i);
        add_symbol(name, TYPE_FLOAT, SCOPE_FUNCTION, i, 0);
    }
    
    start = clock();
    exit_scope();
    end = clock();
    metrics.scope_exit_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    
    free_symbol_table();
    
    return metrics;
}

void print_results(int num_symbols, PerformanceMetrics ll_metrics) {
    printf("\n┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│ Symbol Count: %-5d                                            │\n", num_symbols);
    printf("├─────────────────────────────────────────────────────────────────┤\n");
    printf("│ Operation        │ Linked List (ms) │                         │\n");
    printf("├──────────────────┼──────────────────┼─────────────────────────┤\n");
    printf("│ Insert           │ %15.4f  │                         │\n", ll_metrics.insert_time);
    printf("│ Lookup           │ %15.4f  │                         │\n", ll_metrics.lookup_time);
    printf("│ Scope Exit       │ %15.4f  │                         │\n", ll_metrics.scope_exit_time);
    printf("└──────────────────┴──────────────────┴─────────────────────────┘\n");
}

int main() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║  PERFORMANCE TEST: Linked List Symbol Table                  ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    int test_sizes[] = {50, 100, 250, 500, 1000};
    
    for (int i = 0; i < NUM_TESTS; i++) {
        int num_symbols = test_sizes[i];
        
        printf("\n[Test %d/%d] Testing with %d symbols...\n", i+1, NUM_TESTS, num_symbols);
        
        PerformanceMetrics ll_metrics = test_linkedlist_implementation(num_symbols);
        
        print_results(num_symbols, ll_metrics);
    }
    
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║  LINKED LIST IMPLEMENTATION CHARACTERISTICS                   ║\n");
    printf("╠═══════════════════════════════════════════════════════════════╣\n");
    printf("║  Advantages:                                                  ║\n");
    printf("║  ✓ O(1) insertion at head (constant time)                     ║\n");
    printf("║  ✓ O(1) node deletion (just update pointers)                  ║\n");
    printf("║  ✓ Dynamic memory - no fixed size limit                       ║\n");
    printf("║  ✓ Memory efficient for sparse symbol tables                  ║\n");
    printf("║                                                               ║\n");
    printf("║  Disadvantages:                                               ║\n");
    printf("║  ✗ Pointer overhead (extra memory per node)                   ║\n");
    printf("║  ✗ Cache misses due to non-sequential memory                  ║\n");
    printf("║  ✗ Memory fragmentation over time                             ║\n");
    printf("║  ✗ More complex code (pointer management)                     ║\n");
    printf("║                                                               ║\n");
    printf("║  Use Cases:                                                   ║\n");
    printf("║  • Large programs with many symbols                           ║\n");
    printf("║  • Frequent scope entry/exit                                  ║\n");
    printf("║  • Unknown symbol table size at compile time                  ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("NOTE: For comparison with array implementation, compile and run\n");
    printf("      the array-based version in the parent directory.\n");
    printf("\n");
    
    return 0;
}
