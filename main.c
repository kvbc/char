#include <stdio.h>
#include "src/vm.h"
#include "src/err.h"
#include "src/char.h"


int main(int argc, char** argv) {
	puts("");
	if(argc > 1) {
		char_vm_state_t* vm = char_vm_new();
		char_vm_run(vm, argv[1], argc > 2 ? argv[2] : CHAR_DEF_INPUT);
		char_vm_close(vm);
	} else {
		printf("Usage: %s <src> [input]", argv[0]);
	}
	puts("");
}
