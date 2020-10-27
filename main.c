#include <stdio.h>
#include <stdlib.h>
#include "src/vm.h"
#include "src/err.h"
#include "src/char.h"


static char* char_readfile(char* fn) {
	char* buff = NULL;
	FILE* f = fopen(fn, "rb");

	if(f) {
		fseek(f, 0, SEEK_END);
		uint32_t len = ftell(f);
		fseek(f, 0, SEEK_SET);
		
		buff = (char*)malloc(len + 1);
		buff[len] = '\0';
		uint32_t read_len = fread(buff, 1, len, f);

		if(len != read_len) {
			free(buff);
			buff = NULL;
			printf(CHAR_ERR_FILE_RF, fn);
		}

		fclose(f);
	}
	else printf(CHAR_ERR_FILE_NF, fn);
	return buff;
}


int main(int argc, char** argv) {
	puts("");
	if(argc > 1) {
		char* p = char_readfile(argv[1]);
		if(!p) return EXIT_FAILURE;

		char_vm_state_t* vm = char_vm_new();
		char_vm_run(vm, p, argc > 2 ? argv[2] : CHAR_DEF_INPUT);
		char_vm_close(vm);
	} else {
		printf("Usage: %s <src> [input]", argv[0]);
	}
	return EXIT_SUCCESS;
}
