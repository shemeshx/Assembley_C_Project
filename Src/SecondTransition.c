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

int secondTransition(instNode *listOfInstructions, symbolTableList *symbolTable, memoryImageList *memoryImageList)
{
    instNode* posInstr = listOfInstructions;
    boolean labelFlag=false;
    while(posInstr != NULL)
    {



        posInstr=posInstr->next;
    }
}