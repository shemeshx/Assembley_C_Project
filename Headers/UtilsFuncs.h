
#ifndef UTILSFUNCSH
#define UTILSFUNCSH

#include <stdio.h>
#include "Structs.h"
instNode* buildInstructionsList(FILE *);
methods* buildMethods();
char indxOfMethod(methods *methods,char *method);
char* substr(const char *src, int m, int n); /*The function gets string and returns a substring from m index to n (excluding n).*/
void convertStringToArray(char* str, char *delim ,char** arr);
int amountOfChars(char* str, char c);
#endif 
