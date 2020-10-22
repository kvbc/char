/*
*
* char.h
* Char core
*
*/


#pragma once
#include <stdbool.h>

#define CHAR_STATE					bool
#define CHAR_ERROR					false
#define CHAR_SUCCESS				true

#define CHAR_DEF_INPUT				""			// Default input of a program

#define CHAR_STACK_CAP_INC			50			// Capacity increase of a stack
#define CHAR_LOCTAB_CAP_INC			50			// Capacity increase of a location table

#define CHAR_VM_STACK_SIZE			100			// Default stack size for the VM
#define CHAR_VM_RETS_SIZE			50			// Default size of the stack for "returns" for the VM
#define CHAR_VM_LBLS_SIZE			50			// Default size of the location table for labels for the VM