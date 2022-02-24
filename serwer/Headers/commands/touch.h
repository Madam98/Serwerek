#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_TOUCH_H
#define SERWER_TOUCH_H

void touchCommand(struct clients_struct *client_data, char *arguments[], int size_of_array){
    //readlink("/proc/self/exe", path, sizeof(path)); //<--- w systemach uniksowych do znalezienia sciezki musimy odwolac sie do /usr/bin/perl
    //komenda na gorze powinna dzialac ale no wlasnie cos jest nie tak. Przejdziemy do podstepu i wykonamy komende linuksowa z przekierowaniem do /dev/null
    //system("pwd >/dev/null 2>&1");

    char* path = client_data->path;
    char* buf = strdup(client_data->path);
    strcpy(buf, path);

    //printBreak();
    //printf("%s\n", buf);
    if(ExistsFolder(path) == 1){
        printf("BRAK GLOWNEGO FOLDERU UZYTKOWNIKA!!\n");
        //perror();
    }

    //printf("Odczytane:\t\t\t\t %s\n", arguments[0]);
    //printBreak();
    //printf("\n");

    //printBreak();
    strcat(buf, "/");
    int i = 0;
    while(arguments[i] != NULL) {
        strcat(buf, arguments[i]);
        if(arguments[i + 1] != NULL)
            strcat(buf, " ");
        i++;
    }
    strcat(buf, ".txt");
    //printf("Sciezka tworzonego pliku: \n\t%s\n", buf);

    FILE* file_descriptor ;
    file_descriptor = fopen(buf, "r");

    if (file_descriptor > 0) {
        printf("Błąd przy próbie TWORZENIA pliku!\n");
        printf("Podany plik o danej nazwie juz istnieje!\n");
        printf("Sciezka istniejacego pliku: \n\t%s\n", buf);
    }
    else{
        file_descriptor = fopen(buf, "w");
        printf("Utworzono plik pod sciezka:\t\t\t\033[1;32m%s\033[0m\n", buf);
    }
    //printBreak();
    fclose(file_descriptor);
    free(buf);
};

#endif /* !SERWER_TOUCH_H */
