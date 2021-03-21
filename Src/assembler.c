#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/FirstTransition.h"
#include "../Headers/Constants.h"
#include "../Headers/Validations.h"
#include "../Headers/UtilsFuncs.h"

int main(int argc, char **argv) {

   int i;
   exportFile *file =NULL; /*creating an export file struct.*/
   
   if(argc==1){
      printf("No file entered.");
      return -1;
   }

   for (i = 1; i < argc; i++)
   {
      if(isFileValid(argv[i])) /*checks if the file is valid*/
         file = firstTransition(argv[i]); /*start first transition*/ 
      else
         printf("there %s is not a valid file!\n",argv[i]);
      
      if(file==NULL)/*if the first and second trasitions not passed the files will not create*/
      {
         printf("\n\nThe running failed. no files will be create.");
         continue;
      }
      else
      {
         createFiles(file);/*create the relevant files.*/
         freeAllData(file);/*free all the structs*/
         printf("\n\nSuccess! file has been created.");
      }
   }
   return 0;
}