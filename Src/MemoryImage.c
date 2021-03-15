#include "../Headers/Structs.h"
#include "../Headers/UtilsFuncs.h"
#include "../Headers/Constants.h"
#include "../Headers/MemoryImage.h"
#include "../Headers/Validations.h"
#include <stdlib.h>
#include <string.h>
memoryImageList* initMemoryImageList()
{
    memoryImageList * list = (memoryImageList*)malloc(sizeof(memoryImageList*));
    list->head = NULL;
    list->last = NULL; 
    return list;
}

memoryNode* createMemoryImageNode(int adress, int value, char type)
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
        char *str = substr(data,1,strlen(data)-1); /*remove "" from the data */
        while(i < strlen(str))
        {
            addNewMemoryNode(list, createMemoryImageNode(startAddress+i,(int)str[i],'A'));
            i++;
        }
        addNewMemoryNode(list, createMemoryImageNode(startAddress+i,0,'A'));    
    }
    else if(strcmp(type,".data")==0)
    {
        int i;
        char **arr;
        int n = amountOfChars(data,',');
        arr = malloc(sizeof(char**)*(n+1));
        convertStringToArray(data, ",", arr);
        if(n==0) 
            addNewMemoryNode(list, createMemoryImageNode(startAddress,atoi(arr[0]),'A'));
        else 
            for(i=0;i<n;i++)
            {
                addNewMemoryNode(list, createMemoryImageNode(startAddress+i,atoi(arr[i]),'A'));
            }
    }
}

/*TODO NEED TO BE REMOVED!!*/
void printMemoryList(memoryImageList *list)
{
    memoryNode* tmp;
    memoryNode* head = list->head;
    unsigned char *binStr = malloc(sizeof(unsigned char) * 12);
    short n;
    char i;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        n = tmp->value;
        i=0;
        while (i<12) {
            if (n & 1)
                *(binStr+i)='1';
            else
                *(binStr+i)='0';
            n >>= 1;
            i++;
        }
        printf("%d, %#06hx ",tmp->adress,tmp->value);
        for(i=11;i>=0;i--)
            printf("%c",*(binStr+i));
        printf(" %c\n",tmp->type);
    }
}

int getCodeLine(methods* methods, char *method ,char **operands, char nOfOperands)
{
    char methodIndex = indxOfMethod(methods, method);
    char opcode = methods->opcode[(unsigned char)methodIndex];
    char funct = methods->funct[(unsigned char)methodIndex];
    int res=0;
    if(methodIndex==METHOD_NOT_FOUND) return METHOD_NOT_FOUND;
    /*Build the opcode*/
    res = (opcode+res)<<4; 
    
    /*Build the opcode*/
    res = funct+res;
    
    if(nOfOperands==0) 
        res<<=4;
    else 
        if(nOfOperands==1) 
        {
            addresingType type = checkTypeOfAddressingModes(*(operands));
            res<<=2;
            if(type == ERROR_ARGUMENT_NOT_VALID) 
                return ERROR_ARGUMENT_NOT_VALID;
            res=(res<<2) + type;
        }
        else 
            if(nOfOperands==2)
            {
                char i = 0;
                for(; i < 2; i++)
                {
                    addresingType type = checkTypeOfAddressingModes(*(operands+i));
                    if(type == ERROR_ARGUMENT_NOT_VALID) 
                        return ERROR_ARGUMENT_NOT_VALID;
                    res=(res<<2) + type;
                }
            }
    return res;
}

memoryNode* createOperandNodeForMemory(int address,char *operand)
{
    addresingType type = checkTypeOfAddressingModes(operand);
    switch (type)
    {
    case immediate:
        return createMemoryImageNode(address,atoi(substr(operand,1,strlen(operand))),'A');
        break;
    case direct:
        return createMemoryImageNode(address,0,'?');
        break;
    case relative:
        return createMemoryImageNode(address,0,'L');
        break;
    case register_direct:
        return createMemoryImageNode(address,(int)(1<<(operand[1] - '0')),'A');
        break;
    default:
        return NULL;
    }
}
