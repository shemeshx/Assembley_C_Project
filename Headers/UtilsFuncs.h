
#ifndef UTILSFUNCSH
#define UTILSFUNCSH

#include <stdio.h>
#include "Structs.h"
instNode* buildInstructionsList(FILE *);
methods* buildMethods();
char indxOfMethod(methods *methods,  char *method);
char* substr(char *src, int m, int n); /*The function gets string and returns a substring from m index to n (excluding n).*/
void convertStringToArray( char* str, char *delim ,char** arr);
int amountOfChars(char* str, char c);
void createFiles(exportFile *file,char *name);
int char_index(char c, char *string);
#endif 
