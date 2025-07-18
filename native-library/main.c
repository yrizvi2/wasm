#include <stdio.h>
__attribute__((import_module("env"), import_name("print_42"))) 

extern int print_42(void); 

 

int main(void) { 
	printf("Hello!\n");
	int x = print_42();
    return 0; 
}
