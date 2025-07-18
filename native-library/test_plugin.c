//wasm module
__attribute__((import_module("env"), import_name("print_42"))) 

extern int print_42(void); 

 

__attribute__((export_name("run"))) 

int run(void) { 

    return print_42(); 
}
