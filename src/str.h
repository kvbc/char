/*
*
* str.h
* String
*
*/


#pragma once
#include <stdint.h>


typedef struct {
	char* src;
	uint32_t len;
} char_str_t;


char_str_t* char_str_new(void);
char_str_t* char_str_set(char_str_t* str, char* src, uint32_t len);
void char_str_free(char_str_t* str);