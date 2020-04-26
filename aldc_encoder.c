/** @file aldc_encoder.c
 ** **author:** Palaiologos Efstathios  
 **
 ** @brief __main function file__
 */
#include "aldc.h"
#include "fio.h"
#include "datasets_paths.c" 


int main(void) {
	for ( size_t fctr=0; fctr< REC_FILES_NUM; fctr++){

		/* INITIALIZATION START*/
		f_io fio = { .in_id = samples_dir[fctr]  ,
					 .out_id = cmpr_samples_dir[fctr]};
		int16_t* inbuf = 0;
		fio = f_open(fio, &inbuf);
		outbuf bufout = { .ctr = 0, .data = malloc(sizeof(uint32_t) * fio.nsamples / 2) };		
		cmp_buf_init();
		/* INITIALIZATION END */

		printf("compressing %s . . . .\n", fio.in_id);

		/* MAIN COMPRESSION PROCESS START*/
		aldc(&bufout, inbuf, fio.nsamples);  //compresses the whole file in one run
		/* MAIN COMPRESSION PROCESS END*/

		
		padding(&bufout); //finalization of the compressed bit stream		
		fwrite(bufout.data, sizeof(uint32_t), bufout.ctr, fio.out);
		f_close(fio);
		free(inbuf);
	}
	printf("Done! \n");
	return EXIT_SUCCESS;
}