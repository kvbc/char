/*
*
* err.c
* Error
*
*/


#include "err.h"
#include <stdio.h>
#include <stdarg.h>


static void char_err_vprint(char* fn, uint32_t line, uint32_t col, char* frmt, va_list* args) {
	printf("%s:%d:%d: ", fn, line, col);
	vprintf(frmt, *args);
	va_end(*args);
}


void char_err_print(char* fn, uint32_t line, uint32_t col, char* frmt, ...) {
	va_list args;
	va_start(args, frmt);
	char_err_vprint(fn, line, col, frmt, &args);
}


void char_err_rdrprint(char* fn, char_reader_t* rdr, uint32_t offset, char* frmt, ...) {
	va_list args;
	va_start(args, frmt);
	char_err_vprint(fn, rdr->line, rdr->col - offset, frmt, &args);
}
