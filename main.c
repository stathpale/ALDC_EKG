/* Outstanding leg compressor*/

/* INCLUDES */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "lectools.h"
#include "fio.h"
#include "datasets_paths.h"



/* MACRO DEFINITIONS*/
/* TYPEDEFS*/



int main ( int argc, char* argv[argc+1]){
	/* INITIALIZATION*/
	f_io fio = {.in_id=in3   ,
			.out_id=out3  ,
			.in_mode="rb ",
			.out_mode="wb"};
				
	int16_t* inbuf=0;
	
	fio=f_open(fio,&inbuf); 
	//get FILE I/O pointers
	
	//for ( size_t i = 0 ; i<1; i+=ALDC_WND ){
	for ( size_t i = 0 ; i<fio.nsamples; i+=ALDC_WND ){
		aldc(fio.out,  inbuf+i);
	}
	
	//padding(fio.out, &stream);
	//printf("%u\n",BCTRMX/32);
	f_close(fio);
	free(inbuf);
	printf("DONE\n");
	return EXIT_SUCCESS;
}