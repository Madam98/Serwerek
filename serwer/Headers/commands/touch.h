#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_TOUCH_H
#define SERWER_TOUCH_H

void touchCommand(void *t_data, char *arguments[]){
    //readlink("/proc/self/exe", path, sizeof(path)); //<--- w systemach uniksowych do znalezienia sciezki musimy odwolac sie do /usr/bin/perl
    //komenda na gorze powinna dzialac ale no wlasnie cos jest nie tak. Przejdziemy do podstepu i wykonamy komende linuksowa z przekierowaniem do /dev/null
    //system("pwd >/dev/null 2>&1");
    char buf[100];
    struct thread_data_t *t_data_ptr = (struct thread_data_t *)t_data;
    int client_socket =  t_data_ptr->last_connected;

    char* result = t_data_ptr->path;

    char* path = (char*)malloc(strlen(result)+1);
    strcpy(path, result);

    //t_data_ptr->path;

    //strcpy(*path, t_data_ptr->path);

    //char *path = getenv("PWD");

    printBreak();
    printf("%s\n", path);
    //sprawdz czy istnieje
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
    printf("Sciezka tworzonego pliku: \n\t%s\n", result);

    FILE* file_descriptor = fopen(path, "r");

    //printf("%d\n", file_descriptor);
    if (file_descriptor > 0) {
        printf("Błąd przy próbie tworzenia pliku!\n");
        printf("Podany plik o danej nazwie juz istnieje!\n");
        printf("Sciezka istniejacego pliku: \n\t%s\n", path);
    }
    else{
        file_descriptor = fopen(path, "w");
        printf("Utworzono plik o podanej nazwie pod sciezka: \n\t%s\n", path);
    }
    printBreak();
    fclose(file_descriptor);
};

#endif /* !SERWER_TOUCH_H */
