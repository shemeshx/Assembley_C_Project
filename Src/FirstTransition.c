/*
    This file contain the first transition method.
*/
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
exportFile* firstTransition (char *fileName)
{
    /*ICF - Instructions counter only, IC - Instructions counter of every move, DC - Data counter.*/
    int ICF=100;
    int IC=100;
    int DC=0; 

    boolean errorFlag = false;/*handle the errors*/

    int lineN=1;/*count the lines*/

    FILE *insFile; /*Instructions file pointer.*/ 

    instNode *listOfInstructions; /* List of the instructions*/
    instNode *instPos; /*pos of the instruction list*;*/

    boolean labelFlag;/*if there is a label*/

    symbolNode *symbolNode;/*node to symbol table*/
    symbolTableList *symbolTable=NULL;/*list of symbol table*/

    memoryNode *memoryNode;/*node to memory rows*/
    memoryImageList *memoryImageList=NULL;/*list of memory rows*/

    methods* methods;/*methods structure*/
    char methodIndex;/*handle the index of method*/

    /*handle the operands of a row*/
    char NofOperands;
    char** operands;
    char i;

    char *fileNameNoExt;
    fileNameNoExt = substr(fileName,0,char_index('.',fileName));

    /*initialize the structures.*/
    symbolTable = initSymbolTable();
    memoryImageList = initMemoryImageList();
    methods = buildMethods();
    

    /*open the file*/
    if((insFile=fopen(fileName,"r"))==NULL)
    {
        perror("cannot open file!\n");
        return NULL;
    }

    /*build the list from the file*/
    listOfInstructions = buildInstructionsList(insFile);
    instPos = listOfInstructions;     

    while(instPos!=NULL)
    { 
        if(isLabel(instPos->words[0])) /*step 4 - flag on*/
        {
            labelFlag=true;
        }
        /*step 5 - Is it a string or a data instruction.*/
        if(isDataAllocation(instPos->words[0]) || isDataAllocation(instPos->words[1]))
        {
            if(labelFlag)
            {/*step 6 + 7 - create a symbol node and add it to memory image*/   
                symbolNode = createSymbolNode(instPos->words[0], IC, ".data");
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
            else  /*step 7 - there is no label*/
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
        /*step 8+9 - handle external or entry instruction*/
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
        /* step 11 - add the symbol as code type*/
        if(labelFlag)
        {
            symbolNode = createSymbolNode(instPos->words[0], IC, ".code");
            addNewSymbol(symbolTable,symbolNode);
        }
        /* step 12 - search of method */
        methodIndex = indxOfMethod(methods,instPos->words[labelFlag]);
        if (methodIndex==METHOD_NOT_FOUND)
        {   
            printf("ERROR : method not exists at line %d,\n",lineN);
            errorFlag=true;
            goto STEP2;
        }

        /* step 13-16 - handle a code instructions line.*/ 
        switch (instPos->amountOfWords)
        {
        case 1:
            printf("ERROR : Wrong number of line words at line %d.\n",lineN);
            errorFlag=true;
            goto STEP2;
            break;
        case 2: /*there are two options -  */
                if(labelFlag) /*1. Label with method (no operands)*/
                {
                    memoryNode = createMemoryImageNode(IC,getCodeLine(methods, instPos->words[1] ,NULL, 0),'A');
                    addNewMemoryNode(memoryImageList,memoryNode);
                    IC++;
                    ICF++;
                }
                else /*2.method with operands (no label)*/
                {
                    NofOperands = (char)amountOfChars(instPos->words[instPos->amountOfWords-1],',')+1;
                    operands = malloc(sizeof(char**)* NofOperands);
                    convertStringToArray(instPos->words[instPos->amountOfWords-1] ,"," ,operands);
                    memoryNode = createMemoryImageNode(IC,getCodeLine(methods, instPos->words[0] ,operands, NofOperands),'A');
                    addNewMemoryNode(memoryImageList,memoryNode);
                    IC++;
                    ICF++;
                    for (i = 0 ; i < NofOperands; i++)
                    {
                        memoryNode = createOperandNodeForMemory(IC++,*(operands+i));
                        addNewMemoryNode(memoryImageList,memoryNode);
                        ICF++;
                    }
                }
            break;
        case 3: /* line contains label, method and operands*/
            NofOperands = (char)amountOfChars(instPos->words[instPos->amountOfWords-1],',')+1;
            operands = malloc(sizeof(char**)* NofOperands);
            convertStringToArray(instPos->words[instPos->amountOfWords-1] ,"," ,operands);
            memoryNode = createMemoryImageNode(IC,getCodeLine(methods, instPos->words[labelFlag] ,operands, NofOperands),'A');
            addNewMemoryNode(memoryImageList,memoryNode);
            IC++;
            ICF++;
            for (i = 0 ; i < NofOperands; i++)
            {
                memoryNode = createOperandNodeForMemory(IC++,*(operands+i));
                addNewMemoryNode(memoryImageList,memoryNode);
                ICF++;
            }
            break;
        }
        
        STEP2:labelFlag=false;
        instPos=instPos->next;
        lineN++;
    }
    
    
    /*printMemoryList(memoryImageList);
    printf("\n\n");
    printSymbolList(symbolTable);
    */

   
    /*close file*/
    if (fclose(insFile))
    {
        perror("cannot close file!\n");
        return NULL;
    }


    /*start second transition*/
    return secondTransition(listOfInstructions,fileNameNoExt,symbolTable,memoryImageList,ICF-100,DC,errorFlag);

}

