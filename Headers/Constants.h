/*
 All the constants define here.
*/
#ifndef CONSTANTSH
#define CONSTANTSH

#define MAX_LINE_LEN 80 /*max length of line is .as file*/

#define TEMP_FILE "test.ob" /*TODO - need to be removed! replace with original input file.*/

#define SPACE_CHAR 32 /*ASCII for space*/

#define MAX_LENGTH_LABEL 32 /*max length of label.*/

/*boolean type definition*/
typedef int boolean;
enum { false, true };

#define METHODS_AMOUNT 16 /*the amout of methods (mov,cmp,lea, etc...)*/

#define BIGGEST_12_BITS_NUM 4096 /*the max value of 12 bit number.*/
#define SMALLEST_12_BITS_NUM -4095/*the min value of 12 bit number.*/
#define AMOUNT_OF_BITS_SRC_CODE 12/*the amount of bits in a number*/


/*Error definition*/
#define METHOD_NOT_FOUND -1
#define SYMBOL_NOT_FOUND NULL
#define ERROR_WRONG_ADDRESSINGMODE -2
#define ERROR_ARGUMENT_NOT_VALID -3

/*type of addresses*/
typedef char addresingType;
enum {immediate, direct, relative, register_direct};

/*type of outsource data*/
typedef char outsourceType;
enum {Extern,Entry};
#endif