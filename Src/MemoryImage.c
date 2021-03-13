#include "../Headers/Structs.h"
#include "../Headers/UtilsFuncs.h"
#include "../Headers/Constants.h"
#include "../Headers/MemoryImage.h"
#include <stdlib.h>
#include <string.h>
memoryImageList* initMemoryImageList()
{
    memoryImageList * list = (memoryImageList*)malloc(sizeof(memoryImageList*));
    list->head = NULL;
    list->last = NULL; 
    return list;
}

memoryNode* createMemoryImageNode(int adress, short value, char type)
{
    memoryNode* newMemoryNode=malloc(sizeof(memoryNode));
    newMemoryNode->adress = adress;
    newMemoryNode->value = value;
    newMemoryNode->type = type;
    
    return newMemoryNode;
}

void addNewMemoryNode(memoryImageList *list, memoryNode *newNode)
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

void freeMemoryImage(memoryImageList *list)
{
    memoryNode* tmp;
    memoryNode* head = list->head;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void addAllocationDataToMemoryImage(memoryImageList *list , char *type, char *data, int startAddress)
{
    if(strcmp(type,".string")==0)
    {
        int i = 0;
        while(i < strlen(data))
        {
            addNewMemoryNode(list, createMemoryImageNode(startAddress++,(short)data[i],'A'));
            i++;
        }
        addNewMemoryNode(list, createMemoryImageNode(startAddress++,0,'A'));    
    }
    else if(strcmp(type,".data")==0)
    {
        int i;
        char **arr;
        int n = amountOfChars(data,',');
        arr = malloc(sizeof(char**)*n);
        convertStringToArray(data, ",", arr);
        for(i=0;i<n;i++)
            addNewMemoryNode(list, createMemoryImageNode(startAddress++,atoi(arr[i]),'A'));
    }
}

/*TODO NEED TO BE REMOVED!!*/
void printMemoryList(memoryImageList *list)
{
    memoryNode* tmp;
    memoryNode* head = list->head;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        printf("%d, %#06hx, %c\n",tmp->adress,tmp->value,tmp->type);
    }
}

char insertCodeLine(methods* methods, char *method, memoryImageList *list, char **operands, char nOfOperands)
{
    char methodIndex = indxOfMethod(methods, method);
    char opcode = methods->opcode[methodIndex];
    char funct = methods->funct[methodIndex];
    char srcAddress;
    char destAdress;
    char res=0;
    char bits = AMOUNT_OF_BITS_SRC_CODE-1;
    /*Build the opcode*/
    while(bits > 7)
    {
        if(opcode&1) res = (res << 1)+1;
        else res<<=1; 
        opcode>>=1;
        bits--;
    }
    /*Build the opcode*/
    while(bits > 3)
    {
        if(funct&1) res = (res << 1)+1;
        else res<<=1; 
        funct>>=1;
        bits--;
    }
    
    
}