/*
*
* lex.h
* Lexical Analyzer
*
*/


#pragma once
#include "str.h"
#include "rdr.h"


typedef enum {
	TK_EOF = 256,
	TK_IDENT,
	TK_NUMBER
} char_token_type_t;


typedef struct {
	char_reader_t* rdr;
	char_str_t* tk_lexeme;
	char_token_type_t tk_type;
} char_lex_state_t;


char_lex_state_t* char_lex_new(char* src);
void char_lex_next(char_lex_state_t* ls);
void char_lex_close(char_lex_state_t* ls);