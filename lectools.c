/** @file lectools.c
 ** **author:** Palaiologos Efstathios  
 ** @brief Lossless entropy compression methods implementation
 **
 ** It contains the hidden implementation of the available compression methods. 
 ** 
 */

#include "lectools.h"
#include "huftbl.c"

static const uint16_t msk_tbl[12] = { [0] = 0X0001U,[1] = 0X0003U,[2] = 0X0007U,
										[3] = 0X000fU,[4] = 0X001fU,[5] = 0X003fU,
										[6] = 0X007fU,[7] = 0X00ffU,[8] = 0X01ffU,
										[9] = 0X03ffU,[10] = 0X07ffU,[11] = 0X0fffU, };



#if  defined(__ALDC_3_1__) || defined(__ALDC_3_2__) || defined(__ALEC_3__)

static cmp_buf strm3 = { .b_ctr = BCTRMX, .data = {0U}, };

#endif /*usage of 3rd internal buffer */

#if !defined(__LEC__)

static cmp_buf strm2 = { .b_ctr = BCTRMX, .data = {0U}, };

#endif  /*usage of 2nd internal buffer*/

static cmp_buf strm1={.b_ctr=BCTRMX, .data={0U},};
static t_buf tbuf = { .b_ctr = BCTRMX, .data = 0U };





void aldc (outbuf* bufout, int16_t* inbuf,size_t inbuf_len){

#if   defined(__ALDC_3_1__)

	static compressor* cmprf[] = { [0] = alec3,[1] = lec };

#elif  defined( __ALDC_2_1__)

	compressor* cmprf[] = { [0] = alec2,[1] = lec };

#elif   defined(__ALDC_3_2__)

	compressor* cmprf[] = { [0] = alec3,[1] = alec2 };

#elif defined(__ALEC_3__)

	compressor* cmprf = alec3;


#elif defined(__ALEC_2__)

	compressor* cmprf = alec2;


#elif defined(__LEC__)

	compressor* cmprf = lec;

#else

	fprintf(stderr, "ERROR COMPRESSION METHOD IS UNDIFINED \m");
	exit(EXIT_FAILURE);

#endif /*COMPRESSION METHOD*/


	if( inbuf_len%ALDC_WND)	{
		fprintf(stderr,"length of input buffer must be an integer multiple"
						"\nof the size of ALDC COMPRESSION WINDOW\n");
		exit(EXIT_FAILURE);
	}			
	if (!inbuf) {
		fprintf(stderr, "input buffer is uninitialised \n");
		exit(EXIT_FAILURE);
	}
	if (!bufout || !bufout->data) {
		fprintf(stderr, "output buffer is uninitialised \n");
		exit(EXIT_FAILURE);
	}


	for (size_t i = 0; i < inbuf_len; i += ALDC_WND) 
	{

#ifdef __ALDC__
		uint32_t buf_sum = 10 * get_buf_sum(inbuf+i);
#endif /*ALDC COMPRESSION METHOD*/

		for (size_t j = 0; j < ALDC_WND; j += ALEC_WND)
		{

#if defined(__ALDC__)
			cmprf[buf_sum <= 25 * ALDC_WND](bufout, inbuf +i + j, !j);
#else
			cmprf(bufout, inbuf + i + j, 0);
#endif /* ALDC OR ALEC FOR COMPRESSION METHOD*/

		}


	}
}


#if defined(__ALDC_3_1__) || defined(__ALDC_2_1__) || defined(__LEC__)

static void lec(outbuf* bufout, int16_t* inbuf, bool ft ){

#ifdef __LEC__

	lec_init(0);

#else

	lec_init(ft);

#endif /*ALDC OR LEC*/

	for (size_t k = 0 ; k <ALEC_WND; k++){				
		encode_init( *(inbuf+k), LECOPT, &strm1);
	}	
	f_trsmt(bufout,strm1);
}

#endif /*USAGE OF LEC*/


#if  defined(__ALDC_3_2__) || defined(__ALDC_2_1__) || defined(__ALEC_2__)

static void al2_init(bool first){
	
	for(size_t i=0;i<BUFF_SIZE-1 ;i++) {
		strm1.data[i]=0;
		strm2.data[i]=0;
	}
	strm1.data[BUFF_SIZE-1]= tbuf.data;
	strm2.data[BUFF_SIZE-1]= tbuf.data;
	strm1.b_ctr = tbuf.b_ctr;
	strm2.b_ctr = tbuf.b_ctr;


#ifdef __ALDC__

	if(first){
		encode(&strm2,ALDCOP1_CD_LN, ALDCOP1_CD);
		encode(&strm1,ALDCOP1_CD_LN, ALDCOP1_CD);
	}

#endif /*WRITE ALDC UNIQUE PREFIX CODE*/
	

	encode(&strm2,AL2OP1_CD_LN, AL2OP1_CD);
	encode(&strm1,AL2OP2_CD_LN, AL2OP2_CD);
}

static void alec2(outbuf* bufout, int16_t* inbuf, bool ft) {

#ifdef __ALEC_2__

	al2_init(0);

#else

	al2_init(ft);

#endif /*ALDC OR ALEC2 TYPE OF INIT*/


	for (size_t k = 0; k < ALEC_WND; k++) {
		encode_init(*(inbuf + k), AL2OPT1, &strm1);
		encode_init(*(inbuf + k), AL2OPT2, &strm2);
	}

	if (strm1.b_ctr >= strm2.b_ctr) {
		f_trsmt(bufout, strm1);
	}
	else {
		f_trsmt(bufout, strm2);
	}
}

#endif /*USAGE OF ALEC2*/

#if defined(__ALDC_3_2__) || defined( __ALDC_3_1__) || defined(__ALEC_3__)

static void al3_init(bool first){
	

	for(size_t i=0;i<BUFF_SIZE-1 ;i++) {
		strm1.data[i]=0;
		strm2.data[i]=0;
		strm3.data[i]=0;
	}
	strm1.data[BUFF_SIZE-1]= tbuf.data;
	strm2.data[BUFF_SIZE-1]= tbuf.data;
	strm3.data[BUFF_SIZE-1]= tbuf.data;
	strm1.b_ctr = tbuf.b_ctr;
	strm2.b_ctr = tbuf.b_ctr;
	strm3.b_ctr = tbuf.b_ctr;


#ifdef __ALDC__

	if(first){
		encode(&strm1,ALDCOP2_CD_LN, ALDCOP2_CD);
		encode(&strm2,ALDCOP2_CD_LN, ALDCOP2_CD);
		encode(&strm3,ALDCOP2_CD_LN, ALDCOP2_CD);
	}

#endif /*WRITE ALDC UNIQUE PREFIX CODE*/
	//writing their unique prefix codes	in case they are chosen as the best option
	
	//writing 10 to buffer 1
	encode(&strm1,AL3OP1_CD_LN, AL3OP1_CD);	
	
	//writing 11 to buffer 2
	encode(&strm2,AL3OP2_CD_LN, AL3OP2_CD);
	
	// 0 to buffer 3	
	encode(&strm3,AL3OP3_CD_LN, AL3OP3_CD);
}

static void alec3(outbuf* bufout, int16_t* inbuf, bool ft ){

#ifdef __ALEC_3__

	al3_init(0);

#else

	al3_init(ft);

#endif /*ALDC OR ALEC3 TYPE OF INIT*/


	for (size_t k = 0 ; k <ALEC_WND; k++){
		encode_init(*(inbuf+k), AL3OPT1, &strm1);
		encode_init(*(inbuf+k), AL3OPT2, &strm2);
		encode_init(*(inbuf+k), AL3OPT3, &strm3);
	}

	if (strm1.b_ctr >= strm2.b_ctr && strm1.b_ctr >= (strm3.b_ctr - 1))	{
		f_trsmt(bufout,strm1);
	} else if (strm2.b_ctr > strm1.b_ctr && strm2.b_ctr >= (strm3.b_ctr - 1))	{
		f_trsmt(bufout,strm2);
	} else {
		f_trsmt(bufout,strm3);
	}
}

#endif /*USAGE OF ALEC3*/

static void lec_init(bool first) {

	for (size_t i = 0; i < BUFF_SIZE - 1; i++) 
		strm1.data[i] = 0;
	strm1.data[BUFF_SIZE - 1] = tbuf.data;
	strm1.b_ctr = tbuf.b_ctr;

#ifdef __ALDC__

	if (first) {
		encode(&strm1, ALDCOP1_CD_LN, ALDCOP1_CD);
	}

#endif   /*WRITE ALDC UNIQUE PREFIX CODE*/

}

static void encode_init( int16_t di, char const huf_opt,cmp_buf* buf){

	uint32_t ni = define_n(di);
	uint16_t d=two2one_cmpl(di,ni);

	switch(huf_opt){
		case '1': 
			encode( buf, huf_tbl1_len[ni], huf_tbl1[ni]);
			break;
		case '2':
			encode( buf, huf_tbl2_len[ni], huf_tbl2[ni]);
			break;
		case '3':
			encode( buf, huf_tbl3_len[ni], huf_tbl3[ni]);
			break;
		case '4': 
			encode(  buf, huf_tbl1b_len[ni], huf_tbl1b[ni]);
			break;
		case '5':
			encode(  buf, huf_tbl2b_len[ni], huf_tbl2b[ni]);
			break;
		case '6':
			encode(  buf, huf_tbl3b_len[ni], huf_tbl3b[ni]);
			break;/**/
		default: 				
			fprintf(stderr, "INVALID COMPRESION MODE! \n");
			exit(EXIT_FAILURE);
	}
	
	if(ni)encode( buf, ni, d);
}  

static uint16_t two2one_cmpl(int16_t dta, uint32_t dta_ordr){

	if(dta<0){		
		return (uint16_t)(msk_tbl[dta_ordr-1]&(dta-1));
	} else 
		return (uint16_t)dta;
}

static void encode( cmp_buf* buf, uint32_t len, uint16_t dta){

	if (len>13){
		fprintf(stderr, "order of the difference of samples is %u and can't be compressed\n"
		"limit = 12 bits\n",len);
		exit(EXIT_FAILURE);
	}	

	if (len <= (buf->b_ctr % 32) + 1)	{
		buf->data[buf->b_ctr / 32] |= dta << ((buf->b_ctr % 32) - len + 1);
		buf->b_ctr -= len;
	}	else	{
		buf->data[buf->b_ctr / 32] |= dta >> (len - 1 - (buf->b_ctr % 32));
		uint32_t nf = (buf->b_ctr % 32) + 1;
		buf->b_ctr -= nf;

		buf->data[buf->b_ctr / 32] |= dta << ((buf->b_ctr % 32) - len + 1 + nf);
		buf->b_ctr -= (len - nf);
	}
	
}

static uint32_t define_n(int16_t d){

	uint32_t  n = 0;
	while (d !=  0)	{
		d = d / 2;
		n++;
	}
	return n;
}

static void f_trsmt(outbuf* bufout, cmp_buf buf){
		
	
	uint32_t* tbufp=&(buf.data[BUFF_SIZE-1]);
	size_t slen=(BCTRMX - buf.b_ctr) / 32;
	
	while (slen > 0){
		bufout->data[bufout->ctr++] = *tbufp;
		slen--; tbufp--; buf.b_ctr += 32;
	}
	
	tbuf.data= *tbufp ;
	tbuf.b_ctr= buf.b_ctr;
}


#ifdef __ALDC__

static uint32_t get_buf_sum(int16_t* inbuf) {

	//do it with recursion latter	
	uint32_t sum = 0U;
	for (size_t i = 0; i < ALDC_WND; i++)
		sum += abs(*(inbuf + i));

	return sum;
}

#endif /*USAGE OF PREDICTION METHOD*/

void padding(outbuf* bufout ){
	lec_init(false);
	encode(&strm1, END_TRNM_CD1_LEN, END_TRNM_CD1);
	encode(&strm1, END_TRNM_CD2_LEN, END_TRNM_CD2);

	bufout->data[bufout->ctr++] = strm1.data[BUFF_SIZE - 1];
	if( (strm1.b_ctr) < (BCTRMX -32) ) 		
		bufout->data[bufout->ctr++] = strm1.data[BUFF_SIZE - 2];	
}


void cmp_buf_init(void) {

	tbuf.b_ctr = BCTRMX;
	tbuf.data = 0U;
	strm1.b_ctr = BCTRMX;


#if  !defined(__LEC__)

	strm2.b_ctr = BCTRMX;

#endif /*USAGE OF 2ND INTERNAL BUFFER*/


#if  defined(__ALDC_3_1__) || defined(__ALDC_3_2__) || defined(__ALEC_3__)

	strm3.b_ctr = BCTRMX;

#endif /*USAGE OF 3RD INTERNAL BUFFER*/

	for (size_t i = 0; i < BUFF_SIZE; ++i) {
		strm1.data[i] = 0U;


#if  !defined(__LEC__)

		strm2.data[i] = 0U;

#endif /*USAGE OF 2ND INTERNAL BUFFER*/


#if  defined(__ALDC_3_1__) || defined(__ALDC_3_2__) || defined(__ALEC_3__)
		strm3.data[i] = 0U;
#endif  /*USAGE OF 3RD INTERNAL BUFFER*/

	}
}