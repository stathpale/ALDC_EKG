//#define __ALDC_CMPR_3_1__
//#define __ALDC_CMPR_2_1__
#include <stdbool.h>
#include <stdint.h>
typedef struct {
	size_t  ctr;
	uint32_t* data;
}outbuf ;
typedef void compressor(outbuf*, int16_t*, bool);

void aldc (outbuf* bufout, int16_t* inbuf,size_t inbuf_len);
void padding(outbuf* bufout);
void cmp_buf_init(void);