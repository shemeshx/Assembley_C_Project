#include "../Headers/Structs.h"
#include "../Headers/Constants.h"
#include "../Headers/EntryAndExtern.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
outsourceData* initOutsourceData()
{
    outsourceData *data = malloc(sizeof(outsourceData));
    data->arrEntry=malloc(sizeof(entryVal*));
    data->arrExtern=malloc(sizeof(externVal*));
    data->amountEntries=0;
    data->amountExterns=0;
    return data;
}

void addOutsourceData(outsourceData* obj ,outsourceType type,char *label,int address)
{
    
    switch (type)
    {
    case Extern:
        obj->amountExterns++;
        if(obj->amountExterns>1)
            obj->arrExtern=realloc(obj->arrExtern,sizeof(externVal*)*obj->amountExterns);
        obj->arrExtern[obj->amountExterns-1]=malloc(sizeof(externVal));
        obj->arrExtern[obj->amountExterns-1]->name = (char*)malloc(sizeof(char)*strlen(label));
        strcpy(obj->arrExtern[obj->amountExterns-1]->name,label);
        obj->arrExtern[obj->amountExterns-1]->address = address;
        break;
    case Entry:
        obj->amountEntries++;
        if(obj->amountEntries>1)
            obj->arrEntry=realloc(obj->arrEntry,sizeof(entryVal*)*obj->amountEntries);
        obj->arrEntry[obj->amountEntries-1]=malloc(sizeof(entryVal));
        obj->arrEntry[obj->amountEntries-1]->name = (char*)malloc(sizeof(char)*strlen(label));
        strcpy(obj->arrEntry[obj->amountEntries-1]->name,label);
        obj->arrEntry[obj->amountEntries-1]->address = address;
        break;
    }
}

void freeOutsourceData(outsourceData *outsourceData)
{
    free(outsourceData);
}
/*TODO - remove the function*/
void printOutsources(outsourceData *data)
{
    int i;
    printf("externs:\n");
    for (i = 0; i < data->amountExterns; i++)
    {
        printf("%s %d\n",data->arrExtern[i]->name,data->arrExtern[i]->address);

    }
    printf("\nentries:\n");
    for (i = 0; i < data->amountEntries; i++)
    {
        printf("%s %d\n",data->arrEntry[i]->name,data->arrEntry[i]->address);
    }
}


void setEntries(outsourceData* obj, symbolTableList *symbolTable)
{
    symbolNode *symbolNode = symbolTable->head;
    while(symbolNode!=NULL)
    {
        int i;
        for (i = 0; i < symbolNode->nOfAtt; i++)
        {
            if(strcmp(symbolNode->attributes[i],"entry")==0)
                addOutsourceData(obj,Entry,symbolNode->symbol,symbolNode->value);
        }
        symbolNode=symbolNode->next;
    }
}