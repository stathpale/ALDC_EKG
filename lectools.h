#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "fio.h"
#define BUFF_SIZE 2
#define ALDC_WND 40
#define ALEC_WND 10

#ifndef __LECTOOLS_H__
#define __LECTOOLS_H__


typedef struct{
	uint32_t b_ctr;	
	uint32_t data[BUFF_SIZE];	
	uint32_t const b_max;
	uint32_t const word32size;
}cmp_buf ;

/**
 ** @name File Input and Output
 ** @{
 **/
 

// encoding par
void alec3(FILE* fout, char const huf_opt,
		size_t n_samples, cmp_buf* buf, int16_t* inbuf );

void lec(FILE* fout, char const huf_opt,
		size_t n_samples, cmp_buf* buf, int16_t* inbuf );
void encode_init(int16_t d, char const huf_opt, cmp_buf* buf);
uint16_t two2one_cmpl(int16_t dta, uint32_t dta_ordr);
void encode( cmp_buf* buf, uint32_t len, uint16_t dta);
uint32_t define_n(int16_t d);
void padding(FILE* fout, cmp_buf* buf );
void f_write(FILE* fout, cmp_buf* buf);

#endif