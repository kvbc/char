/*
*
* stack.c
* Stack
*
*/


#include "char.h"
#include "stack.h"
#include <stdlib.h>


char_stack_t* char_stack_new(uint32_t cap) {
	char_stack_t* stack = malloc(sizeof(char_stack_t));
	stack->cap = cap;
	stack->top = 0;
	stack->mem = malloc(sizeof(int) * cap);
	return stack;
}


void char_stack_push(char_stack_t* stack, int val) {
	if(stack->top == stack->cap)
		stack->mem = realloc(stack->mem, sizeof(int) * (stack->cap += CHAR_STACK_CAP_INC));
	stack->mem[stack->top++] = val;
}


int char_stack_pop(char_stack_t* stack) {
	if(stack->top == 0)
		return NULL;
	return stack->mem[--stack->top];
}


int char_stack_top(char_stack_t* stack) {
	if(stack->top == 0)
		return NULL;
	return stack->mem[stack->top - 1];
}


void char_stack_free(char_stack_t* stack) {
	free(stack->mem);
	free(stack);
}