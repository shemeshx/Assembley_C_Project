#include "../Headers/Validations.h"
#include "../Headers/Constants.h"
#include "../Headers/UtilsFuncs.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/*
    Validations functions.
*/


/*The function returns true if the word is a label.*/
boolean isLabel(char *word)
{
    if(word[strlen(word)-1]==':' && strlen(word)<=MAX_LENGTH_LABEL)
        return true;
    return false;
}


boolean isContainLettersAndNumbers(char *word)
{
    int i=0;
    boolean check;
    check = false;

    while(i<strlen(word))
    {
        unsigned char c = (unsigned char)(word[i]);
        if(c >= 'a' && c <= 'z')
            check = true;
        else if(c >= 'A' && c <= 'Z')
            check = true;
        else if(c >= '0' && c <= '9')
            check = true;
        if(check == false)
            break;
        i++;
    }
    return check;
}

/*The functions return true if the word is allocation data word.*/
boolean isDataAllocation(char *word)
{
    if(strcmp(word,".string")==0 || strcmp(word,".data")==0)
        return true;
    return false;
}

 /*the function returns true if the given word uis extern or entry*/
boolean isExternalOrEntry(char *word)
{
    if(strcmp(word,".extern")==0 || strcmp(word,".entry")==0)
        return true;
    return false;
}

/*check if string is a valid int*/
boolean is_valid_int(char *str)
{
   if (*str == '-')
      ++str;

   if (!*str)
      return false;

   while (*str)
   {
      if (!isdigit(*str))
         return false;
      else
         ++str;
   }
   return true;
}

/*check if the number is valid with 12 bits.*/    
boolean isValidNumber(int num)
{
    if(num<=BIGGEST_12_BITS_NUM && num>=SMALLEST_12_BITS_NUM)
        return true;
    return false;
}


boolean isRegister(char *word)
{
    if(strlen(word)!=2)
        return false;
    if(word[0]!='r')
        return false;
    if(word[1] <'0' || word[1]>'7')
        return false;
    return true;
}

/*return the type of addressing,*/
addresingType checkTypeOfAddressingModes(char *word)
{
    if(word[0]=='#' && (is_valid_int(substr(word,1,strlen(word)))==true && isValidNumber(atoi(substr(word,1,strlen(word))))))
            return immediate;
    else if(word[0]=='%' && (isContainLettersAndNumbers(substr(word,1,strlen(word)))==true && strlen(word)<32) )
            return relative;
    else if(isRegister(word)==true)
            return register_direct;
    else if(isContainLettersAndNumbers(word)==true && strlen(word)<=MAX_LENGTH_LABEL)   
        return direct;
    return ERROR_ARGUMENT_NOT_VALID;

}

/*check if a string is a method*/
boolean isMethod(char *str)
{
    methods* methods = buildMethods();
    int i;
    for (i = 0; i < METHODS_AMOUNT; i++)
    {
        if(strcmp(methods->name[i],str)==0)
            return true;
    }
    return false;
}

/*check if a line is blank or comment*/
boolean isBlankOrCommentLine(char *str)
{
    if(strcmp(str,"\n")==0)
        return true;
    else if(*str == ';')
        return true;
    return false;
}

/*check if the arguments contain a valid file*/
boolean isFileValid(int argc, char **argv)
{
    FILE *fptr;

    if(argc != 2)
        return false;

    fptr = fopen(argv[argc-1], "r");
    if (fptr == NULL)
        return false;

    fclose(fptr);

    return true;
}

