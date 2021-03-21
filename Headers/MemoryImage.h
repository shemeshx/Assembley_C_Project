#ifndef MEMORYIMAGEH
#define MEMORYIMAGEH
/*
    This section handles the memory image.
    the functions are handle all funcitionality of memory image.
*/

/*
    initialize the memory image as list.
*/
memoryImageList* initMemoryImageList();

/*
    return a new stucrt object of memory node.
*/
memoryNode* createMemoryImageNode(int adress, int value, char type);

/*
    the function add new node for the list.
*/
void addNewMemoryNode(memoryImageList *list, memoryNode *newNode);

/*
    free the list.
*/
void freeMemoryImage(memoryImageList *list);

/*
    add allocation data to memory image (string or data type). 
*/
void addAllocationDataToMemoryImage(memoryImageList *list , char *type, char *data, int startAddress);

/*TODO - REMOVE*/
void printMemoryList(memoryImageList *list);/*TODO NEED TO BE REMOVED!!*/

/*
    return a number that represend a funct+opcode+sourcetaget+destinition targer.
*/
int getCodeLine(methods* methods, char *method, char **operands, char nOfOperands);

/*
    return a node by operand and adress.
*/
memoryNode* createOperandNodeForMemory(int address,char *operand);
#endif