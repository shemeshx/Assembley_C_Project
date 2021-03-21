#ifndef ENTRYANDEXTERNH
#define ENTRYANDEXTERNH

outsourceData* initOutsourceData();
void addOutsourceData(outsourceData *obj,outsourceType type,char *label,int address);
void freeOutsourceData(outsourceData *outsourceData);
void printOutsources(outsourceData *data); /*TODO - remove*/
void setEntries(outsourceData* obj, symbolTableList *symbolTable);
#endif