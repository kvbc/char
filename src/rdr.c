/*
*
* rdr.c
* Reader
*
*/


#include "rdr.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


static bool char_reader_islb(char c) {
	return c == '\n'
		|| c == '\r';
}


char_reader_t* char_reader_new(char* src) {
	char_reader_t* rdr = malloc(sizeof(char_reader_t));
	rdr->src = src;
	rdr->cur = src;
	rdr->end = src + strlen(src);
	rdr->col = 1;
	rdr->line = 1;
	return rdr;
}


char char_reader_next(char_reader_t* rdr) {
	if(rdr->cur < rdr->end) {
		char c = *rdr->cur++;
		if(char_reader_islb(c)) {
			if(*rdr->cur != c && char_reader_islb(*rdr->cur)) ++rdr->cur;
			++rdr->line;
			rdr->col = 1;
		}
		else ++rdr->col;
		return c;
	}
	return CHAR_READER_EOS;
}


void char_reader_skip(char_reader_t* rdr, int chars) {
	rdr->cur += chars;
	rdr->col += chars;
}


void char_reader_goto(char_reader_t* rdr, uint32_t idx, uint32_t col, uint32_t line) {
	rdr->cur = rdr->src + idx;
	rdr->col = col;
	rdr->line = line;
}


void char_reader_close(char_reader_t* rdr) {
	free(rdr);
}