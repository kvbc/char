/*
*
* parser.c
* Syntax Analyzer
*
*/


#include "err.h"
#include "parser.h"
#include <stdlib.h>


static CHAR_STATE char_parser_readnum(char_parser_t* p) {
	bool neg = false;
	char_lex_next(p->ls);
	if(p->ls->tk_type == '-') {
		neg = true;
		char_lex_next(p->ls);
	}
	if(p->ls->tk_type != TK_NUMBER) {
		char_err_rdrprint(p->fn, p->ls->rdr, 0, CHAR_ERR_NUM_EXP);
		return CHAR_ERROR;
	}
	int n = strtol(p->ls->tk_lexeme->src, NULL, 10);
	p->v.i = neg ? -n : n;
	return CHAR_SUCCESS;
}


char_parser_t* char_parser_new(char_lex_state_t* ls, char* fn) {
	char_parser_t* p = (char_parser_t*)malloc(sizeof(char_parser_t));
	p->ls = ls;
	p->fn = fn;
	p->cmd = 0;
	p->v.i = -1;
	p->v.s = NULL; 
	return p;
}


CHAR_STATE char_parser_next(char_parser_t* p) {
	char_lex_next(p->ls);
	p->cmd = p->ls->tk_type;

	switch(p->cmd) {
		case '>':
			if(!char_parser_readnum(p))
				return CHAR_ERROR;
			break;
		case '^':
			char_lex_next(p->ls);
			break;
		case ':':
		case ';': {
			char_lex_next(p->ls);
			if(p->ls->tk_type != TK_IDENT) {
				char_err_rdrprint(p->fn, p->ls->rdr, 0, CHAR_ERR_LBL_EXP);
				return CHAR_ERROR;
			}
			p->v.s = p->ls->tk_lexeme;
			break;
		}
		case TK_IDENT:
			char_err_rdrprint(p->fn, p->ls->rdr, p->ls->tk_lexeme->len, CHAR_ERR_IDENT_UNEXP, p->ls->tk_lexeme->src);
			return CHAR_ERROR;
		case TK_NUMBER:
			char_err_rdrprint(p->fn, p->ls->rdr, p->ls->tk_lexeme->len, CHAR_ERR_NUM_UNEXP, p->ls->tk_lexeme->src);
			return CHAR_ERROR;
	}

	return CHAR_SUCCESS;
}


void char_parser_close(char_parser_t* p) {
	free(p);
}
