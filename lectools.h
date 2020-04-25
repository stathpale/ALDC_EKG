#ifndef __LECTOOLS_H__

#   define __LECTOOLS_H__

#   include "aldc.h"

#   define BUFF_SIZE (ALEC_WND)
#   define BCTRMX ((BUFF_SIZE)*32-1)


    typedef void compressor(outbuf*, int16_t*, bool);

    typedef struct{
	    uint32_t b_ctr;	
	    uint32_t data[BUFF_SIZE];
    }cmp_buf ;

    typedef struct{
	    uint32_t b_ctr;
	    uint32_t data;
    }t_buf;



    /**
     ** @name File Input and Output
     ** @{
     **/
 

    // encoding par
#   if defined(__ALDC__)

    static uint32_t get_buf_sum(int16_t* inbuf);

#   endif



#   if defined(__ALDC_3_2__) || defined(__ALDC_3_1__) || defined(__ALEC_3__)

    static void alec3(outbuf* bufout, int16_t* inbuf,bool ft );
    static void al3_init(bool first);

#   endif


#   if defined(__ALDC_3_2__) || defined(__ALDC_2_1__) || defined(__ALEC_2__)

    static void alec2(outbuf* bufout, int16_t* inbuf, bool ft);
    static void al2_init(bool first);

#   endif


#   if defined(__ALDC_3_1__) || defined(__ALDC_2_1__) || defined(__LEC__)

    static void lec(outbuf* bufout, int16_t* inbuf, bool ft );

#   endif

    static void lec_init(bool first);
    static void encode_init(int16_t d, char const huf_opt, cmp_buf* buf);
    static uint16_t two2one_cmpl(int16_t dta, uint32_t dta_ordr);
    static void encode( cmp_buf* buf, uint32_t len, uint16_t dta);
    static uint32_t define_n(int16_t d);
    static void f_trsmt(outbuf* bufout, cmp_buf buf);


#endif