#include <stdio.h> 

#include <stdint.h> 

#include <stdlib.h> 

#include <string.h> 

#include "wasm_export.h" 

 

#define STACK_SIZE (64 * 1024) 

#define HEAP_SIZE  (64 * 1024) 

 

int main() { 

    const char *wasm_file = "func1.wasm"; 

 

    RuntimeInitArgs init_args; 

    memset(&init_args, 0, sizeof(RuntimeInitArgs)); 

    static char global_heap_buf[512 * 1024]; 

    init_args.mem_alloc_type = Alloc_With_Pool; 

    init_args.mem_alloc_option.pool.heap_buf = global_heap_buf; 

    init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf); 

 

    if (!wasm_runtime_full_init(&init_args)) { 

        printf("Failed to initialize WAMR runtime.\n"); 

        return 1; 

    } 

 

    // Load wasm file 

    FILE *file = fopen(wasm_file, "rb"); 

    fseek(file, 0, SEEK_END); 

    size_t file_size = ftell(file); 

    fseek(file, 0, SEEK_SET); 

    uint8_t *wasm_buf = malloc(file_size); 

    fread(wasm_buf, 1, file_size, file); 

    fclose(file); 

 

    wasm_module_t module = wasm_runtime_load(wasm_buf, file_size, NULL, 0); 

    free(wasm_buf); 

    if (!module) { 

        printf("Failed to load module.\n"); 

        return 1; 

    } 

 

    wasm_module_inst_t module_inst = wasm_runtime_instantiate(module, STACK_SIZE, HEAP_SIZE, NULL, 0); 

    if (!module_inst) { 

        printf("Failed to instantiate module.\n"); 

        return 1; 

    } 

 

    wasm_exec_env_t exec_env = wasm_runtime_create_exec_env(module_inst, STACK_SIZE); 

 

    wasm_function_inst_t addr_func = wasm_runtime_lookup_function(module_inst, "addr_export", NULL); 

    if (!addr_func) { 

        printf("addr_export not found.\n"); 

        return 1; 

    } 

 

    if (!wasm_runtime_call_wasm(exec_env, addr_func, 0, NULL)) { 

        printf("Failed to call addr_export\n"); 

        return 1; 

    } 

 

    uint32_t func_index = wasm_runtime_get_i32_return_value(exec_env); 

    printf("Function table index returned from Wasm: %u\n", func_index); 

 

    uint32_t params[2] = { 42, 0 }; 

    uint32_t paramCount = sizeof(params) / sizeof(uint32_t); 

 

    bool retval = wasm_runtime_call_indirect(exec_env, func_index, paramCount, params); 

    if (!retval) { 

        printf("Indirect call failed: %s\n", wasm_runtime_get_exception(module_inst)); 

        return 1; 

    } 

 

    wasm_runtime_destroy_exec_env(exec_env); 

    wasm_runtime_deinstantiate(module_inst); 

    wasm_runtime_unload(module); 

    wasm_runtime_destroy(); 

 

    return 0; 

} 
