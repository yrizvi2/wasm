#include <stdint.h> 
#include <stdio.h> 

#define WASM_EXPORT(name) __attribute__((used)) __attribute__((export_name(name))) 

typedef void (*Tfunc)(uint32_t); 
// Called from host via indirect call 

void print_num(uint32_t x) { 
    printf("you gave me = %d\n", x); 
} 

// Export the function so it's added to the function table 

WASM_EXPORT("print_num_export") 
void print_num_export(uint32_t x) { 
	Tfunc fn = print_num;
    fn(x); 
} 

// Manually return the index into the table with wasm-objdump

WASM_EXPORT("addr_export") 
uint32_t addr_export() { 
    return 10;
} 
