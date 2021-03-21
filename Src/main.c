#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/FirstTransition.h"
#include "../Headers/Constants.h"
#include "../Headers/Validations.h"
#include "../Headers/UtilsFuncs.h"

int main(int argc, char **argv) {
   exportFile *file =NULL;
   if(isFileValid(argc,argv)){
      file = firstTransition(argv[argc-1]); 
   }

   if(file==NULL)
      return -1;
   else
   {
      createFiles(file);
      return 0;
   }
   
}