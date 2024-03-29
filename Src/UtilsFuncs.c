/*
This file contains all the utilites functions for the project.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../Headers/Structs.h"
#include "../Headers/Constants.h"
#include "../Headers/UtilsFuncs.h"
#include "../Headers/Validations.h"
#include "../Headers/MemoryImage.h"
#include "../Headers/SymbolsTable.h"
#include "../Headers/EntryAndExtern.h"

/*
    Utilites functions.
*/

void trimSpace(char *str);/*Help function to trim spaces*/
void convertStringToArray(char* str,char *delim ,char** arr); /* this function converts string to an array by using given delimeter */
char amountOfSpaces(char* line); /*this function returns the amount of spaces */


/*
    the function return new list of instructions from a file.
*/
instNode* buildInstructionsList(FILE *insFile)
{
    char line[MAX_LINE_LEN] ={0};/*varible for reading the lines.*/
    instNode *head = NULL;
    instNode *pos = NULL;
    while (fgets(line, MAX_LINE_LEN, insFile))
    {
        instNode *node = malloc(sizeof(instNode));
        trimSpace(line);
        if(isBlankOrCommentLine(line))
            continue;
        node->amountOfWords=amountOfSpaces(line)+1;
        node->words = malloc(sizeof(char**) * node->amountOfWords);
        convertStringToArray(line, " \t",node->words);

        node->next =NULL;

        if(head == NULL){  
            pos = head = node;
        } else {
            pos = pos->next = node;
        }
    }

    return head;
}

/*
    Build the methods struct.
*/
methods* buildMethods()
{
    methods *strc;
    strc = malloc(sizeof(methods*));
    strc->name = malloc(sizeof(char**)*METHODS_AMOUNT);
    strc->name[0]="mov";
    strc->name[1]="cmp";
    strc->name[2]="add";
    strc->name[3]="sub";
    strc->name[4]="lea";
    strc->name[5]="clr";
    strc->name[6]="not";
    strc->name[7]="inc";
    strc->name[8]="dec";
    strc->name[9]="jmp";
    strc->name[10]="bne";
    strc->name[11]="jsr";
    strc->name[12]="red";
    strc->name[13]="prn";
    strc->name[14]="rts";
    strc->name[15]="stop";
    
    strc->funct = malloc(sizeof(char*)*METHODS_AMOUNT);
    strc->funct[0]=0;
    strc->funct[1]=0;
    strc->funct[2]=10;
    strc->funct[3]=11;
    strc->funct[4]=0;
    strc->funct[5]=10;
    strc->funct[6]=11;
    strc->funct[7]=12;
    strc->funct[8]=13;
    strc->funct[9]=10;
    strc->funct[10]=11;
    strc->funct[11]=12;
    strc->funct[12]=0;
    strc->funct[13]=0;
    strc->funct[14]=0;
    strc->funct[15]=0;
    
    strc->opcode = malloc(sizeof(char*)*METHODS_AMOUNT);
    strc->opcode[0]=0;
    strc->opcode[1]=1;
    strc->opcode[2]=2;
    strc->opcode[3]=2;
    strc->opcode[4]=4;
    strc->opcode[5]=5;
    strc->opcode[6]=5;
    strc->opcode[7]=5;
    strc->opcode[8]=5;
    strc->opcode[9]=9;
    strc->opcode[10]=9;
    strc->opcode[11]=9;
    strc->opcode[12]=12;
    strc->opcode[13]=13;
    strc->opcode[14]=14;
    strc->opcode[15]=15;

    return strc;
}

/*
    The function return the index of method.
    if not exist return an error.
*/
char indxOfMethod(methods *methods,char *method)
{
    char i;
    for(i=0;i<METHODS_AMOUNT;i++)
    {
        if(strcmp(*((methods->name)+i),method)==0)
            return i;
    }
    return METHOD_NOT_FOUND;
}


void trimSpace(char *str)
{
  char *p;
  size_t len = strlen(str);
  for (p = str + len - 1; isspace (*p); --p) ;
  p[1] = '\0';
  for (p = str; isspace (*p); ++p) ;
  memmove (str, p, len - (size_t) (p - str) + 1);

}

/*
    convert a string to array by delimeter
*/
void convertStringToArray(char* str, char *delim ,char** arr)
{
    int i;
    char *pWord;
    /* split the elements by space delimeter */ 
    char *cloneStr = malloc(sizeof(char*)*strlen(str));
    strcpy(cloneStr,str);
    pWord=strtok(cloneStr,delim);
    i=0;
    while(pWord!=NULL)
    {
        arr[i] = malloc(sizeof(char*));
        strcpy(arr[i++],pWord);
        pWord=strtok(NULL,delim);
    }
}

char amountOfSpaces(char* line){
  int i;
  char amountOfSpaces=0; 
  for(i=0;line[i];i++) /* count amount of spaces */ 
        if(line[i]==' ')
             amountOfSpaces++;
  return amountOfSpaces;           
}

/*
    return amount of characters of given character c in string.
*/
int amountOfChars(char* str, char c){
  int i;
  char amount=0; 
  for(i=0;str[i];i++) /* count amount of given c */ 
        if(str[i]==c)
             amount++;
  return amount;           
}


/*
    return a substring from m to n (not including n) position.
*/
char* substr(char *src, int m, int n)
{
    int len, i;
    char *dest;

    len = n - m;
 
    dest = (char*)malloc(sizeof(char) * (len + 1));
 
    for (i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
 
    *dest = '\0';
 
    return dest - len;
}

/*
    The function create the ob,ext and ent files.
*/
void createFiles(exportFile *file)
{
    FILE *obFile;
  
    memoryNode *memoryPos =file->memoryImage->head;
    int i;
    char *extFileName,*entFileName,*obFileName;

    obFileName = malloc(sizeof(char) * strlen(file->fileName));
    entFileName = malloc(sizeof(char) * strlen(file->fileName));
    extFileName = malloc(sizeof(char) * strlen(file->fileName));
   
    strcpy(obFileName,file->fileName);
    strcpy(entFileName,file->fileName);
    strcpy(extFileName,file->fileName);

    strcat(obFileName,".ob");
    strcat(entFileName,".ent");
    strcat(extFileName,".ext");

    obFile=fopen(obFileName,"w+");
    fprintf(obFile,"\t%d %d\n",file->ICF,file->DCF);
    while(memoryPos!=NULL)
    {
        fprintf(obFile,"0%d %03X %c\n",memoryPos->adress,memoryPos->value & 0xfff,memoryPos->type);
        memoryPos=memoryPos->next;
    }
    fclose(obFile);

    obFile=fopen(extFileName,"w+");
    for (i = 0; i < file->outsource->amountExterns; i++)
    {
        fprintf(obFile,"%s 0%d\n",file->outsource->arrExtern[i]->name,file->outsource->arrExtern[i]->address);
    }
    fclose(obFile);

    obFile=fopen(entFileName,"w+");
    for (i = 0; i < file->outsource->amountEntries; i++)
    {
        fprintf(obFile,"%s 0%d\n",file->outsource->arrEntry[i]->name,file->outsource->arrEntry[i]->address);
    }
    fclose(obFile);

}

/*
    The function return the index of character in a string
*/
int char_index(char c, char *string) {
    int i;
    for (i = 0; string[i] != '\0'; i++)
        if (string[i] == c)
            return i;

    return ERROR_ARGUMENT_NOT_VALID;
}

/*
    free all the structs
*/
void freeAllData(exportFile *file)
{
    freeMemoryImage(file->memoryImage);
    freeSymbolTable(file->symbolTable);
    freeOutsourceData(file->outsource);
}