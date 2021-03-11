/*This file contain the first transition method.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/Constants.h"
#include "../Headers/Structs.h"
#include "../Headers/UtilsFuncs.h"
#include "../Headers/Validations.h"
#include "../Headers/SymbolsTable.h"
#include "../Headers/MemoryImage.h"
int firstTransition (char *fileName)
{
    int IC=100,DC=0; /*IC - Instructions counter, DC - Data counter.*/
    FILE *insFile; /*Instructions file pointer.*/ 
    instNode *listOfInstructions;
    instNode *instPos;
    boolean labelFlag;
    symbolNode *symbolNode;
    symbolTableList *symbolTable=NULL;
    struct memoryNode *memoryNode;
    memoryImageList *memoryImageList=NULL;
    methods* methods;
    char methodIndex;
    char NofOperands;
    char** operands;

    symbolTable = initSymbolTable();
    memoryImageList = initMemoryImageList();
    methods = buildMethods();
    
    if((insFile=fopen(fileName,"r"))==NULL)
    {
        perror("cannot open file!");
        return EXIT_FAILURE;
    }

    listOfInstructions = buildInstructionsList(insFile);
    instPos = listOfInstructions;
    while(instPos!=NULL)
    {
        if(isLabel(instPos->words[0]))
        {
            labelFlag=true;
        }
        if(isDataAllocation(instPos->words[1]))
        {
            if(labelFlag)
            {   
                symbolNode = createSymbolNode(instPos->words[0], DC, instPos->words[1]);
                addNewSymbol(symbolTable,symbolNode);
                addAllocationDataToMemoryImage(memoryImageList, instPos->words[1], instPos->words[2], DC);
                if(strcmp(instPos->words[1],".string")==0) DC = DC + strlen(instPos->words[2]) + 1;
                else if(strcmp(instPos->words[1],".data")==0) DC = DC + amountOfChars(instPos->words[2], ',') + 1;
                memoryNode = createMemoryImageNode(DC,123,'A');
                addNewMemoryNode(memoryImageList,memoryNode);
            }
            else  /*no label*/
            {
                addAllocationDataToMemoryImage(memoryImageList, instPos->words[0], instPos->words[1], DC);
                if(strcmp(instPos->words[1],".string")==0) DC = DC + strlen(instPos->words[1]) + 1;
                else if(strcmp(instPos->words[1],".data")==0) DC = DC + amountOfChars(instPos->words[1], ',') + 1;
            }
            goto STEP2;
        }
        else if(isExternalOrEntry(instPos->words[0]))
        {
            if(strcmp(instPos->words[0],".entry")==0)
                goto STEP2;
            else /*.extern step...*/
            {
                symbolNode = createSymbolNode(instPos->words[1], 0, ".external");
                addNewSymbol(symbolTable,symbolNode);
                goto STEP2;
            }
        }
        /* step 11 */
        if(labelFlag)
        {
            symbolNode = createSymbolNode(instPos->words[0], IC, ".code");
            addNewSymbol(symbolTable,symbolNode);
        }
        methodIndex = indxOfMethod(methods,instPos->words[labelFlag]);/* step 12 */
        if (methodIndex==METHOD_NOT_FOUND)
        {   
           perror("method not exists!!!");
            return EXIT_FAILURE;
        }
        /* step 13 */
        NofOperands = (char)amountOfChars(instPos->words[labelFlag+1],',') + 1;
        operands = malloc(sizeof(char**)* NofOperands);
        convertStringToArray(instPos->words[labelFlag+1] ,"," ,operands);

        STEP2:labelFlag=false;
        instPos=instPos->next;
    }
    printMemoryList(memoryImageList);
    printf("\n\n");
    printSymbolList(symbolTable);
    /*TODO - move to other transition*/
    freeSymbolTable(symbolTable);
    freeMemoryImage(memoryImageList);
    if (fclose(insFile))
    {
        perror("cannot close file!");
        return EXIT_FAILURE;
    }

    return(EXIT_SUCCESS);
}

