/* Outstanding leg compressor*/

/* INCLUDES */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "lectools.h"
#include "datasets_paths.h"



/* MACRO DEFINITIONS*/
/* TYPEDEFS*/



int main ( int argc, char* argv[argc+1]){
	/* INITIALIZATION*/
	cmp_buf stream={.b_ctr=BUFF_SIZE*32-1, .data={0U},
					.b_max=BUFF_SIZE*32-1, .word32size=BUFF_SIZE};
	f_io fio = {.in_id=in1, .out_id=out1,
				.in_mode="rb", .out_mode="wb"};	
	fio=f_open(fio);                            //get FILE I/O pointers
	

	if( lec(fio, '1', fio.nsamples, &stream )){
		fprintf(stderr, "lec encoder function failed\n");
		exit(EXIT_FAILURE);
	}
	padding(fio.out, &stream);

	f_close(fio);
	
	printf("DONE\n");
	return EXIT_SUCCESS;
}