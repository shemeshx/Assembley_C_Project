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


void trimSpace(char *str);/*Help function to trim spaces*/
void convertLineToArray(char* line, char** arr); /* this function converts line to an array by using delimeter of space */
char amountOfSpaces(char* line); /*this function returns the amount of spaces */

instNode* buildInstructionsList(FILE *insFile)
{
    char line[MAX_LINE_LEN] ={0};/*varible for reading the lines.*/
    instNode *head = NULL;
    instNode *pos = NULL;
    while (fgets(line, MAX_LINE_LEN, insFile))
    {
        instNode *node = malloc(sizeof(instNode));
        trimSpace(line);
        node->amountOfWords=amountOfSpaces(line)+1;
        node->words = malloc(sizeof(char**) * node->amountOfWords);
        convertLineToArray(line, node->words);

        node->next =NULL;

        if(head == NULL){  
            pos = head = node;
        } else {
            pos = pos->next = node;
        }
    }

    return head;
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

void convertLineToArray(char* line, char** arr)
{
    int i;
    char *pWord;
    /* split the elements by space delimeter */ 
    pWord=strtok(line," \t");
    i=0;
    while(pWord!=NULL)
    {
        arr[i] = malloc(sizeof(char*));
        strcpy(arr[i++],pWord);
        pWord=strtok(NULL," \t");
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

char* substr(const char *src, int m, int n)
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

