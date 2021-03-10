
#ifndef UTILSFUNCSH
#define UTILSFUNCSH

#include <stdio.h>
#include "Structs.h"
instNode* buildInstructionsList(FILE *);
char* substr(const char *src, int m, int n); /*The function gets string and returns a substring from m index to n (excluding n).*/
#endif 
