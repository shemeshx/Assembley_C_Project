#include "../Headers/Structs.h"
#include "../Headers/UtilsFuncs.h"
#include "../Headers/Constants.h"
#include <stdlib.h>
#include <string.h>
void initSymbolTable(symbolTableList *list)
{
    list = (symbolTableList*)malloc(sizeof(symbolTableList));
    list->head = NULL;
    list->last = NULL; 
}

symbolNode* createSymbolNode( char *symbol, int value, char *attr)
{
    symbolNode* newSymbol=malloc(sizeof(symbolNode));
    newSymbol->symbol=malloc(sizeof(char) * strlen(symbol));
    strcpy(newSymbol->symbol,substr(symbol,0,strlen(symbol)-1));
    newSymbol->value = value;
    newSymbol->nOfAtt = 1;
    newSymbol->attributes=malloc(sizeof(char*));
    newSymbol->attributes[0]=malloc(sizeof(char)* strlen(attr));
    strcpy(newSymbol->attributes[0], substr(attr,1,strlen(attr)));
    return newSymbol;
}

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

void freeSymbolTable(symbolTableList *list)
{
    /*TODO need to fix the free function for ALL structs!*/
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
