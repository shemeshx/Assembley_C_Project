#ifndef SECONDTRANSITIONH
#define SECONDTRANSITIONH
#include "Structs.h"

/*
    The second transition function gets a string of the file name .as.
    The function is performing the second part of the algorithm that discribed in the instructions.
    The function returns a struct that contain all the data to create the files.
*/
exportFile* secondTransition(instNode *listOfInstructions,char* fileName ,symbolTableList *symbolTable, memoryImageList *memoryImageList, int ICF, int DC,boolean errorFlag);

#endif