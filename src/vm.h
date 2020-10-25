/*
*
* vm.h
* Virtual Machine
*
*/


#pragma once
#include "lex.h"
#include "stack.h"
#include "parser.h"
#include "loctab.h"


typedef struct {
	char* err;
	char_stack_t* st;
	char_stack_t* rets;
	char_loctab_t* lbls;
	char_reader_t* irdr;
	char_parser_t* p;
	char_lex_state_t* ls;
} char_vm_state_t;


char_vm_state_t* char_vm_new(void);
void char_vm_run(char_vm_state_t* vm, char* fn, char* inp);
void char_vm_close(char_vm_state_t* vm);
