
#ifndef VALIDATIONH
#define VALIDATIONH

#include <stdio.h>
#include "Constants.h"

/*
    Validations functions.
*/

    /*The function returns true if the word is a label.*/
    boolean isLabel(char[]); 
    
    /*The function returns true if the word is allocation data word.*/
    boolean isDataAllocation(char *word);
    
    /*the function returns true if the given word uis extern or entry*/
    boolean isExternalOrEntry(char *word);
    
    /*return the type of addressing,*/
    addresingType checkTypeOfAddressingModes(char *word);
    
    /*check if a string is a method*/
    boolean isMethod(char *str);
    
    /*check if a line is blank or comment*/
    boolean isBlankOrCommentLine(char *str);
    
    /*check if the arguments contain a valid file*/
    boolean isFileValid(int argc, char **argv);
    
    /*check if the number is valid with 12 bits.*/
    boolean isValidNumber(int num);
    
    /*check if string is a valid int*/
    boolean is_valid_int(char *str);
#endif 
