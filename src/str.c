/*
*
* str.c
* String
*
*/


#include "str.h"
#include <stdlib.h>
#include <string.h>


char_str_t* char_str_new(void) {
	char_str_t* str = malloc(sizeof(char_str_t));
	str->len = 0;
	str->src = NULL;
	return str;
}


char_str_t* char_str_set(char_str_t* str, char* src, uint32_t len) {
	char* dest = str->src;
	if(str->len < len) {
		if(str->src)
			free(str->src);
		dest = malloc(len + 1);
	}
	str->len = len;
	str->src = memcpy(dest, src, len);
	str->src[len] = '\0';
	return str;
}


void char_str_free(char_str_t* str) {
	if(str->src)
		free(str->src);
	free(str);
}
