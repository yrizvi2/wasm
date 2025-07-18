#include <stdint.h>
#include <stdio.h>

#define WASM_EXPORT(name) __attribute__((used)) __attribute__((export_name(name)))
typedef void (*TFunc)(uint32_t);
extern void *__funcref_table __attribute__((import_module("env"))) __attribute__((import_name("table")));

void print_num(uint32_t x) {
    printf("you gave me = %d\n", x);
}

// Exported wrapper for linking/exporting function
WASM_EXPORT("print_num")
void print_num_export(uint32_t x) {
    print_num(x);
}

// Set up function table
WASM_EXPORT("setup_table")
void setup_table() {
    if (__builtin_wasm_table_size(__funcref_table) == 0) {
        __builtin_wasm_table_grow(__funcref_table, (void *)print_num_export, 1);
    } else {
        __builtin_wasm_table_set(__funcref_tabl, 0, (void *)print_num_export);
    }
}

// Return the index 0 where function was stored
WASM_EXPORT("addr")
uint32_t addr() {
    return 0;
}
