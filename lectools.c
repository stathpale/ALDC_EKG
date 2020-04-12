#include "lectools.h"
#include "huftbl.c"

/**/

static int16_t r[2]={0};			
static t_buf tbuf={.b_ctr=BCTRMX, .data=0};


void lec(FILE* fout, char const huf_opt,
		 size_t offset,cmp_buf* buf, int16_t* inbuf ){
			 
	for(size_t i=0;i<BUFF_SIZE ;i++) buf->data[i]=0;
	buf->data[BUFF_SIZE-1]= tbuf.data;
	buf->b_ctr = tbuf.b_ctr;
	
	for (size_t k = 0 ; k <ALEC_WND; k++){
		r[1] = *(inbuf+k+offset);  			
		encode_init(r[1]-r[0], huf_opt, buf);
		r[0] = r[1];
		//printf("inside lec %zu , %zu\n",k+offset,k);
	}
	//for(size_t i=BUFF_SIZE-1 ;i ;i--)
	//	printf("%#x buf->data[i];
	//	printf("
	f_trnmt(fout,buf);

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
			encode( buf, huf_tbl1b_len[ni], huf_tbl1b[ni]);
			break;
		case '5':
			encode( buf, huf_tbl2b_len[ni], huf_tbl2b[ni]);
			break;
		case '6':
			encode( buf, huf_tbl3b_len[ni], huf_tbl3b[ni]);
			break;
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
			"12 bits = limit\n",len);
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

void f_trnmt(FILE* fout, cmp_buf* buf){
	uint32_t* tbufp=&(buf->data[BUFF_SIZE-1]);

	size_t slen=(BCTRMX - buf->b_ctr) / 32;
	if ((BCTRMX - buf->b_ctr) % 32 > 0) 
		slen++;
	
	while (slen > 1)
	{
		
		//printf("%#X %#X %u \n" , *tbufp , buf->data[BUFF_SIZE-1],buf->b_ctr);
		fwrite( tbufp,sizeof(uint32_t),1,fout);
		slen--; tbufp--; buf->b_ctr += 32;
	}
	

	tbuf.data= *tbufp ;
	tbuf.b_ctr= buf->b_ctr;
	/*
	if(buf->b_ctr< BCTRMX-32){		
		uint32_t temp=buf->data[BCTRMX/32];
		if(!fwrite( &temp,sizeof(uint32_t),1,fout)){
			fprintf(stderr, "could not write to file \n");
			exit(EXIT_FAILURE);
		}
		buf->data[BUFF_SIZE-1]=buf->data[BUFF_SIZE-2];
		buf->data[BUFF_SIZE-2]=0;
		buf->b_ctr+=32;
	}*/	
}

/* padding function
void padding(FILE* fout, cmp_buf* buf ){
	encode( buf, 4U, 0X000FU);
	encode( buf, 8U, 0X00FFU);

	fwrite( &buf->data[1],sizeof(uint32_t),1,fout);	
		//buf->b_ctr-=32;
	if( (buf->b_ctr) < BCTRMX-32 )		
		if(!fwrite( &buf->data[0],sizeof(uint32_t),1,fout)){
			fprintf(stderr, "could not write to file \n");
			exit(EXIT_FAILURE);
		}
	
}

*/