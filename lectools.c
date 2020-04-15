#include "lectools.h"
#include "huftbl.c"

/**/

static t_buf tbuf={.b_ctr=BCTRMX, .data=0U};
static cmp_buf strm1={.b_ctr=BCTRMX, .data={0U},};
static cmp_buf strm2={.b_ctr=BCTRMX, .data={0U},};
static cmp_buf strm3={.b_ctr=BCTRMX, .data={0U},};


void lec_init(bool first){
	
		for(size_t i=0;i<BUFF_SIZE-1 ;i++) strm1.data[i]=0;
		strm1.data[BUFF_SIZE-1]= tbuf.data;
		strm1.b_ctr = tbuf.b_ctr;
	if(first){
		encode(&strm1,ALDCOP1_CD_LN, ALDCOP1_CD);
	} 
}

void al2_init(bool first){
	
		for(size_t i=0;i<BUFF_SIZE-1 ;i++) {
			strm1.data[i]=0;
			strm2.data[i]=0;
		}
		strm1.data[BUFF_SIZE-1]= tbuf.data;
		strm2.data[BUFF_SIZE-1]= tbuf.data;
		strm1.b_ctr = tbuf.b_ctr;
		strm2.b_ctr = tbuf.b_ctr;
	if(first){
		encode(&strm2,ALDCOP1_CD_LN, ALDCOP1_CD);
		encode(&strm1,ALDCOP1_CD_LN, ALDCOP1_CD);
	}

	
	encode(&strm2,AL2OP1_CD_LN, AL2OP1_CD);

	encode(&strm1,AL2OP2_CD_LN, AL2OP2_CD);
}

void al3_init(bool first){
	

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
	
	if(first){
		encode(&strm1,ALDCOP2_CD_LN, ALDCOP2_CD);
		encode(&strm2,ALDCOP2_CD_LN, ALDCOP2_CD);
		encode(&strm3,ALDCOP2_CD_LN, ALDCOP2_CD);


	}

	//writing their unique prefix codes	in case they are chosen as the best option
	
	//writing 10 to buffer 1
	encode(&strm1,AL3OP1_CD_LN, AL3OP1_CD);	
	
	//writing 11 to buffer 2
	encode(&strm2,AL3OP2_CD_LN, AL3OP2_CD);
	
	// 0 to buffer 3	
	encode(&strm3,AL3OP3_CD_LN, AL3OP3_CD);
}

void aldc (FILE* fout, int16_t* inbuf){
	compressor* cmprf[]={[0]=alec3, [1]=lec};
	uint32_t buf_sum = 10*get_buf_sum(inbuf);
	
	for(size_t j = 0 ; j< ALDC_WND ; j+=ALEC_WND){
		
		cmprf[buf_sum <= 25*ALDC_WND](fout, inbuf+j,!j);

	}
		
	
}

void alec3(FILE* fout, int16_t* inbuf, bool ft ){	
	al3_init(ft);
	for (size_t k = 0 ; k <ALEC_WND; k++){
		encode_init(*(inbuf+k), AL3OPT1, &strm1);
		encode_init(*(inbuf+k), AL3OPT2, &strm2);
		encode_init(*(inbuf+k), AL3OPT3, &strm3);
	}
	if (strm1.b_ctr >= strm2.b_ctr && strm1.b_ctr >= (strm3.b_ctr - 1))	{
		f_trsmt(fout,strm1);
	} else if (strm2.b_ctr > strm1.b_ctr && strm2.b_ctr >= (strm3.b_ctr - 1))	{
		f_trsmt(fout,strm2);
	} else {
		f_trsmt(fout,strm3);
	}
}

void alec2(FILE* fout, int16_t* inbuf,bool ft ){	
	al2_init(ft);
	for (size_t k = 0 ; k <ALEC_WND; k++){ 			
		encode_init(*(inbuf+k), AL2OPT1, &strm1);
		encode_init(*(inbuf+k), AL2OPT2, &strm2);
	}	
	if (strm1.b_ctr >= strm2.b_ctr ){
		f_trsmt(fout,strm1);
	} else {
		f_trsmt(fout,strm2);
	}	
}

void lec(FILE* fout, int16_t* inbuf, bool ft ){	
	lec_init(ft);
	for (size_t k = 0 ; k <ALEC_WND; k++){				
		encode_init( *(inbuf+k), LECOPT, &strm1);
	}	
	f_trsmt(fout,strm1);
}

void encode_init( int16_t di, char const huf_opt,cmp_buf* buf){
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

uint16_t two2one_cmpl(int16_t dta, uint32_t dta_ordr){
	if(dta<0){		
		return (uint16_t)(msk_tbl[dta_ordr-1]&(dta-1));
	}else 
		return (uint16_t)dta;
}

void encode( cmp_buf* buf, uint32_t len, uint16_t dta){	
	if (len>=13){
			fprintf(stderr, "order of the sample is %u and can't be compressed\n"
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

uint32_t define_n(int16_t d){
	uint32_t  n = 0;
	while (d !=  0)	{
		d = d / 2;
		n++;
	}
	return n;
}

void f_trsmt(FILE* fout, cmp_buf buf){
		
	
	uint32_t* tbufp=&(buf.data[BUFF_SIZE-1]);
	size_t slen=(BCTRMX - buf.b_ctr) / 32;
	
	while (slen > 0){		
		fwrite( tbufp,sizeof(uint32_t),1,fout);
		slen--; tbufp--; buf.b_ctr += 32;
	}
	
	tbuf.data= *tbufp ;
	tbuf.b_ctr= buf.b_ctr;
}

uint32_t get_buf_sum(int16_t* inbuf) {
	//do it with recursion latter	
	uint32_t sum = 0U;
	for (size_t i = 0; i < ALDC_WND; i++)
		sum += abs(*(inbuf + i));

	return sum;
}


/* padding function
void padding(FILE* fout, cmp_buf* buf ){
	encode( buf, 4U, 0X000FU);
	encode( buf, 8U, 0X00FFU);
	fwrite( &buf->data[1],sizeof(uint32_t),1,fout);	
		//buf->b_ctr-=32;
	if( (buf->b_ctr) < (buf->b_max-32) )		
	if( (buf->b_ctr) < BCTRMX-32 )		
		if(!fwrite( &buf->data[0],sizeof(uint32_t),1,fout)){
			fprintf(stderr, "could not write to file \n");
			exit(EXIT_FAILURE);
		}
	
}*/
