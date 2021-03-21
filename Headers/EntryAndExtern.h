#ifndef ENTRYANDEXTERNH
#define ENTRYANDEXTERNH

/*
    The functionality of outsource data (Entry or extern goes here).
    The data saves in arrays - one for entries and one for extrens datas.
*/


/*  
    initialize the structure. return an initialized struct.
*/
outsourceData* initOutsourceData(); 

/*
    adding an element for the outsource data by getting the structure obj, 
    the type (extern or entry), the name of the label and address of the location in the code.
*/
void addOutsourceData(outsourceData *obj,outsourceType type,char *label,int address);

/*
    free the memory of the outsource object.
*/
void freeOutsourceData(outsourceData *outsourceData);
void printOutsources(outsourceData *data); /*TODO - remove*/

/*
    set the entries in the array.
    the function get the outsource object and the symbol table.
    the fucntion creates the relevant data in the outsource object.
*/
void setEntries(outsourceData* obj, symbolTableList *symbolTable);
#endif