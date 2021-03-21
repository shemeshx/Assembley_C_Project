HEADERS=Headers/
SRC=Src/
assembler:assembler.o firstTransition.o SecondTransition.o UtilsFuncs.o Validations.o SymbolsTable.o MemoryImage.o EntryAndExtern.o
	gcc -g -ansi -Wall -pedantic assembler.o Validations.o UtilsFuncs.o SymbolsTable.o firstTransition.o MemoryImage.o SecondTransition.o EntryAndExtern.o -o assembler 
	rm assembler.o firstTransition.o UtilsFuncs.o Validations.o SymbolsTable.o MemoryImage.o SecondTransition.o EntryAndExtern.o
assembler.o: ${SRC}assembler.c ${HEADERS}FirstTransition.h
	gcc -c -ansi -Wall -pedantic ${SRC}assembler.c -o assembler.o
Validations.o: ${SRC}Validations.c ${HEADERS}Constants.h ${HEADERS}Structs.h
	gcc -c -ansi -Wall -pedantic ${SRC}Validations.c -o Validations.o
SymbolsTable.o: ${HEADERS}Constants.h ${HEADERS}Structs.h ${HEADERS}UtilsFuncs.h
	gcc -c -ansi -Wall -pedantic ${SRC}SymbolsTable.c -o SymbolsTable.o
MemoryImage.o: ${HEADERS}Constants.h ${HEADERS}Structs.h ${HEADERS}UtilsFuncs.h
	gcc -c -ansi -Wall -pedantic ${SRC}MemoryImage.c -o MemoryImage.o
UtilsFuncs.o: ${SRC}UtilsFuncs.c ${HEADERS}Constants.h ${HEADERS}Structs.h ${HEADERS}UtilsFuncs.h ${HEADERS}Validations.h
	gcc -c -ansi -Wall -pedantic ${SRC}UtilsFuncs.c -o UtilsFuncs.o
EntryAndExtern.o: ${SRC}EntryAndExtern.c ${HEADERS}Constants.h ${HEADERS}Structs.h ${HEADERS}EntryAndExtern.h 
	gcc -c -ansi -Wall -pedantic ${SRC}EntryAndExtern.c -o EntryAndExtern.o
SecondTransition.o: ${SRC}SecondTransition.c ${HEADERS}Constants.h ${HEADERS}UtilsFuncs.h ${HEADERS}SymbolsTable.h ${HEADERS}SecondTransition.h
	gcc -c -ansi -Wall -pedantic ${SRC}SecondTransition.c -o SecondTransition.o
firstTransition.o: ${SRC}FirstTransition.c ${HEADERS}Constants.h ${HEADERS}FirstTransition.h ${HEADERS}UtilsFuncs.h ${HEADERS}SymbolsTable.h 
	gcc -c -ansi -Wall -pedantic ${SRC}FirstTransition.c -o firstTransition.o

