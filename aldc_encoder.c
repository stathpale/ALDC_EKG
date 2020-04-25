/* Outstanding aldc compressor*/

/* INCLUDES */

#include "aldc.h"
#include "fio.h"
#include "datasets_paths.c"


int main(void) {
	/* INITIALIZATION*/
	for ( size_t fctr=0; fctr<8; fctr++){
		f_io fio = { .in_id = samples_dir[fctr]  ,
					 .out_id = cmpr_samples_dir[fctr]};
		int16_t* inbuf = 0;
		fio = f_open(fio, &inbuf);
		outbuf bufout = { .ctr = 0, .data = malloc(sizeof(uint32_t) * fio.nsamples / 2) };
		printf("compressing %s . . . .\n",fio.in_id );
		
		cmp_buf_init();
		aldc(&bufout, inbuf, fio.nsamples);
		padding(&bufout);
		
		fwrite(bufout.data, sizeof(uint32_t), bufout.ctr, fio.out);
		f_close(fio);
		free(inbuf);
	}
	printf("Done! \n");
	

	return EXIT_SUCCESS;
}