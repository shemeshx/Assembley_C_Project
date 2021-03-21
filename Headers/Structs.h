/*
This header contains all the structs in the project.
*/ 
#ifndef STRUCTSH
#define STRUCTSH
#include "Constants.h"
typedef struct instNode { 
    /*
    This struct contain a line as node.
    Each node contains words of the line (as array) and poniter to the next node.
    */
    char **words; 
    char amountOfWords;
    struct instNode* next; 
}instNode;


typedef struct symbolNode { 
    /*
    This struct contain a symbol row in table symbos as a node.
    Each node contains symbol, value and attributes.
    */
    char *symbol; 
    int value;
    char **attributes;
    int nOfAtt;
    struct symbolNode* next; 
}symbolNode;

typedef struct symbolTableList { 
    /*
    This struct contains the symbol table as a linked list.
    There are 2 pointers - one to the head and one to the end.
    */
    symbolNode *head;
    symbolNode *last;
}symbolTableList;



typedef struct memoryNode { 
    /*
    This struct contain a memory line as a node.
    Each node contains address, value (as Hexadecimal) and type(?,A,R or E).
    */
    int adress;
    int value:12;
    char type;
    struct memoryNode* next; 
}memoryNode;

typedef struct memoryImageList { 
    /*
    This struct contains the symbol table as a linked list.
    There are 2 pointers - one to the head and one to the end.
    */
    struct memoryNode *head;
    struct memoryNode *last;
}memoryImageList;

typedef struct methods{
    /*
    This struct contains the methods (move,lea,cmp, etc...)
    */
    char **name;
    char *funct;
    char *opcode;
}methods;


typedef struct externVal{
    /*
    This struct represents a extenal value.
    */
    char* name;
    int address;
}externVal;

typedef struct entryVal{
    /*
    This struct represents a entry value.
    */
    char* name;
    int address;
}entryVal;

typedef struct outsourceData{
    /*
    This struct conatin 2 arrays of entries and externs datas.
    */
    entryVal **arrEntry;
    externVal **arrExtern;
    int amountEntries;
    int amountExterns;
}outsourceData;


typedef struct exportFile{
    /*
    The struct contain all the relevant information to create the files.
    */
    int ICF;
    int DCF;
    outsourceData *outsource;
    symbolTableList *symbolTable;
    memoryImageList *memoryImage;
    char *fileName;
}exportFile;

#endif