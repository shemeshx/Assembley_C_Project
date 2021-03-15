#ifndef MEMORYIMAGEH
#define MEMORYIMAGEH

memoryImageList* initMemoryImageList();
memoryNode* createMemoryImageNode(int adress, int value, char type);
void addNewMemoryNode(memoryImageList *list, memoryNode *newNode);
void freeMemoryImage(memoryImageList *list);
void addAllocationDataToMemoryImage(memoryImageList *list , char *type, char *data, int startAddress);
void insertCodeLine(memoryImageList *list, char methodIndex, char **operands, char nOfOperands);
void printMemoryList(memoryImageList *list);/*TODO NEED TO BE REMOVED!!*/
int getCodeLine(methods* methods, char *method, char **operands, char nOfOperands);
memoryNode* createOperandNodeForMemory(int address,char *operand);
#endif