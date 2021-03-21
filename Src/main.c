#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/FirstTransition.h"
#include "../Headers/Constants.h"
#include "../Headers/Validations.h"
#include "../Headers/UtilsFuncs.h"

int main(int argc, char **argv) {
   char *filename; 
   exportFile *file =NULL;
   char *strr;
   if(argc == 2){
      if(isFileExists(argv[1])){
         file = firstTransition(argv[1]); 
      }
   }
   if(file==NULL)
      return -1;
   else
   {
      createFiles(file);
      return 0;
   }

}