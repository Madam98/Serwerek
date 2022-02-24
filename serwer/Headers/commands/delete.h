#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#ifndef SERWER_DELETE_H
#define SERWER_DELETE_H

void deleteCommand(struct clients_struct *client_data, char *arguments[], int size_of_array){
    char buf[100];

    int client_socket   = client_data->client_socket;
    char* result        = client_data->path;
    char* path          = (char*)malloc(strlen(result)+1);

    strcpy(path, result);

    //printBreak();
    //printf("%s\n", path);

    //sprawdz czy istnieje glowny folder uzytkownika
    if(ExistsFolder(path) == 1){
        printf("BRAK GLOWNEGO FOLDERU UZYTKOWNIKA!!\n");
        //perror("1");
    }
    //printf("Odczytane:\t\t\t\t %s\n", arguments[0]);
    //printf("Na sockecie:\t\t\t %d\n", client_socket);
    //printBreak();
    //printf("\n");

    //printBreak();
    strcat(path, "/");
    int i = 0;
    while(arguments[i] != NULL) {
        strcat(path, arguments[i]);
        if(arguments[i + 1] != NULL)
            strcat(path, " ");
        i++;
    }
    strcat(path, ".txt");
    //printf("Sciezka usuwanego pliku: \n\t%s\n", path);

    FILE* file_descriptor = fopen(path, "r");

    if (file_descriptor == 0) {
        printf("Błąd przy próbie USUWANIA pliku!\n");
        printf("Podany plik o danej nazwie nie istnieje!\n");
    }
    else{
        //printf("Sciezka istniejacego pliku: \n\t%s\n", path);
        remove(path);
        red();
        printf("USUNIETO PODANY PLIK!\n");
        reset();
    }
    fclose(file_descriptor);
    free(path);
}
#endif //SERWER_DELETE_H
