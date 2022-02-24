#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#ifndef SERWER_RENAME_H
#define SERWER_RENAME_H

void renameCommand(struct clients_struct *client_data, char *arguments[], int size_of_array){
    char buf[100];
    int client_socket = client_data->client_socket;
    char* path        = strdup(client_data->path);
    char* new_path    = strdup(client_data->path);

    strcpy(path, client_data->path);
    strcpy(new_path, client_data->path);

    //printBreak();
    //printf("%s\n", path);

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
    strcat(new_path, "/");
    int i = 0;
    while(arguments[i] != NULL && strcmp(arguments[i], ">") != 0 ) {
        strcat(path, arguments[i]);
        if(arguments[i + 1] != NULL && strcmp(arguments[i + 1], ">") != 0 )
            strcat(path, " ");
        i++;
    }
    if(strcmp(arguments[i], ">") == 0){
        i++;
        while(arguments[i] != NULL) {
            strcat(new_path, arguments[i]);
            if(arguments[i + 1] != NULL)
                strcat(new_path, " ");
            i++;
        }
    }
    strcat(path, ".txt");
    strcat(new_path, ".txt");
    //printf("Sciezka zmienianego pliku: \n\t%s\n", path);

    FILE* file_descriptor = fopen(path, "r");

    if (file_descriptor == 0) {
        printf("Błąd przy próbie ZMIENIANIA NAZWY pliku!\n");
        printf("Podany plik o danej nazwie nie istnieje!\n");
    }
    else{
        char ch;
        FILE* new_file_descriptor = fopen(new_path, "r");
        //printf("Sciezka tworzonego pliku: \n\t%s\n", path);
        green();
        rename(path, new_path);
        reset();
        printf("Udalo sie ZMIENIC nazwe pliku!\n");
    }
}
#endif //SERWER_RENAME_H
