//wasm module - compile to .wasm
#include <stdio.h>
#include <stdint.h>

typedef void (*Tfunc)(uint32_t);

//the function you want to call indriectly form native code
void print_num(uint32_t x) {
	printf("you gave me = %d\n", x);
}

//function returning the address (pointer) to the function
Tfunc addr() {
	return print_num; //pointer to uint32_t
}

int main(void) {
	Tfunc function = addr();
	
	printf("function's address is %p\n", function);
	function(42);

	//Simulate calling via address
	Tfunc fp = addr();
	fp(123);
	
	return 0;
}

//this function return the table index of 'print_num'.
//assume its the first and only function in the table for now

//uint32_t add() {
//	return 0;
//}

//Export functions so they're visible to the host
//WASM_EXPORT("print_num") void print_num_export(uint32_t x) { print_num(x); }
