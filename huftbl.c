/** @file huftbl.c
 ** **author:** Palaiologos Efstathios
 **
 ** @brief Static Huffman Tables.
 **
 ** This .c file contains two different sets of Huffman tables, each one with three discrete levels.
 ** The identifiers huf_tblx and huf_tblxb, stand for set a and b respectively, while x represents the level. 
 ** For each Huffman table there is corresponding table that contains the length of the unique prefix code of each element.
 */

#include <stdint.h>


/* table '1' */ 
static const uint16_t huf_tbl1[13] = {  [ 0]=0X0007U, [ 1]=0X0000U, [ 2]=0X0002U,
										[ 3]=0X000DU, [ 4]=0X0019U, [ 5]=0X0063U,
										[ 6]=0X0030U, [ 7]=0X00C5U, [ 8]=0X0189U, 
										[ 9]=0X0C40U, [10]=0X0311U, [11]=0X0C41U,
										[12]=0X0621U, };		
		
static const size_t huf_tbl1_len[13] ={ [ 0]= 3, [ 1]= 1,  [ 2]= 2,
										[ 3]= 4, [ 4]= 5,  [ 5]= 7,
										[ 6]= 6, [ 7]= 8,  [ 8]= 9,
										[ 9]=12, [10]=10,  [11]=12,
										[12]=11};		

/* table '2' */
static const uint16_t huf_tbl2[13] = {  [ 0]=0X0021U, [ 1]=0X0011U, [ 2]=0X0009U,
										[ 3]=0X0003U, [ 4]=0X000BU, [ 5]=0X000AU,
										[ 6]=0X0000U, [ 7]=0X0003U, [ 8]=0X0002U, 
										[ 9]=0X0100U, [10]=0X0041U, [11]=0X0101U,
										[12]=0X0081U, };

static const size_t huf_tbl2_len[13] = {[ 0]= 6, [ 1]= 5,  [ 2]= 4,
										[ 3]= 3, [ 4]= 4,  [ 5]= 4,
										[ 6]= 2, [ 7]= 2,  [ 8]= 3,
										[ 9]= 9, [10]= 7,  [11]= 9,
										[12]= 8}; 
	
/* table '3' */
static const uint16_t huf_tbl3[13] = {	[ 0]=0X0015U, [ 1]=0X000BU, [ 2]=0X0003U,
										[ 3]=0X0000U, [ 4]=0X0004U, [ 5]=0X00A7U,
										[ 6]=0X0052U, [ 7]=0X0028U, [ 8]=0X014DU, 
										[ 9]=0X0A60U, [10]=0X0299U, [11]=0X0A61U,
										[12]=0X0531U, };
								
static const size_t huf_tbl3_len[13] ={ [ 0]= 5, [ 1]= 4,  [ 2]= 2,
										[ 3]= 1, [ 4]= 3,  [ 5]= 8,
										[ 6]= 7, [ 7]= 6,  [ 8]= 9,
										[ 9]=12, [10]=10,  [11]=12,
										[12]=11};

/* table '4' */
static const uint16_t huf_tbl1b[13] ={  [ 0]=0X0000U, [ 1]=0X0001U, [ 2]=0X0003U,
										[ 3]=0X0005U, [ 4]=0X0009U, [ 5]=0X0011U,
										[ 6]=0X0021U, [ 7]=0X0041U, [ 8]=0X0081U, 
										[ 9]=0X0200U, [10]=0X0402U, [11]=0X0403U,
										[12]=0X0404U, };		
		
static const size_t huf_tbl1b_len[13] ={[ 0]= 2, [ 1]= 2,  [ 2]= 2,
										[ 3]= 3, [ 4]= 4,  [ 5]= 5,
										[ 6]= 6, [ 7]= 7,  [ 8]= 8,
										[ 9]=10, [10]=11,  [11]=11,
										[12]=11};


/* table '5' */
static const uint16_t huf_tbl2b[13] ={	[ 0]=0X006FU, [ 1]=0X001AU, [ 2]=0X000CU,
										[ 3]=0X0003U, [ 4]=0X0007U, [ 5]=0X0002U,
										[ 6]=0X0000U, [ 7]=0X0002U, [ 8]=0X0036U, 
										[ 9]=0X01BBU, [10]=0X01B9U, [11]=0X0375U,
										[12]=0X0374U, };		
		
static const size_t huf_tbl2b_len[13] ={[ 0]= 7, [ 1]= 5,  [ 2]= 4,
										[ 3]= 3, [ 4]= 3,  [ 5]= 2,
										[ 6]= 2, [ 7]= 3,  [ 8]= 6,
										[ 9]= 9, [10]= 9,  [11]=10,
										[12]=10};		

/* table '6' */
static const uint16_t huf_tbl3b[13] ={  [ 0]=0X0009U, [ 1]=0X0005U, [ 2]=0X0000U,
										[ 3]=0X0001U, [ 4]=0X0003U, [ 5]=0X0011U,
										[ 6]=0X0021U, [ 7]=0X0041U, [ 8]=0X0081U, 
										[ 9]=0X0200U, [10]=0X0402U, [11]=0X0403U,
										[12]=0X0404U, };		
		
static const size_t huf_tbl3b_len[13]= {[ 0]= 4, [ 1]= 3,  [ 2]= 2,
										[ 3]= 2, [ 4]= 2,  [ 5]= 5,
										[ 6]= 6, [ 7]= 7,  [ 8]= 8,
										[ 9]=10, [10]=11,  [11]=11,
										[12]=11};		
