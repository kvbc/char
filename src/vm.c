/*
*
* vm.c
* Virtual Machine
*
*/


#include "vm.h"
#include "err.h"
#include "char.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


char_vm_state_t* char_vm_new(void) {
	char_vm_state_t* vm = (char_vm_state_t*)malloc(sizeof(char_vm_state_t));
	vm->err  = NULL;
	vm->st   = char_stack_new(CHAR_VM_STACK_SIZE);
	vm->rets = char_stack_new(CHAR_VM_RETS_SIZE);
	vm->lbls = char_loctab_new(CHAR_VM_LBLS_SIZE);
	return vm;
}


static char* char_vm_read_file(char* fn) {
	char* buff = NULL;
	FILE* f = fopen(fn, "rb");

	if(f) {
		fseek(f, 0, SEEK_END);
		uint32_t len = ftell(f);
		fseek(f, 0, SEEK_SET);
		
		buff = (char*)malloc(len + 1);
		buff[len] = '\0';
		uint32_t read_len = fread(buff, 1, len, f);

		if(len != read_len) {
			free(buff);
			buff = NULL;
			printf(CHAR_ERR_FILE_RF, fn);
		}

		fclose(f);
	}
	else printf(CHAR_ERR_FILE_NF, fn);
	return buff;
}


static CHAR_STATE char_vm_runstmt(char_vm_state_t* vm) {
	switch(vm->p->cmd) {
		case '>':
			char_stack_push(vm->st, vm->p->v.i);
			break;
		case '<':
			char_stack_pop(vm->st);
			break;
		case '+':
			char_stack_push(vm->st, char_stack_pop(vm->st) + char_stack_pop(vm->st));
			break;
		case '-': {
			int a = char_stack_pop(vm->st);
			int b = char_stack_pop(vm->st);
			char_stack_push(vm->st, b - a);
			break;
		}
		case '*':
			char_stack_push(vm->st, char_stack_pop(vm->st) * char_stack_pop(vm->st));
			break;
		case '/': {
			int a = char_stack_pop(vm->st);
			int b = char_stack_pop(vm->st);
			char_stack_push(vm->st, b / a);
			break;
		}
		case '%': {
			int a = char_stack_pop(vm->st);
			int b = char_stack_pop(vm->st);
			char_stack_push(vm->st, b % a);
			break;
		}
		case '.':
			printf("%c", char_stack_pop(vm->st));
			break;
		case ',': {
			char c = char_reader_next(vm->irdr);
			char_stack_push(vm->st, c == CHAR_READER_EOS ? '\0' : c);
			break;
		}
		case '"':
			char_stack_push(vm->st, char_stack_top(vm->st));
			break;
		case '&': {
			int a = char_stack_pop(vm->st);
			int b = char_stack_pop(vm->st);
			char_stack_push(vm->st, a);
			char_stack_push(vm->st, b);
			break;
		}
		case '~':
			char_parser_next(vm->p);
			if(char_stack_top(vm->st) < 0)
				char_vm_runstmt(vm);
			break;
		case '?':
			char_parser_next(vm->p);
			if(char_stack_top(vm->st))
				char_vm_runstmt(vm);
			break;
		case ':':
		case ';': {
			char_loc_t* lbl = char_loctab_lookup(vm->lbls, vm->p->v.s->src);
			if(!lbl) {
				char_err_rdrprint(vm->p->fn, vm->ls->rdr, vm->p->v.s->len, CHAR_ERR_LBL_UND, vm->p->v.s->src);
				return CHAR_ERROR;
			}
			if(vm->p->cmd == ';') {
				char_stack_push(vm->rets, vm->ls->rdr->cur - vm->ls->rdr->src);
				char_stack_push(vm->rets, vm->ls->rdr->col);
				char_stack_push(vm->rets, vm->ls->rdr->line);
			}
			char_reader_goto(vm->ls->rdr, lbl->idx, lbl->col, lbl->line);
			break;
		}
		case '!':
			char_reader_goto(vm->ls->rdr,
				char_stack_pop(vm->rets),
				char_stack_pop(vm->rets),
				char_stack_pop(vm->rets));
			break;
		case '^':
			break;
		case TK_EOF:
			printf("\nWarning: Unclean termination");
		case '@':
			return CHAR_ERROR;
		default:
			char_err_rdrprint(vm->p->fn, vm->ls->rdr, 1, CHAR_ERR_CHAR_UNEXP, vm->p->cmd);
			return CHAR_ERROR;
	}

	return CHAR_SUCCESS;
}


void char_vm_run(char_vm_state_t* vm, char* fn, char* inp) {
	char* src = char_vm_read_file(fn);
	if(!src) return;

	char_lex_state_t* ls = char_lex_new(src);
	do {
		char_lex_next(ls);
		if(ls->tk_type == '^') {
			char_lex_next(ls);
			if(ls->tk_type != TK_IDENT) {
				char_err_rdrprint(fn, ls->rdr, 0, CHAR_ERR_LBL_EXP);
				char_lex_close(ls);
				return;
			}
			if(char_loctab_lookup(vm->lbls, ls->tk_lexeme->src)) {
				char_err_rdrprint(fn, ls->rdr, 0, CHAR_ERR_LBL_RDEC, ls->tk_lexeme->src);
				char_lex_close(ls);
				return;
			}
			char_loctab_new_entry(vm->lbls, ls->tk_lexeme->src, ls->rdr->cur - ls->rdr->src, ls->rdr->col, ls->rdr->line);
		}
	} while(ls->tk_type != TK_EOF);
	char_lex_close(ls);

	vm->ls   = char_lex_new(src);
	vm->p    = char_parser_new(vm->ls, fn);
	vm->irdr = char_reader_new(inp);

	while(true) {
		if(!char_parser_next(vm->p)) break;
		if(!char_vm_runstmt(vm)) {
			if(vm->err)
				char_err_rdrprint(fn, vm->ls->rdr, 0, vm->err);
			break;
		}
	}

	char_lex_close(vm->ls);
	char_parser_close(vm->p);
	char_reader_close(vm->irdr);
	free(src);
}


void char_vm_close(char_vm_state_t* vm) {
	char_stack_free(vm->st);
	char_stack_free(vm->rets);
	char_loctab_free(vm->lbls);
	free(vm);
}
