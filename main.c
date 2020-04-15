/* Outstanding leg compressor*/

/* INCLUDES */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "lectools.h"
#include "fio.h"
#include "datasets_paths.h"


int main (void) {
	/* INITIALIZATION*/
	f_io fio = {.in_id=in8  ,
			  .out_id=out8  ,
			.in_mode="rb ",
			.out_mode="wb"};
	printf("test no 2\n");
				
	int16_t* inbuf=0;

	fio=f_open(fio,&inbuf); 
	
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