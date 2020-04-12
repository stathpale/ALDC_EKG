
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#ifndef __FIO_H__
#define __FIO_H__

typedef struct{
	FILE* in;
	FILE* out;
	char const* in_id;
	char const* out_id;
	char const* in_mode;
	char const* out_mode;
	size_t nsamples;
}f_io;



/**
 ** @name File Input and Output
 ** @{
 **/
 
/** @brief Open input and output files
 ** which are included in the typedef f_io  @a files.
 **
 ** Only use this function with a partly intialised f_io struct
 ** @a .in_id and @a .outid  aswell @a in_mode  and @a out.mode must
 ** be well defined or else the program will have undefined behavior.
 **
 ** Returns in each input and output @a .in , @a .out a valid FILE* value
 ** upon success or it exits the program upon fopen failure.
 **
 ** Each @a f_io type struct that opens with f_open must be 
 ** closed with f_close.
 **/
f_io f_open(f_io files);

void f_close(f_io files);

size_t f_get_len(FILE* fptr);

int16_t f_fetch_sample(FILE* fptr);

void buffering(FILE* fptr,size_t len, int16_t* buf);
#endif
