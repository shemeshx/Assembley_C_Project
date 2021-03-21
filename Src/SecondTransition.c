/*This file contain the second transition method.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/Constants.h"
#include "../Headers/Structs.h"
#include "../Headers/UtilsFuncs.h"
#include "../Headers/Validations.h"
#include "../Headers/SymbolsTable.h"
#include "../Headers/MemoryImage.h"
#include "../Headers/EntryAndExtern.h"
#include "../Headers/SecondTransition.h"

/*
    The second transition function gets a string of the file name .as.
    The function is performing the second part of the algorithm that discribed in the instructions.
    The function returns a struct that contain all the data to create the files.
*/
exportFile* secondTransition(instNode *listOfInstructions, char* fileName, symbolTableList *symbolTable, memoryImageList *memoryImageList, int ICF, int DC, boolean errorFlag)
{
    instNode* instPos = listOfInstructions;/*pos of the instruction list*/

    memoryNode* memoryNode = memoryImageList->head;/*node to memory rows*/

    int startIndex=0; /*if there is a label or not.*/

    outsourceData *outsourceData; /*structure of outsource data (extern or entry)*/
    
    struct symbolNode *currSymbol; /*points to current symbol by name(return by a method).*/

    /*initialize the structure.*/
    outsourceData = initOutsourceData();

    printf("\n\t\tsecond transition started \n\n");
    while(instPos != NULL)
    {
        int i;
        char** operands;
        struct memoryNode *tmpMemoryNode;
        int NofOperands;

        if(isLabel(instPos->words[startIndex])) /*step 2 - jump over the label word.*/
            startIndex++;
        /*step 3 - skip string, data or extern instructions*/
        if(strcmp(instPos->words[startIndex],".string") == 0 ||
           strcmp(instPos->words[startIndex],".data") == 0)
            goto STEP1_CODE;
        if(strcmp(instPos->words[startIndex],".extern")==0)
            goto STEP1;
        
        /*step 4+5 - for entry instruction, add attribute 'entry' to relevant symbol */
        if(strcmp(instPos->words[startIndex],".entry") == 0)
        {
            if(!isExistLabel(symbolTable,instPos->words[startIndex+1]))
            {
                printf("ERROR:symbol '%s' not found when try to add entry attribute!",instPos->words[startIndex+1]);
            }
            addEntryAttrToLabel(symbolTable,instPos->words[startIndex+1]);
            currSymbol = getSymbolNodeByName(symbolTable,instPos->words[instPos->amountOfWords-1]);
            if(currSymbol == SYMBOL_NOT_FOUND)
                printf("ERROR : symbol '%s' not declared!", instPos->words[instPos->amountOfWords-1]);
            goto STEP1;
        }
        
        /*step 6 - if there is a missing information about the 
                    memory instruction (address of label or jumping to an adress),
                    feel the relevant information.*/
        tmpMemoryNode = memoryNode->next;
        NofOperands = amountOfChars(instPos->words[instPos->amountOfWords-1],',')+1;

        /*if it is only method with no operands*/
        if(isMethod(instPos->words[instPos->amountOfWords-1])) goto STEP1_CODE;
    
        operands = malloc(sizeof(char**)* (NofOperands+1));
        convertStringToArray(instPos->words[instPos->amountOfWords-1] ,"," ,operands);
        
        for (i = 0; i < NofOperands; i++)
        {
            if(tmpMemoryNode->type=='?' || tmpMemoryNode->type=='L')
            {
                switch (tmpMemoryNode->type)
                {
                case '?': /*missing address*/
                    currSymbol = getSymbolNodeByName(symbolTable,operands[i]);
                    if(strcmp(currSymbol->attributes[0],"external")==0) /*external*/
                    {
                        tmpMemoryNode->type='E';
                        addOutsourceData(outsourceData,Extern,currSymbol->symbol,tmpMemoryNode->adress);
                    }
                    else /*not external*/
                        tmpMemoryNode->type='R';
                    tmpMemoryNode->value=currSymbol->value;
                    break;
                case 'L': /*jump to relevant address*/
                    currSymbol = getSymbolNodeByName(symbolTable,substr(operands[i],1,strlen(operands[i])));
                    tmpMemoryNode->type='A';
                    tmpMemoryNode->value = currSymbol->value - (memoryNode->adress + 1);
                    break;
                }
            }
            tmpMemoryNode=tmpMemoryNode->next;
        }
        /*go to the next relevant row by pass the operands rows in memory image.*/
        for (i = 0; i < NofOperands; i++){
            memoryNode = memoryNode->next;
        }
        STEP1_CODE:memoryNode=memoryNode->next;
        STEP1:startIndex=0;
        instPos=instPos->next;
    }

    /*set the entries*/
    setEntries(outsourceData, symbolTable);


    printSymbolList(symbolTable);
    printf("\n\n");
    printMemoryList(memoryImageList);
    printf("\n\n");
    printOutsources(outsourceData);

    /*free all the memories*/
    /*freeOutsourceData(outsourceData);
    freeSymbolTable(symbolTable);
    freeMemoryImage(memoryImageList);*/
    
    if(errorFlag)
        return NULL;
    else
        {
            exportFile *exportFile = malloc(sizeof(struct exportFile));
            exportFile->DCF = DC;
            exportFile->ICF = ICF;
            exportFile->memoryImage=memoryImageList;
            exportFile->outsource=outsourceData;
            exportFile->symbolTable=symbolTable;
            exportFile->fileName=fileName;
            return exportFile;
        }
}