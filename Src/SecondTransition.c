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
#include "../Headers/SecondTransition.h"
int secondTransition(instNode *listOfInstructions, symbolTableList *symbolTable, memoryImageList *memoryImageList)
{
    instNode* instPos = listOfInstructions;
    memoryNode* memoryNode = memoryImageList->head;
    int startIndex=0;
    printf("\n\t\tsecond transition started \n\n");
    while(instPos != NULL)
    {
        if(isLabel(instPos->words[startIndex]))
            startIndex++;
        if(strcmp(instPos->words[startIndex],".extern") == 0 || 
           strcmp(instPos->words[startIndex],".string") == 0 ||
           strcmp(instPos->words[startIndex],".data") == 0)
                goto STEP1;
        if(strcmp(instPos->words[startIndex],".entry") == 0)
        {
            if(!isExistLabel(symbolTable,instPos->words[startIndex+1]))
            {
                perror("symbol not found when try to add entry attribute!");
                return ERROR_ARGUMENT_NOT_VALID;
            }
            addEntryAttrToLabel(symbolTable,instPos->words[startIndex+1]);
            goto STEP1;    
        }
        else
        {
            int i;
            char** operands;
            struct memoryNode *tmpMemoryNode = memoryNode->next;
            int NofOperands = amountOfChars(instPos->words[instPos->amountOfWords-1],',')+1;

            if(isMethod(instPos->words[instPos->amountOfWords-1])) goto STEP1;

            operands = malloc(sizeof(char**)* (NofOperands+1));
            convertStringToArray(instPos->words[instPos->amountOfWords-1] ,"," ,operands);
            for (i = 0; i < NofOperands; i++, tmpMemoryNode=tmpMemoryNode->next)
            {
                struct symbolNode *currSymbol;
                if(tmpMemoryNode->type=='?' || tmpMemoryNode->type=='L')
                {
                    switch (tmpMemoryNode->type)
                    {
                    case '?':
                        currSymbol = getSymbolNodeByName(symbolTable,operands[i]);
                        if(strcmp(currSymbol->attributes[0],"external")==0)
                            tmpMemoryNode->type='E';
                        else
                            tmpMemoryNode->type='R';
                        tmpMemoryNode->value=currSymbol->value;
                        break;
                    case 'L':
                        currSymbol = getSymbolNodeByName(symbolTable,substr(operands[i],1,strlen(operands[i])));
                        tmpMemoryNode->type='A';
                        tmpMemoryNode->value = currSymbol->value - (memoryNode->adress + 1);
                        break;
                    }
                }
            }
            for (i = 0; i < NofOperands; i++){
                memoryNode = memoryNode->next;
            }
        }
        STEP1:startIndex=0;
        instPos=instPos->next;
        memoryNode=memoryNode->next;
    }
    printf("\n\n");
    printSymbolList(symbolTable);
    printf("\n\n");
    printMemoryList(memoryImageList);

    freeSymbolTable(symbolTable);
    freeMemoryImage(memoryImageList);
    return EXIT_SUCCESS;
}