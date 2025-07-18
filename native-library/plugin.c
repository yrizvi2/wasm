//native code to compile into .so
#include <stdio.h> 

#include <stddef.h> 

#include <stdint.h>

#include "wasm_export.h" 

 

int print_42(wasm_exec_env_t exec_env) { 

    printf("Native plugin says: 42\n"); 

    return 42; 

} 

 

uint32_t get_native_lib(char** ModuleName, NativeSymbol **symbol_list) { 

    static NativeSymbol symbols[] = { 

        { "print_42", print_42, "()i", NULL } 

    }; 
	*ModuleName = "env";
    *symbol_list = symbols; 

    return sizeof(symbols) / sizeof(NativeSymbol); 

} 
