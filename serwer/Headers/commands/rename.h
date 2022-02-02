#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#ifndef SERWER_RENAME_H
#define SERWER_RENAME_H

void renameCommand(struct clients_struct *client_data, char *arguments[], int size_of_array){
    char buf[100];

    int client_socket   = client_data->client_socket;
    char* result        = client_data->client_socket;
    char* path          = (char*)malloc(strlen(result)+1);

    strcpy(path, result);
    printBreak();
    printf("%s\n", path);
    //sprawdz czy istnieje glowny folder uzytkownika
    if(ExistsFolder(path) == 1){
        printf("BRAK GLOWNEGO FOLDERU UZYTKOWNIKA!!\n");
        perror(1);
    }
    printf("Odczytane:\t\t\t\t %s\n", arguments[0]);
    printf("Na sockecie:\t\t\t %d\n", client_socket);

    printBreak();
    printf("\n");

    char* new_path = (char*)malloc(strlen(result)+1);
    strcpy(new_path, result);

    printBreak();
    strcat(path, "/");
    strcat(new_path, "/");
    int i = 0;
    while(arguments[i] != NULL && strcmp(arguments[i], ">") != 0 ) {
        strcat(path, arguments[i]);
        if(arguments[i + 1] != NULL && strcmp(arguments[i + 1], ">") != 0 )
            strcat(path, " ");
        i++;
    }
    if(strcmp(arguments[i], ">") == 0){
        while(arguments[i] != NULL) {
            strcat(new_path, arguments[i]);
            if(arguments[i + 1] != NULL)
                strcat(new_path, " ");
            i++;
        }
    }

    strcat(path, ".txt");
    printf("Sciezka zmienianego pliku: \n\t%s\n", path);
    printf("Sciezka nowego pliku: \n\t%s\n", new_path);

    FILE* file_descriptor = fopen(path, "r");

    //printf("%d\n", file_descriptor);
    if (file_descriptor == 0) {
        printf("Błąd przy próbie ZMIENIANIA NAZWY pliku!\n");
        printf("Podany plik o danej nazwie nie istnieje!\n");
    }
    else{
        printf("Sciezka istniejacego pliku: \n\t%s\n", path);
        close(file_descriptor);
        rename(path, new_path);
        printf("Udalo sie ZMIENIC nazwe pliku!\n");
    }
}
#endif //SERWER_RENAME_H
