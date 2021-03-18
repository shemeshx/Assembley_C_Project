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
#include "../Headers/SecondTransition.h"
int firstTransition (char *fileName)
{
    int lineN=1;

    int IC=100,DC=0; /*IC - Instructions counter, DC - Data counter.*/
    FILE *insFile; /*Instructions file pointer.*/ 
    instNode *listOfInstructions;
    instNode *instPos;
    boolean labelFlag;
    symbolNode *symbolNode;
    symbolTableList *symbolTable=NULL;
    memoryNode *memoryNode;
    memoryImageList *memoryImageList=NULL;
    methods* methods;
    char methodIndex;
    char NofOperands;
    char** operands;
    char i;

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
        if(isDataAllocation(instPos->words[0]) || isDataAllocation(instPos->words[1]))
        {
            if(labelFlag)
            {   
                symbolNode = createSymbolNode(instPos->words[0], IC, instPos->words[1]);
                addNewSymbol(symbolTable,symbolNode);
                addAllocationDataToMemoryImage(memoryImageList, instPos->words[1], instPos->words[2], IC);
                if(strcmp(instPos->words[1],".string")==0)
                {   
                    int length = strlen(substr(instPos->words[2],1,strlen(instPos->words[2])));
                    DC = DC + length;
                    IC = IC + length;
                }
                else 
                    if(strcmp(instPos->words[1],".data")==0)
                    {
                        int length =  amountOfChars(instPos->words[2], ',');
                        if (length==0)
                            length = 1;
                        else
                            length++;
                        DC = DC + length;
                        IC = IC + length;
                    }          
            }
            else  /*no label*/
            {
                addAllocationDataToMemoryImage(memoryImageList, instPos->words[0], instPos->words[1], IC);
                if(strcmp(instPos->words[0],".data")==0) 
                {
                    int length =  amountOfChars(instPos->words[1], ',') + 1;
                    DC = DC + length;
                    IC = IC + length;
                }
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
        
        switch (instPos->amountOfWords)
        {
        case 1:
            perror("Wrong number of line words.");
            return EXIT_FAILURE;
            break;
        case 2: /*there are two options -  */
                if(labelFlag) /*1. Label with method (no operands)*/
                {
                    memoryNode = createMemoryImageNode(IC,getCodeLine(methods, instPos->words[1] ,NULL, 0),'A');
                    addNewMemoryNode(memoryImageList,memoryNode);
                    IC++;
                }
                else /*2.method with operands (no label)*/
                {
                    NofOperands = (char)amountOfChars(instPos->words[instPos->amountOfWords-1],',')+1;
                    operands = malloc(sizeof(char**)* NofOperands);
                    convertStringToArray(instPos->words[instPos->amountOfWords-1] ,"," ,operands);
                    memoryNode = createMemoryImageNode(IC,getCodeLine(methods, instPos->words[0] ,operands, NofOperands),'A');
                    addNewMemoryNode(memoryImageList,memoryNode);
                    IC++;
                    for (i = 0 ; i < NofOperands; i++)
                    {
                        memoryNode = createOperandNodeForMemory(IC++,*(operands+i));
                        addNewMemoryNode(memoryImageList,memoryNode);
                    }
                }
            break;
        case 3: /* line contain -> label: method operands*/
            NofOperands = (char)amountOfChars(instPos->words[instPos->amountOfWords-1],',')+1;
            operands = malloc(sizeof(char**)* NofOperands);
            convertStringToArray(instPos->words[instPos->amountOfWords-1] ,"," ,operands);
            memoryNode = createMemoryImageNode(IC,getCodeLine(methods, instPos->words[labelFlag] ,operands, NofOperands),'A');
            addNewMemoryNode(memoryImageList,memoryNode);
            IC++;
            for (i = 0 ; i < NofOperands; i++)
            {
                memoryNode = createOperandNodeForMemory(IC++,*(operands+i));
                addNewMemoryNode(memoryImageList,memoryNode);
            }
            break;
        }

        STEP2:labelFlag=false;
        instPos=instPos->next;
        lineN++;
    }
    
    
    printMemoryList(memoryImageList);
    printf("\n\n");
    printSymbolList(symbolTable);
    


    /*TODO - move to other transition*/
    
    if (fclose(insFile))
    {
        perror("cannot close file!");
        return EXIT_FAILURE;
    }
    
    return secondTransition(listOfInstructions,symbolTable,memoryImageList);

}

