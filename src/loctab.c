/*
*
* loctab.c
* Location Table
*
*/


#include "char.h"
#include "loctab.h"
#include <string.h>
#include <stdlib.h>


char_loctab_t* char_loctab_new(uint32_t cap) {
	char_loctab_t* lt = (char_loctab_t*)malloc(sizeof(char_loctab_t));
	lt->top = 0;
	lt->cap = cap;
	lt->mem = (char_loc_t*)malloc(sizeof(char_loc_t) * cap);
	return lt;
}


void char_loctab_new_entry(char_loctab_t* lt, char* id, uint32_t idx, uint32_t col, uint32_t line) {
	if(lt->top == lt->cap)
		lt->mem = realloc(lt->mem, sizeof(char_loc_t) * (lt->cap += CHAR_LOCTAB_CAP_INC));
	char_loc_t l;
	l.idx = idx;
	l.col = col;
	l.line = line;
	l.id = char_str_set(char_str_new(), id, strlen(id));
	lt->mem[lt->top++] = l;
}


char_loc_t* char_loctab_lookup(char_loctab_t* lt, char* id) {
	for(uint32_t i = 0; i < lt->top; ++i)
		if(strcmp(lt->mem[i].id->src, id) == 0)
			return &lt->mem[i];
	return NULL;
}


void char_loctab_free(char_loctab_t* lt) {
	for(uint32_t i = 0; i < lt->top; ++i)
		char_str_free(lt->mem[i].id);
	free(lt->mem);
	free(lt);
}
