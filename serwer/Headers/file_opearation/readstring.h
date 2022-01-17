#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#pragma once
#ifndef SERWER_READSTRING_H
#define SERWER_READSTRING_H




// funkcje odczytujaca przeslane wiadomosci od klienta
//************************************
// funkcja odpowiedzialna za podzial. Zczytana tablica wprowadzonych argumentow
char** buf_split(char* a_str, const char a_delim){
    printf("FUNKCJA BUF_SPLIT\n");
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    printf("Wprowadzony string:\t\t\t %s\n", a_str);
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

//WPISANIE WPISANYCH WARTOSCI DO TABLICY
void enterArray(char** tokens, char*** result){
    int counter = 0;
    int i;

    if (tokens) {
        int i;
        for (i = 0; *(tokens + i); i++) {
            counter++;
        }
    }
    char* array_arguments[counter - 1];
    if (tokens) {
        int i;
        for (i = 1; *(tokens + i); i++) {
            strcpy(array_arguments[i - 1], *(tokens + i));
            (*result)[i] = (*tokens + i);
            //array_arguments[i - 1] = *(tokens + i);
            printf("Buffor: %s\n", array_arguments[i - 1]);
            char* path = (char*)malloc(strlen(array_arguments[i - 1]) + 1);
            //free(*(tokens + i));
        }
    }
    //char* folder_sciezka = (char*)malloc(strlen(dirname)+1);

    for (i = 1; i < counter; i++) {
        char *path = (char *) malloc(strlen(array_arguments[i - 1]) + 1);
        strcpy(path, array_arguments[i]);
        (result[i]) = *path;
    }
}



//ODCZYT PIERWSZEJ WCZYTANEJ WARTOSCI DO SPACJI I ZRZUTOWANIE JEJ NA WARTOSC NUMERYCZNA
int readCommand(char** tokens, char* buf[], char* result[]){
    int i;
    int j;
    char* first = " ";
    int counter = 0;

    tokens = buf_split(buf, ' '); //<-- wynik tablica wskaznikow char

    if(tokens){
        for (i = 0; *(tokens + i); i++){
            printf("Argument: %s\n", *(tokens + i));
            //free(*(tokens + i));
        }
        printf("\n");
        //free(tokens);
    }

    first = *(tokens + 0);
    for (i = 0; i < COMMAND_SIZE; i++){
        //fwrite(commands[i], 1, strlen(commands[i]), stdout);
        if(strcmp(first, commands[i]) == 0){
            free(*tokens + 0);

            for (j = 0; *(tokens + j); j++) {
                counter++;
            }
            char** tmp = calloc(40, sizeof(char*));
            //char** result = malloc(40 * sizeof(char*));
            counter--;
            //char* array_arguments[counter - 1];

            if (tokens) {
                for (j = 1; *(tokens + j); j++) {
                    //(*result)[j - 1] = *(tokens + j + 1);
                    *(tmp + j - 1) = *(tokens + j);
                    //strcpy((*result)[j - 1], *(tokens + j));
                    //strcpy(tmp[j], *(tokens + j + 1));
                    //*(tmp + j) = "5";
                    //printf("Buffor: %s\n", (tmp + j - 1));
                    //free(*(tokens + i));
                    result[j - 1] = *(tmp + j - 1);
                }
                //*result = tmp;
            }

            //enterArray(tokens, &result);
            return i;
        }
        else
            printf("Lancuchy nie sa rowne\n");
    }
}
//***********************


#endif /* !SERWER_READSTRING_H */

