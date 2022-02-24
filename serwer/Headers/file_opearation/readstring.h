#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#pragma once
#ifndef SERWER_READSTRING_H
#define SERWER_READSTRING_H




// funkcje odczytujaca przeslane wiadomosci od klienta
//************************************
// funkcja odpowiedzialna za podzial. Zczytana tablica wprowadzonych argumentow
char** buf_split(char* a_str, const char a_delim){
    //printf("FUNKCJA BUF_SPLIT\n");
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str; //<---poprawiony warning
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    //printf("Wprowadzony string:\t\t\t%s\n", a_str);
    /* Count how many elements will be extracted. */
    while (*tmp){
        if (a_delim == *tmp){
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);
    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;
    result = malloc(sizeof(char*) * count);

    if (result){
        size_t idx  = 0;
        char* token = strtok(a_str, delim);
        while (token){
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }

        //printf("%d\n", count);
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}


//ODCZYT PIERWSZEJ WCZYTANEJ WARTOSCI DO SPACJI I ZRZUTOWANIE JEJ NA WARTOSC NUMERYCZNA
int readCommand(char* buf, char* result[]){
    int i;
    int j;
    char* rest;
    int counter = 0;
    char** tokens;


    rest = strchr(buf, ':');
    int length_first = strlen(buf) - strlen(rest);

    //char* first = (char*)malloc(strlen((length_first) + 1) * sizeof(char));
    //char* first = strdup();
    //char* first = (char*)malloc((length_first) * sizeof(char));
    //first = ;
    char first[length_first + 1];

    strncpy(first, buf, length_first);
    first[length_first] = '\0';

    char* second_rest = rest + 1;
    second_rest[strlen(second_rest)] = '\0';

    //printf("Second_rest: %s\n", second_rest);
    //printf("Rozmiar second_rest: %d\n", strlen(second_rest));


    tokens = buf_split(second_rest, ' '); //<-- wynik tablica wskaznikow char

    //printf("Argument: %s\n", first);


    //COPY TO RESULT
    if(tokens){
        for (i = 0; *(tokens + i); i++){
            //printf("Argument: %s\n", *(tokens + i));
            result[i] = (*(tokens + i));
            //free(*(tokens + i));
        }
        printf("\n");
        //free(tokens);
    }

    //char** tmp = calloc(100, sizeof(char*));
    /*
    if (tokens) {
        for (j = 0; *(tokens + j); j++) {
            char* tmp;
            tmp = malloc(sizeof(char) * (strlen(*(tokens + j)) + 1));

            strcpy(tmp, *(tokens + j));
            result[j] = tmp;
            //free(*(tokens + j));
        }
    }
    */

    for (i = 0; i < COMMAND_SIZE; i++){
        if(strcmp(first, PKW_converter[i].key) == 0){
            return i;
        }
        //else
            //printf("Lancuchy nie sa rowne\n");
    }

    return -1;

}

#endif /* !SERWER_READSTRING_H */

