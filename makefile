HEADERS=Headers/
SRC=Src/
myprog:main.o firstTransition.o UtilsFuncs.o Validations.o SymbolsTable.o MemoryImage.o
	gcc -g -ansi -Wall -pedantic main.o Validations.o UtilsFuncs.o SymbolsTable.o firstTransition.o MemoryImage.o -o myprog 
	rm main.o firstTransition.o UtilsFuncs.o Validations.o SymbolsTable.o MemoryImage.o
main.o: ${SRC}main.c ${HEADERS}FirstTransition.h
	gcc -c -ansi -Wall -pedantic ${SRC}main.c -o main.o
Validations.o: ${SRC}Validations.c ${HEADERS}Constants.h ${HEADERS}Structs.h
	gcc -c -ansi -Wall -pedantic ${SRC}Validations.c -o Validations.o
SymbolsTable.o: ${HEADERS}Constants.h ${HEADERS}Structs.h ${HEADERS}UtilsFuncs.h
	gcc -c -ansi -Wall -pedantic ${SRC}SymbolsTable.c -o SymbolsTable.o
MemoryImage.o: ${HEADERS}Constants.h ${HEADERS}Structs.h ${HEADERS}UtilsFuncs.h
	gcc -c -ansi -Wall -pedantic ${SRC}MemoryImage.c -o MemoryImage.o
UtilsFuncs.o: ${SRC}UtilsFuncs.c ${HEADERS}Constants.h ${HEADERS}Structs.h ${HEADERS}UtilsFuncs.h
	gcc -c -ansi -Wall -pedantic ${SRC}UtilsFuncs.c -o UtilsFuncs.o
firstTransition.o: ${SRC}FirstTransition.c ${HEADERS}Constants.h ${HEADERS}FirstTransition.h ${HEADERS}UtilsFuncs.h
	gcc -c -ansi -Wall -pedantic ${SRC}FirstTransition.c -o firstTransition.o

