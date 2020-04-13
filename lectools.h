#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/*  Temporarily, choose among the available compression tables
**  Each option corresponds to a different huffman table
*/
#define LECOPT  '1'
#define AL3OPT1 '4'
#define AL3OPT2 '5'
#define AL3OPT3 '6'
#define AL2OPT1 '4'
#define AL2OPT2 '5'

/* Unrelated with ALxOPT and LECOPT 
** Sets the unique prefix code to the compressed bit stream
** among ALEC2 and ALEC3 tables
*/
#define AL3OP1_CD 0X02U
#define AL3OP2_CD 0X03U
#define AL3OP3_CD  0X0U
#define AL3OP1_CD_LN 2U
#define AL3OP2_CD_LN 2U
#define AL3OP3_CD_LN 1U
#define AL2OP1_CD 0X01U
#define AL2OP2_CD 0X00U
#define AL2OP1_CD_LN 1U
#define AL2OP2_CD_LN 1U

/* Unrelated with ALxOPT / LECOPT 
** Sets the unique prefix code to the compressed bit stream
*/
#define ALDCOP1_CD 0X1U
#define ALDCOP2_CD 0X0U
#define ALDCOP1_CD_LN 1U
#define ALDCOP2_CD_LN 1U


/* Unrelated with ALxOPT / LECOPT 
** Sets the unique prefix code to the compressed bit stream
*/
#define ALDC_WND 40
#define ALEC_WND 10


#define BUFF_SIZE ALEC_WND
#define BCTRMX (BUFF_SIZE*32-1)

#ifndef __LECTOOLS_H__
#define __LECTOOLS_H__


typedef struct{
	uint32_t b_ctr;	
	uint32_t data[BUFF_SIZE];
}cmp_buf ;

typedef struct{
	uint32_t b_ctr;
	uint32_t data;
}t_buf;

/**
 ** @name File Input and Output
 ** @{
 **/
 

// encoding par

void aldc (FILE* fout, size_t offset, int16_t* inbuf);
void alec3(FILE* fout, size_t offset, int16_t* inbuf );
void alec2(FILE* fout, size_t offset, int16_t* inbuf );
void lec(FILE* fout, size_t offset, int16_t* inbuf );
void al3_init(bool first);
void al2_init(bool first);
void lec_init(bool first);
void encode_init(int16_t d, char const huf_opt, cmp_buf* buf);
uint16_t two2one_cmpl(int16_t dta, uint32_t dta_ordr);
void encode( cmp_buf* buf, uint32_t len, uint16_t dta);
uint32_t define_n(int16_t d);
void padding(FILE* fout, cmp_buf buf );
void f_trsmt(FILE* fout, cmp_buf buf);


#endif