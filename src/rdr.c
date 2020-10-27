/*
*
* rdr.h
* Reader
*
*/


#pragma once
#include <stdint.h>
#define CHAR_READER_EOS -1


typedef struct {
	char* src;
	char* cur;
	char* end;
	uint32_t col;
	uint32_t line;
} char_reader_t;


char_reader_t* char_reader_new(char* src);
char char_reader_next(char_reader_t* rdr);
void char_reader_skip(char_reader_t* rdr, int chars);
void char_reader_goto(char_reader_t* rdr, uint32_t idx, uint32_t col, uint32_t line);
void char_reader_close(char_reader_t* rdr);
