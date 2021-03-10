#include "../Headers/Validations.h"
#include "../Headers/Constants.h"
#include <string.h>

boolean isLabel(char *word)
{
    if(word[strlen(word)-1]==':')
        return true;
    return false;
}

boolean isDataAllocation(char *word)
{
    if(strcmp(word,".string")==0 || strcmp(word,".data")==0)
        return true;
    return false;
}