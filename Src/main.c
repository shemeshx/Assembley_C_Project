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
      /*char *locOfDot = (int)strchr(argv[1],'.');*/
      /*int fileNameSize = locOfDot - argv[1];*/
      printf("%s",file->fileName);
      /*strcpy(str,substr(argv[1],0,fileNameSize));*/
      /*printf("%s",argv[1]);*/
      /*createFiles(file,filename[0]);*/
      return 0;
   }

}