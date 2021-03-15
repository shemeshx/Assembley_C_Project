#ifndef SYMBOLSTABLEH
#define SYMBOLSTABLEH

#include "Structs.h"

symbolTableList* initSymbolTable();
void addNewSymbol(symbolTableList *, symbolNode *);
symbolNode* createSymbolNode(char *, int, char *);
void freeSymbolTable(symbolTableList *);
void printSymbolList(symbolTableList *list); /*TODO NEED TO BE REMOVED!!*/
#endif