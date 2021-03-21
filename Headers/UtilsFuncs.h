
#ifndef UTILSFUNCSH
#define UTILSFUNCSH

#include <stdio.h>
#include "Structs.h"
/*
    Utilites functions.
*/

/*
    the function return new list of instructions from a file.
*/
instNode* buildInstructionsList(FILE *);

/*
    Build the methods struct.
*/
methods* buildMethods();

/*
    The function return the index of method.
    if not exist return an error.
*/
char indxOfMethod(methods *methods,  char *method);

/*
    return a substring from m to n (not including n) position.
*/
char* substr(char *src, int m, int n); /*The function gets string and returns a substring from m index to n (excluding n).*/

/*
    convert a string to array by delimeter
*/
void convertStringToArray( char* str, char *delim ,char** arr);

/*
    return amount of characters of given character c in string.
*/
int amountOfChars(char* str, char c);

/*
    The function create the ob,ext and ent files.
*/
void createFiles(exportFile *file);

/*
    The function return the index of character in a string
*/
int char_index(char c, char *string);

/*
    free all the structs
*/
void freeAllData(exportFile *file);
#endif 
