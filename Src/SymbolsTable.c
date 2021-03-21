#include "../Headers/Structs.h"
#include "../Headers/UtilsFuncs.h"
#include "../Headers/Constants.h"
#include "../Headers/Validations.h"
#include <stdlib.h>
#include <string.h>
/*
    This section handles the symbol table.
    the functions are handle all funcitionality of symbol table.
*/

/*
    initialize the symbol table as list.
*/
symbolTableList* initSymbolTable()
{
    symbolTableList* list = (symbolTableList*)malloc(sizeof(symbolTableList*));
    list->head = NULL;
    list->last = NULL; 
    return list;
}

/*
    return a new stucrt object of symbol node.
*/
symbolNode* createSymbolNode( char *symbol, int value, char *attr)
{
    symbolNode* newSymbol=malloc(sizeof(symbolNode));
    newSymbol->symbol=malloc(sizeof(char) * strlen(symbol));
    if(isLabel(symbol))
       symbol= substr(symbol,0,strlen(symbol)-1);
    strcpy(newSymbol->symbol,symbol);
    newSymbol->value = value;
    newSymbol->nOfAtt = 1;
    newSymbol->attributes=malloc(sizeof(char**));
    newSymbol->attributes[0]=malloc(sizeof(char)* strlen(attr));
    strcpy(newSymbol->attributes[0], substr(attr,1,strlen(attr)));
    return newSymbol;
}

/*
    the function add new node for the list.
*/
void addNewSymbol(symbolTableList *list, symbolNode *newNode)
{
    if(list->head == NULL)
    {
        list->head = newNode;
        list->last = newNode;
    }  
    else
    {
        list->last->next = newNode;
        list->last = list->last->next;
    }
}

/*
    free the list.
*/
void freeSymbolTable(symbolTableList *list)
{
    symbolNode* tmp;
    symbolNode* head = list->head;
    while (head != NULL)
    {
        int i=0;
        tmp = head;
        head = head->next;
        for(;i<tmp->nOfAtt;i++) {
            free(tmp->attributes[i]);
        }
        free(tmp->attributes);
        free(tmp->symbol);
        free(tmp);
    }
}

/*TODO - remove this func when finish!*/
void printSymbolList(symbolTableList *list)
{
    symbolNode* tmp;
    symbolNode* head = list->head;
    while (head != NULL)
    {
        int i=0;
        tmp = head;
        head = head->next;
        printf("%s, %d, [",tmp->symbol,tmp->value);
        for ( i = 0; i < tmp->nOfAtt; i++)
        {
            printf("%s, ",tmp->attributes[i]);
        }
        printf("]\n");
    }
}

/*
    Checks if a label is exists in the symbol table.
*/
boolean isExistLabel(symbolTableList *list,char* label)
{
    symbolNode *pos = list->head;
    while(pos!=NULL)
    {
        if(strcmp(pos->symbol,label)==0)
            return true;
        pos=pos->next;
    }
    return false;
}

/*
    Add the entry attribute to a symbol.
*/
void addEntryAttrToLabel(symbolTableList *list, char* label)
{
    symbolNode *pos = list->head;
    
    while(pos!=NULL)
    {
        if(strcmp(pos->symbol,label)==0)
        {
            pos->attributes=realloc(pos->attributes,sizeof(char**)*(pos->nOfAtt++ + 1));
            pos->attributes[pos->nOfAtt-1] = malloc(sizeof(char*)*strlen("entry"));
            strcpy(pos->attributes[pos->nOfAtt-1],"entry");
            return;
        }
        pos=pos->next;
    }
}

/*
    Gets a symbol node by a give name.
*/
symbolNode* getSymbolNodeByName(symbolTableList *list, char* label)
{
    symbolNode *pos = list->head;
    
    while(pos!=NULL)
    {
        if(strcmp(pos->symbol,label)==0)
        {
            return pos;
        }
        pos=pos->next;
    }
    return SYMBOL_NOT_FOUND;
}
