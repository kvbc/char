/*
*
* err.h
* Error
*
*/


#pragma once
#include "rdr.h"
#include <stdint.h>


#define CHAR_ERRT_SYNTAX		"Syntax"
#define CHAR_ERRT_RUNTIME		"Runtime"

#define CHAR_ERR_CHAR_UNEXP		"Unexpected character '%c'"
#define CHAR_ERR_IDENT_UNEXP	"Unexpected identifier \"%s\""
#define CHAR_ERR_NUM_EXP		"Expected an number"
#define CHAR_ERR_NUM_UNEXP		"Unexpected number \"%s\""
#define CHAR_ERR_LBL_UND		"Undefined label"
#define CHAR_ERR_LBL_EXP		"Expected an label"
#define CHAR_ERR_LBL_RDEC		"Redeclaration of label \"%s\""
#define CHAR_ERR_FILE_RF		"Failed to read file \"%s\""
#define CHAR_ERR_FILE_NF		"File \"%s\" not found"	


void char_err_print(char* fn, uint32_t line, uint32_t col, char* frmt, ...);
void char_err_rdrprint(char* fn, char_reader_t* rdr, uint32_t offset, char* frmt, ...);
