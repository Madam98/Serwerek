#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#ifndef SERWER_DELETE_H
#define SERWER_DELETE_H

void deleteCommand(void *t_data_ptr, char* arguments[]){
    char buf[100];
    struct user_data *user = (struct user_data *)t_data_ptr;

    int client_socket = user->user_socket;
    char* result = user->path;

    char* path = (char*)malloc(strlen(result)+1);
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

    printBreak();
    strcat(path, "/");
    int i = 0;
    while(arguments[i] != NULL) {
        strcat(path, arguments[i]);
        if(arguments[i + 1] != NULL)
            strcat(path, " ");
        i++;
    }
    strcat(path, ".txt");
    printf("Sciezka usuwanego pliku: \n\t%s\n", path);

    FILE* file_descriptor = fopen(path, "r");

    //printf("%d\n", file_descriptor);
    if (file_descriptor == 0) {
        printf("Błąd przy próbie USUWANIA pliku!\n");
        printf("Podany plik o danej nazwie nie istnieje!\n");
    }
    else{
        printf("Sciezka istniejacego pliku: \n\t%s\n", path);
        close(file_descriptor);
        remove(path);
        printf("USUNIETO PODANY PLIK!\n");
    }


}
#endif //SERWER_DELETE_H
