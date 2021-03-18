#ifndef SYMBOLSTABLEH
#define SYMBOLSTABLEH

#include "Structs.h"

symbolTableList* initSymbolTable();
void addNewSymbol(symbolTableList *, symbolNode *);
symbolNode* createSymbolNode(char *, int, char *);
void freeSymbolTable(symbolTableList *);
void printSymbolList(symbolTableList *list); /*TODO NEED TO BE REMOVED!!*/
boolean isExistLabel(symbolTableList *list,char* label);
void addEntryAttrToLabel(symbolTableList *list, char* label);
symbolNode* getSymbolNodeByName(symbolTableList *list, char* label);
#endif