//
// Created by jazzzy on 10/22/16.
//

#include <stdio.h>
#include "defineParser.h"
#include "../symbolTable/symbolTable.h"
#include <stdlib.h>
#include <string.h>

void parseReservedWords(symbolTable **oSymbolTable, char *pathToDefineFile) {

    FILE *file = fopen(pathToDefineFile, "r");       //Open the file
    char line[256];                                 //Save space for a line, should not be longer than 256


    while (fgets(line, sizeof(line), file)) {
        char defBuf[64];
        int LexCompBuf;
        char resWordBuf[64];
        sscanf(line, "#define %[^ ] %d //## %[^ \n]\n", defBuf, &LexCompBuf, resWordBuf);


        char *key = (char *) malloc((strlen(resWordBuf) + 1) * sizeof(char));
        int i = 0;
        for (i = 0; i < strlen(resWordBuf); i++) {
            key[i] = resWordBuf[i];
        }
        key[strlen(resWordBuf)] = '\0';

        symbolData *msymbolData = (symbolData *) malloc(sizeof(symbolData));
        msymbolData->lexicalComponent = LexCompBuf;
        addElement(((*oSymbolTable)->reserved), key, (void *) msymbolData);
        //printf("RESERVED WORD DATA: DEFINED [%s], LEXICAL COMPONENT [%d], STRING TO DETECT [%s], LENGTH: [%d]\n", defBuf, msymbolData->lexicalComponent, key,strlen(key));
    }

    fclose(file);


}