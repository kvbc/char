/*
*
* lex.c
* Lexical Analyzer
*
*/


#include "lex.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


static bool char_lex_notlb(char c) {
	return c != '\r'
		&& c != '\n';
}


static bool char_lex_isdgt(char c) {
	return c >= '0' && c <= '9';
}


static bool char_lex_isident(char c) {
	return c == '_'
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9');
}


static bool char_lex_isws(char c) {
	return c==' '  || c=='\t'
		|| c=='\v' || c=='\f'
		|| c=='\n' || c=='\r';
}


static uint32_t char_lex_funclen(char* src, bool(*f)(char)) {
	char* beg = src;
	while(f(*src)) ++src;
	return src - beg;
}


static void char_lex_readstream(char_lex_state_t* ls, bool(*f)(char)) {
	char* cur = ls->rdr->cur - 1;
	uint32_t len = char_lex_funclen(cur, f);
	ls->tk_lexeme = char_str_set(ls->tk_lexeme, cur, len);
	char_reader_skip(ls->rdr, len - 1);
}


static void char_lex_skipstream(char_lex_state_t* ls, bool(*f)(char)) {
	char* cur = ls->rdr->cur - 1;
	uint32_t len = char_lex_funclen(cur, f);
	char_reader_skip(ls->rdr, len - 1);
}


static void char_lex_skipws(char_lex_state_t* ls) {
	char c;
	while(char_lex_isws(c = char_reader_next(ls->rdr)));
	if(c != CHAR_READER_EOS)
		char_reader_skip(ls->rdr, -1);
}


char_lex_state_t* char_lex_new(char* src) {
	char_lex_state_t* ls = (char_lex_state_t*)malloc(sizeof(char_lex_state_t));
	ls->rdr = char_reader_new(src);
	ls->tk_lexeme = char_str_new();
	return ls;
}


void char_lex_next(char_lex_state_t* ls) {
	char c = char_reader_next(ls->rdr);

	if(char_lex_isdgt(c)) {
		ls->tk_type = TK_NUMBER;
		char_lex_readstream(ls, char_lex_isdgt);
	}

	else if(char_lex_isident(c)) {
		ls->tk_type = TK_IDENT;
		char_lex_readstream(ls, char_lex_isident);
	}

	else if(char_lex_isws(c)) {
		char_lex_skipws(ls);
		char_lex_next(ls);
	}

	else if(c == '#') {
		char_lex_skipstream(ls, char_lex_notlb);
		char_lex_next(ls);
	}

	else if(c == CHAR_READER_EOS) {
		ls->tk_type = TK_EOF;
	}

	else ls->tk_type = c;
}


void char_lex_close(char_lex_state_t* ls) {
	char_reader_close(ls->rdr);
	char_str_free(ls->tk_lexeme);
	free(ls);
}
