/*
*
* parser.h
* Syntax Analyzer
*
*/


#pragma once
#include "lex.h"
#include "str.h"
#include "char.h"
#include <stdint.h>


typedef struct {
	union {
		int i;
		char_str_t* s;
	} v;
	char* fn;
	uint32_t cmd;
	char_lex_state_t* ls;
} char_parser_t;


char_parser_t* char_parser_new(char_lex_state_t* ls, char* fn);
CHAR_STATE char_parser_next(char_parser_t* p);
void char_parser_close(char_parser_t* p);
