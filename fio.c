#include "fio.h"
#include "fio_func.h"



f_io f_open(f_io files,int16_t** inbufp ){
	files.in = fopen( files.in_id , "rb");
	files.out= fopen( files.out_id, "wb");
	if ((!files.in)||(!files.out)){
		fprintf(stderr, "Unable to open input or output file \n");
		exit(EXIT_FAILURE);
	}
	files.nsamples = f_get_len(files.in);
	*inbufp= malloc(sizeof(int16_t)*files.nsamples);
	bufndif(files.in,files.nsamples, *inbufp);
	return files;	
}

void f_close(f_io files){
	fclose(files.in);
	fclose(files.out);
}

static size_t f_get_len(FILE* fptr){
	
	fseek(fptr, 0, SEEK_END); //sets the position indicator to the end of the file
	size_t file_len = ftell(fptr);   //retruns the size of the file in bytes
	fseek(fptr, 0, SEEK_SET); //sets the position indicator back to the start of the file
	return file_len/2;
}

static int16_t f_fetch_sample(FILE* fptr){
	int16_t sample;
	if(!fread(&sample, sizeof(int16_t), 1, fptr)){
		fprintf(stderr, "Unable to fetch sample from file");
		exit(EXIT_FAILURE);
	}
	return sample;
}

static void bufndif(FILE* fptr,size_t len, int16_t* buf){
	int16_t prev=0;
	int16_t temp;
	for( size_t i = 0 ; i<len ;++i){
		temp=f_fetch_sample( fptr);
		*(buf+i)=temp-prev;
		prev=temp;
	}
}
