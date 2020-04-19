#define __ALDC_H__
#ifdef __ALDC_H__

//# define __ALDC_3_1__
//#define __ALDC_2_1__
//#define __ALDC_3_2__
//#define __ALEC_3__
//#define __ALEC_2__
//#define __LEC__

# if defined(__ALDC_3_2__) || defined(__ALDC_3_1__) || defined(__ALDC_2_1__)
# 	define __ALDC__
# endif

# include <stdbool.h>
# include <stdint.h>
 typedef struct {
	 size_t  ctr;
	 uint32_t* data;
 }outbuf ;
 typedef void compressor(outbuf*, int16_t*, bool);

 void aldc (outbuf* bufout, int16_t* inbuf,size_t inbuf_len);
 void padding(outbuf* bufout);
 void cmp_buf_init(void);

#endif