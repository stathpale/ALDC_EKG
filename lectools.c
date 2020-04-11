#include "lectools.h"




static const uint16_t msk_tbl[12] = {	[ 0]=0X0001U, [ 1]=0X0003U, [ 2]=0X0007U,
										[ 3]=0X000fU, [ 4]=0X001fU, [ 5]=0X003fU,
										[ 6]=0X007fU, [ 7]=0X00ffU, [ 8]=0X01ffU, 
										[ 9]=0X03ffU, [10]=0X07ffU, [11]=0X0fffU,};
								
								
						   
static const uint16_t huf_tbl1[13] = {  [ 0]=0X0007U, [ 1]=0X0000U, [ 2]=0X0002U,
										[ 3]=0X000DU, [ 4]=0X0019U, [ 5]=0X0063U,
										[ 6]=0X0030U, [ 7]=0X00C5U, [ 8]=0X0189U, 
										[ 9]=0X0C40U, [10]=0X0311U, [11]=0X0C41U,
										[12]=0X0621U, };		
		
static const size_t huf_tbl1_len[13] ={ [ 0]= 3, [ 1]= 1,  [ 2]= 2,
										[ 3]= 4, [ 4]= 5,  [ 5]= 7,
										[ 6]= 6, [ 7]= 8,  [ 8]= 9,
										[ 9]=12, [10]=10,  [11]=12,
										[12]=11};		
									
static const uint16_t huf_tbl2[13] = {  [ 0]=0X0021U, [ 1]=0X0011U, [ 2]=0X0009U,
										[ 3]=0X0003U, [ 4]=0X000BU, [ 5]=0X000AU,
										[ 6]=0X0000U, [ 7]=0X0003U, [ 8]=0X0002U, 
										[ 9]=0X0100U, [10]=0X0041U, [11]=0X0101U,
										[12]=0X0081U, };

static const size_t huf_tbl2_len[13] = {[ 0]= 6, [ 1]= 5,  [ 2]= 4,
										[ 3]= 3, [ 4]= 4,  [ 5]= 4,
										[ 6]= 2, [ 7]= 2,  [ 8]= 3,
										[ 9]= 9, [10]= 7,  [11]= 9,
										[12]= 8}; 
									
static const uint16_t huf_tbl3[13] = {	[ 0]=0X0015U, [ 1]=0X000BU, [ 2]=0X0003U,
										[ 3]=0X0000U, [ 4]=0X0004U, [ 5]=0X00A7U,
										[ 6]=0X0052U, [ 7]=0X0028U, [ 8]=0X014DU, 
										[ 9]=0X0A60U, [10]=0X0299U, [11]=0X0A61U,
										[12]=0X0531U, };
								
static const size_t huf_tbl3_len[13] ={ [ 0]= 5, [ 1]= 4,  [ 2]= 2,
										[ 3]= 1, [ 4]= 3,  [ 5]= 8,
										[ 6]= 7, [ 7]= 6,  [ 8]= 9,
										[ 9]=12, [10]=10,  [11]=12,
										[12]=11};
									

							
static const uint16_t huf_tbl1b[13] ={  [ 0]=0X0000U, [ 1]=0X0001U, [ 2]=0X0003U,
										[ 3]=0X0005U, [ 4]=0X0009U, [ 5]=0X0011U,
										[ 6]=0X0023U, [ 7]=0X0041U, [ 8]=0X0081U, 
										[ 9]=0X0200U, [10]=0X0402U, [11]=0X0403U,
										[12]=0X0404U, };		
		
static const size_t huf_tbl1b_len[13] ={[ 0]= 2, [ 1]= 2,  [ 2]= 2,
										[ 3]= 3, [ 4]= 4,  [ 5]= 5,
										[ 6]= 6, [ 7]= 7,  [ 8]= 8,
										[ 9]=10, [10]=11,  [11]=11,
										[12]=11};		

static const uint16_t huf_tbl2b[13] ={	[ 0]=0X006FU, [ 1]=0X001AU, [ 2]=0X000CU,
										[ 3]=0X0003U, [ 4]=0X0007U, [ 5]=0X0002U,
										[ 6]=0X0000U, [ 7]=0X0002U, [ 8]=0X0005U, 
										[ 9]=0X01BBU, [10]=0X01B9U, [11]=0X0375U,
										[12]=0X0374U, };		
		
static const size_t huf_tbl2b_len[13] ={[ 0]= 7, [ 1]= 5,  [ 2]= 4,
										[ 3]= 3, [ 4]= 3,  [ 5]= 2,
										[ 6]= 2, [ 7]= 3,  [ 8]= 6,
										[ 9]= 9, [10]= 9,  [11]=10,
										[12]=10};		


static const uint16_t huf_tbl3b[13] ={  [ 0]=0X0009U, [ 1]=0X0005U, [ 2]=0X0000U,
										[ 3]=0X0001U, [ 4]=0X0003U, [ 5]=0X0011U,
										[ 6]=0X0021U, [ 7]=0X0041U, [ 8]=0X0081U, 
										[ 9]=0X0200U, [10]=0X0402U, [11]=0X0403U,
										[12]=0X0404U, };		
		
static const size_t huf_tbl3b_len[13]= {[ 0]= 4, [ 1]= 3,  [ 2]= 2,
										[ 3]= 2, [ 4]= 2,  [ 5]= 5,
										[ 6]= 6, [ 7]= 7,  [ 8]= 8,
										[ 9]=10, [10]=11,  [11]=11,
										[12]=11};		



/** @brief Initialize a circular buffer @a c with maximally @a
 ** max_len elements.
 **
 ** Only use this function on an uninitialized buffer.
 **
 ** Each buffer that is initialized with this function must be
 ** destroyed with a call to ::circular_destroy.
 **/

f_io f_open(f_io files ){
	files.in = fopen( files.in_id , files.in_mode);
	files.out= fopen( files.out_id, files.out_mode);
	if ((!files.in)||(!files.out)){
		fprintf(stderr, "Unable to open input or output file \n");
		exit(EXIT_FAILURE);
	}
	files.nsamples = f_get_len(files.in);
	return files;	
}

void f_close(f_io files){
	fclose(files.in);
	fclose(files.out);
}

size_t f_get_len(FILE* fptr){
	
	fseek(fptr, 0, SEEK_END); //sets the position indicator to the end of the file
	size_t file_len = ftell(fptr);   //retruns the size of the file in bytes
	fseek(fptr, 0, SEEK_SET); //sets the position indicator back to the start of the file
	return file_len/2;
}

int16_t f_fetch_sample(FILE* fptr){
	int16_t sample;
	if(fread(&sample, sizeof(int16_t), 1, fptr)== 0){
		fprintf(stderr, "Unable to fetch sample from file");
		exit(EXIT_FAILURE);
	}
	return sample;
}

void f_write(FILE* fout, cmp_buf* buf){
	
	if(buf->b_ctr< buf->b_max-32){		
		uint32_t temp=buf->data[buf->b_max/32];
		fwrite( &temp,sizeof(uint32_t),1,fout);
		buf->data[(buf->word32size)-1]=buf->data[(buf->word32size)-2];
		buf->data[(buf->word32size)-2]=0;
		buf->b_ctr+=32;
	}
	
}


/**/


int32_t lec(f_io fio, char const huf_opt,
	size_t n_samples, cmp_buf* buf ){
	int16_t r[2]={0};			
	for (size_t k = 0; k <n_samples; k++){
		r[1] = f_fetch_sample(fio.in);  	
		
		if(encode_init(r[1]-r[0], huf_opt, buf)){
			fprintf(stderr, "Wrong mode\n");
			exit(EXIT_FAILURE);
		}
		f_write(fio.out,buf);
		r[0] = r[1];
	}
	return EXIT_SUCCESS;
}

int32_t encode_init( int16_t di, char const huf_opt,cmp_buf* buf){
	uint32_t ni = define_n(di);
	uint16_t d=two2one_cmpl(di,ni);
	int32_t ovf_chk = 0;
	switch(huf_opt){
		case '1': 
			ovf_chk=encode( buf, huf_tbl1_len[ni], huf_tbl1[ni]);
			break;
		case '2':
			ovf_chk=encode( buf, huf_tbl2_len[ni], huf_tbl2[ni]);
			break;
		case '3':
			ovf_chk=encode( buf, huf_tbl3_len[ni], huf_tbl3[ni]);
			break;
		case '4': 
			ovf_chk=encode( buf, huf_tbl1b_len[ni], huf_tbl1b[ni]);
			break;
		case '5':
			ovf_chk=encode( buf, huf_tbl2b_len[ni], huf_tbl2b[ni]);
			break;
		case '6':
			ovf_chk=encode( buf, huf_tbl3b_len[ni], huf_tbl3b[ni]);
			break;
		default: 	
			return EXIT_FAILURE;
	}
	if(ovf_chk){
			fprintf(stderr, "huff table overflowed\n");
			exit(EXIT_FAILURE);
	}
	if(ni)ovf_chk=encode( buf, ni, d);
	if(ovf_chk){
			fprintf(stderr, "diff off samples > 12 bits \n");
			exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;


}  

uint16_t two2one_cmpl(int16_t dta, uint32_t dta_ordr){
	if(dta<0){		
		return (uint16_t)(msk_tbl[dta_ordr-1]&(dta-1));
	}else 
		return (uint16_t)dta;
}

int32_t encode( cmp_buf* buf, uint32_t len, uint16_t dta){	
	if (len>=13){
		return EXIT_FAILURE;
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
	return EXIT_SUCCESS;
	
}

uint32_t define_n(int16_t d){
	uint32_t  n = 0;
	while (d !=  0)	{
		d = d / 2;
		n++;
	}
	return n;
}

void padding(FILE* fout, cmp_buf* buf ){
	encode( buf, 4U, 0X000FU);
	encode( buf, 8U, 0X00FFU);

	fwrite( &buf->data[1],sizeof(uint32_t),1,fout);	
		//buf->b_ctr-=32;
	if( (buf->b_ctr) < (buf->b_max-32) ){		
		fwrite( &buf->data[0],sizeof(uint32_t),1,fout);	
	}
}


