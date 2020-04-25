/** @file aldc.h
 ** **author:** Palaiologos Efstathios
 ** 
 ** @brief __IMPORTANT! READ THIS FIRST.__ The header aldc.h describes the compression interface
 ** and includes essential macros that must be defined properly before compilation. 
 ** 
 ** __SECTION 1 : COMPRESSION METHOD__   
 ** Select one of the compilation options definitions from @a "__ALDC_3_1__" to  @a "__LEC__"
 ** in order to compile the source code of this project into the corresponding compression programm.
 ** If you compile  using Visual Studio or Codeblocks(Windows)
 ** then you must define exactly one of the above compilation options, the rest options
 ** must remain inactive with comment-out. If you compile using GCC or CLANG (Linux)  you
 ** may skip the definitiion of any of the available compression methods and include the 
 ** command : "-D [compilation-option] 1" during compilation.  
 **
 ** 
 **
 ** __SECTION 2 : SIZE OF THE ALDC and ALEC WINDOWS__   
 ** @a ALDC_WND defines the number of samples that are compressed using the ALDC-DR
 ** algorithm. @a ALDC_WND must always be defined even if the selected  compression method 
 ** is not ALDC (eg:  LEC, ALEC2, ALEC3).  
 ** @a ALEC_WND defines the number of samples that are compressed using the ALEC algorithm.
 ** @a ALDC_WND must always be defined even if the slected compression method is LEC.
 ** IMPORTANT RULE : ALDC_WND must always be an integer multiple of ALEC_WND.
 **
 **
 **
 ** __SECTION 3 : COMPRESSION (HUFFMAN) TABLES__     
 ** In the preprocessor directive  "#define ALxOPTy z", x represents the number of huffman 
 ** tables used by the selected compression method y repersents the contents of the the 
 ** corresponding table, z is the definition  (char ) that matches the option y to one 
 ** of the available Huffman tables  that are included in the file "huftbl.c"
 **
 **/

#ifndef __ALDC_H__

#define __ALDC_H__ 
#include <stdbool.h>        
#include <stdint.h>          // usage of standart data types for prortability
#include <stdio.h>           // for debugging 
#include <stdlib.h>          // malloc and friends

/////////////////////////////////////////////////////////////////////////
/// AVAILABLE COMPRESSION METHODS (__DEFINE ONLY ONE!__): 
/// 
/// "__ALDC_3_1__"
/// "__ALDC_2_1__"
/// "__ALDC_3_2__"
/// "__ALEC_3__"
/// "__ALEC_2__"
/// "__LEC__"
///
/// EXPLANATION :
/// "__ALDC_X_Y__" : HYBRID ALEC AND LEC AS COMPRESSION METHOD
/// 1 REPRESENTS LEC
/// 2 REPRESENTS ALEC WITH TWO HUFFMAN TABLES
/// 3 REPRESENTS ALEC WITH THREE HUFFMAN TABLES
///
/// "__ALEC_X__" : NEAT ADAPTIVE LEC AS COMPRESSION METHOD
/// X REPRESENTS THE NUMBER OF STATIC HUFFMAN TABLES THAT ARE USED ADAPTIVELY
///
/// "__LEC__"  : NEAT STATIC LOSSLESS ENTROPY COMPRESSOR AS COMPRESSION METHOD
///////////////////////////////////////////////////////////////////////

#define __ALDC_3_1__   ///< Hybrid ALEC 3 and LEC as compression method 
//#define __ALDC_2_1__ ///< Hybrid ALEC 2 and LEC as compression method 
//#define __ALDC_3_2__ ///< Hybrid ALEC 3 and ALEC 2 as compression method 
//#define __ALEC_3__   ///< Neat ALEC 3 as compression method
//#define __ALEC_2__   ///< Neat ALEC 2 as compression method
//#define __LEC__      ///< Neat LEC as compression method



#define ALDC_WND 40 ///< SIZE OF THE ALDC WINDOW IN SAMPLES. (ALDC_WND % ALEC_WND) MUST ALAWAYS BE EQUAL TO 0
#define ALEC_WND 10 ///< SIZE OF THE ALEC WINDOW IN SAMPLES. (ALDC_WND % ALEC_WND) MUST ALAWAYS BE EQUAL TO 0


#define LECOPT  '1' ///< LEC's unique Huffman table. Go to file huftlb.c to see the available tables
#define AL2OPT1 '2' ///< ALEC2's first Huffman table. Go to file huftlb.c to see the available tables
#define AL2OPT2 '3' ///< ALEC2's second Huffman table. Go to file huftlb.c to see the available tables
#define AL3OPT1 '1' ///< ALEC3's first Huffman table. Go to file huftlb.c to see the available tables
#define AL3OPT2 '2' ///< ALEC3's second Huffman table. Go to file huftlb.c to see the available tables
#define AL3OPT3 '3' ///< ALEC3's third Huffman table. Go to file huftlb.c to see the available tables


 
#define AL3OP1_CD 0X2U       ///< The unique prefix code '10' expresses the compression with  the first Huffman table of ALEC 3
#define AL3OP2_CD 0X3U       ///< The unique prefix code '11' expresses the compression with  the second Huffman table of ALEC 3
#define AL3OP3_CD 0X0U       ///< The unique prefix code '0' expresses the compression with  the third Huffman table of ALEC 3
#define AL3OP1_CD_LN 2U      ///< Unique's prefix code '10' size in bits
#define AL3OP2_CD_LN 2U      ///< Unique's prefix code '11' size in bits
#define AL3OP3_CD_LN 1U      ///< Unique's prefix code '0'size in bits
#define AL2OP1_CD 0X1U       ///< The unique prefix code '1' expresses the compression with  the first Huffman table of ALEC 2
#define AL2OP2_CD 0X0U       ///< The unique prefix code '0' expresses the compression with  the second Huffman table of ALEC 2
#define AL2OP1_CD_LN 1U      ///< Unique's prefix code '1' size in bits
#define AL2OP2_CD_LN 1U      ///< Unique's prefix code '0' size in bits
#define END_TRNM_CD1 0x000DU ///< First part of the unique END OF TRANSIMISION prefix code that can be used when encoding with tables '1' '2' or '3'
#define END_TRNM_CD2 0x0001U ///< Second part of the  unique END OF TRANSIMISION prefix code that can be used when encoding with tables '1' '2' or '3'
#define END_TRNM_CD1_LEN 4U  ///< Unique's prefix code  '1101' size in bits
#define END_TRNM_CD2_LEN 8U  ///< Unique's prefix code '00000001' size in bits


#if defined(__ALDC_3_2__) || defined(__ALDC_3_1__) || defined(__ALDC_2_1__)
#define __ALDC__ ///< States that the selected compression method belongs to the ALDC family

#define ALDCOP1_CD 0X0U   ///< The unique prefix code '0' expresses the compression with  the first method (ALEC3, ALEC2 OR LEC)
#define ALDCOP2_CD 0X1U   ///< The unique prefix code '1' expresses the compression with  the second method (ALEC3, ALEC2 OR LEC)
#define ALDCOP1_CD_LN 1U  ///< Unique's prefix code size in bits
#define ALDCOP2_CD_LN 1U  ///< Unique's prefix code size in bits

#endif /* __ALDC__ */

/** @brief A structure to represent the output buffer. 
 **
 ** The user must allocate memory for the compressed stream. The size of the allocated memory
 ** must be analogous  to the size of the input buffer and able to handle the worst case scenarios.
 ** (aprox.) output buffer size = 1.5 * input buffer size 
 **  
 **
 */ 
typedef struct {
    
    size_t  ctr;    ///< Counts the number of 32bit words that are writen to the buffer. 
    uint32_t* data; ///<Is the starting address of the output buffer.
    
}outbuf ;


/** @brief Initializes the internal  compression buffers and variables.  
 **
 ** This function must be called before calling aldc for the first time 
 ** for a new recording
 **
 */
void cmp_buf_init(void);



/** @brief Encoding function that uses the predefined by the user compression method.
 **
 ** Compresses the contents of @a difbuf into @a bufout.
 ** __This function has memory__, it only writes whole 32bit words to bufout 
 ** and it remembers the the remnants of the compressed bit stream.  
 ** eg : if the compressed bit stream of an  input buffer of 40 samples is 330 bits,
 ** then 10* 32-bit-words will be written to bufout and the rest 10 bits will be remembered.
 ** @param[in] diffbuf Pointer at the start of the input buffer. 
 ** Contents of this buffer must be the differences of each pair of two 
 ** sequential adc samples  
 ** eg: difbuf[i] = sample[i] - sample[i-1] ,
 ** difbuf[i+1]= sample[i+1] - sample[i] etc. 
 ** @param[in] difbuf_len Size of difbuf in half words (16 bits).
 ** dibfuf_len must always be an integer multiple of ALDC_WND or else the program
 ** will be terminated with return value -1.
 ** @param[in] bufout Output buffer. Must be an initialized struct of outbuf type
 ** as specified in the typedef outbuf description.
 */
void aldc(outbuf* bufout, int16_t* difbuf, size_t difbuf_len);

/** @brief Finishes the  compression process
 **
 ** This function must be called after calling aldc for the last time.
 ** It appends the END OF TRANSMISSION CODE to the remnants of the compression stream 
 ** and stores them to the output buffer
 */
void padding(outbuf* bufout);

#endif /* __ALDC_H__ */
