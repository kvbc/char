/*
*
* stack.h
* Stack
*
*/


#pragma once
#include <stdint.h>


typedef struct {
	int* mem;
	uint32_t cap;
	uint32_t top;
} char_stack_t;


char_stack_t* char_stack_new(uint32_t cap);
void char_stack_push(char_stack_t* stack, int val);
int char_stack_pop(char_stack_t* stack);
int char_stack_top(char_stack_t* stack);
void char_stack_free(char_stack_t* stack);