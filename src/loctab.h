/*
*
* loctab.h
* Location Table
*
*/


#pragma once
#include "str.h"
#include <stdint.h>


typedef struct {
	uint32_t idx;
	uint32_t col;
	uint32_t line;
	char_str_t* id;
} char_loc_t;


typedef struct {
	uint32_t cur;
	uint32_t cap;
	char_loc_t* mem;
} char_loctab_t;


char_loctab_t* char_loctab_new(uint32_t cap);
void char_loctab_new_entry(char_loctab_t* lt, char* id, uint32_t idx, uint32_t col, uint32_t line);
char_loc_t* char_loctab_lookup(char_loctab_t* lt, char* id);
void char_loctab_free(char_loctab_t* lt);