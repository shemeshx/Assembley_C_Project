/*
 All the constants define here.
*/
#ifndef CONSTANTSH
#define CONSTANTSH

#define MAX_LINE_LEN 80

#define TEMP_FILE "test.txt" /*TODO - need to be removed! replace with original input file.*/

#define SPACE_CHAR 32

typedef int boolean;
enum { false, true };

#define METHODS_AMOUNT 16

#define METHOD_NOT_FOUND -1

#define ERROR_WRONG_ADDRESSINGMODE -2

#define ERROR_ARGUMENT_NOT_VALID -3
typedef char addresingType;
enum {immediate, direct, relative, register_direct};
#define AMOUNT_OF_BITS_SRC_CODE 12
#endif