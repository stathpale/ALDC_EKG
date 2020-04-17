/* Outstanding aldc compressor*/

/* INCLUDES */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "aldc.h"
#include "fio.h"
#include "datasets_paths.h"


int main(void) {
	/* INITIALIZATION*/
	for ( size_t fctr=0; fctr<96; fctr++){
		f_io fio = { .in_id = mitin[fctr]  ,
				  .out_id = mitout[fctr] ,
				  .in_mode = "rb ",
				  .out_mode = "wb" };
		int16_t* inbuf = 0;
		fio = f_open(fio, &inbuf);
		outbuf bufout = { .ctr = 0, .data = malloc(sizeof(uint32_t) * fio.nsamples / 2) };
		cmp_buf_init();
		aldc(&bufout, inbuf, fio.nsamples);
		padding(&bufout);
		fwrite(bufout.data, sizeof(uint32_t), bufout.ctr, fio.out);
		f_close(fio);
		free(inbuf);
		printf("DONE\n");
	}

	return EXIT_SUCCESS;
}