#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "src/vm.h"
#include "src/err.h"
#include "src/char.h"


static char* char_read_file(char* fn) {
	char* buff = NULL;
	FILE* f = fopen(fn, "rb");

	if(f) {
		fseek(f, 0, SEEK_END);
		uint32_t len = ftell(f);
		fseek(f, 0, SEEK_SET);
		
		buff = malloc(len + 1);
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
	if(argc > 1) {
		char* p = char_read_file(argv[1]);
		if(p) {
			char* inp = argc > 2 ? argv[2] : CHAR_DEF_INPUT;
			char_vm_state_t* vm = char_vm_new();
			char_vm_run(vm, p, inp);
			char_vm_close(vm);
			free(p);
		}
	} else {
		printf("Usage: %s <src> [input]", argv[0]);
	}
}
