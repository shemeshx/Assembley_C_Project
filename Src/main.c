#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/FirstTransition.h"
#include "../Headers/Constants.h"
#include "../Headers/Validations.h"
#include "../Headers/UtilsFuncs.h"

int main(int argc, char **argv) {

   exportFile *file =NULL; /*creating an export file struct.*/

   if(isFileValid(argc,argv)){ /*checks if the file is valid*/
      file = firstTransition(argv[argc-1]); /*start first transition*/
   }

   if(file==NULL)/*if the first and second trasitions not passed the files will not create*/
      return -1;
   else
   {
      createFiles(file);/*create the relevant files.*/
      freeAllData(file);/*free all the structs*/
      return 0;
   }
   
}