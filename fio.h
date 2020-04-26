/** @file fio.h
 ** **author:** Palaiologos Efstathios
 ** @brief File input and output Interface
 **
 ** This module provides an opaque interface for opening, loading and closing of continous time recrodings.
 ** It also provides an opaque interface for creating new files.
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#ifndef __FIO_H__

#define __FIO_H__       ///< guard

/** @brief f_io is a struct typedef that gathers all the FILE type associated parameteters  
 **
 **
 */

typedef struct{
	FILE* in;           ///< pointer to an input recording
	FILE* out;          ///< pointer to a compressed recording
	char const* in_id;  ///< input file id
	char const* out_id; ///< ouput file 
	size_t nsamples;    ///< number of the 16-bit samples of the recording
}f_io;


 
/** @brief Opens input and output files
 ** which are included in the typedef f_io  @a files.   
 **
 ** 
 ** Each @a f_io type struct that opens with f_open must be 
 ** closed with f_close.
 ** @param[in] files  @a .in_id and @a .out_id  must be defined prior to the invocation 
 ** of this function or else the program will have undefined behavior.
 **
 ** @param[in] difbuf_adr is the address of an int16_t* null pointer, 
 **
 ** @param[out] files.in a valid FILE* pointer at the input file 
 **
 ** @param[out] files.out a valid FILE* pointer at an empty new file
 **
 ** @param[out] files.nsamples The number of 16-bits samples in the input recording file
 **
 ** @param[out] difbuf_adr the address of the allocated memory for the input buffer, filled with
 ** the differences of all the sequential pairs of samples.
 **
 **
 */
f_io f_open(f_io files,int16_t** difbuf_adr);

/**This function must be called for every files struct that opens with f_open*/
void f_close(f_io files);


#endif
