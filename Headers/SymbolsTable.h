#ifndef SYMBOLSTABLEH
#define SYMBOLSTABLEH

#include "Structs.h"
/*
    This section handles the symbol table.
    the functions are handle all funcitionality of symbol table.
*/

/*
    initialize the symbol table as list.
*/
symbolTableList* initSymbolTable();

/*
    the function add new node for the list.
*/
void addNewSymbol(symbolTableList *, symbolNode *);

/*
    return a new stucrt object of symbol node.
*/
symbolNode* createSymbolNode(char *, int, char *);

/*
    free the list.
*/
void freeSymbolTable(symbolTableList *);

/*TODO - remove*/
void printSymbolList(symbolTableList *list); /*TODO NEED TO BE REMOVED!!*/

/*
    Checks if a label is exists in the symbol table.
*/
boolean isExistLabel(symbolTableList *list,char* label);

/*
    Add the entry attribute to a symbol.
*/
void addEntryAttrToLabel(symbolTableList *list, char* label);

/*
    Gets a symbol node by a give name.
*/
symbolNode* getSymbolNodeByName(symbolTableList *list, char* label);
#endif