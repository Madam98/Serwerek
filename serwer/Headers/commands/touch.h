#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_TOUCH_H
#define SERWER_TOUCH_H

void touchCommand(struct clients_struct *client_data, char *arguments[], int size_of_array){
    //readlink("/proc/self/exe", path, sizeof(path)); //<--- w systemach uniksowych do znalezienia sciezki musimy odwolac sie do /usr/bin/perl
    //komenda na gorze powinna dzialac ale no wlasnie cos jest nie tak. Przejdziemy do podstepu i wykonamy komende linuksowa z przekierowaniem do /dev/null
    //system("pwd >/dev/null 2>&1");
    //char buf[100];
    //char *buf;
    //int client_socket = user->user_socket;
    //char* result = user->path;

    //char* buf = (char*)malloc(strlen(path)+1);

    char* path;

    strcpy(path, client_data->path);
    strcat(path, "/");
    strcat(path, client_data->name);

    char* buf = NULL;
    buf = (char *)malloc(strlen(client_data->path) + 1);
    strcpy(buf, path);

    //t_data_ptr->path;

    //strcpy(*path, t_data_ptr->path);

    //char *path = getenv("PWD");

    printBreak();
    printf("%s\n", buf);
    //sprawdz czy istnieje
    if(ExistsFolder(path) == 1){
        printf("BRAK GLOWNEGO FOLDERU UZYTKOWNIKA!!\n");
        perror(1);
    }

    printf("Odczytane:\t\t\t\t %s\n", arguments[0]);
    //printf("Na sockecie:\t\t\t %d\n", client_socket);
    printBreak();
    printf("\n");

    printBreak();
    strcat(buf, "/");
    int i = 0;
    while(arguments[i] != NULL) {
        strcat(buf, arguments[i]);
        if(arguments[i + 1] != NULL)
            strcat(path, " ");
        i++;
    }
    strcat(buf, ".txt");
    printf("Sciezka tworzonego pliku: \n\t%s\n", path);

    FILE* file_descriptor = fopen(buf, "r");

    //printf("%d\n", file_descriptor);
    if (file_descriptor > 0) {
        printf("Błąd przy próbie TWORZENIA pliku!\n");
        printf("Podany plik o danej nazwie juz istnieje!\n");
        printf("Sciezka istniejacego pliku: \n\t%s\n", buf);
    }
    else{
        file_descriptor = fopen(buf, "w");
        printf("Utworzono plik o podanej nazwie pod sciezka: \n\t%s\n", buf);
    }
    printBreak();
    fclose(file_descriptor);
};

#endif /* !SERWER_TOUCH_H */
