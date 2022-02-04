#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_ENTER_H
#define SERWER_ENTER_H

void enter_file(struct clients_struct *client_data, char *arguments[], int size_of_array){

    char* path = client_data->path;
    char* buf = strdup(client_data->path);
    strcpy(buf, path);

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
            strcat(buf, " ");
        i++;
    }
    strcat(buf, ".txt");
    printf("Sciezka otwieranego pliku: \n\t%s\n", buf);

    FILE* file_descriptor ;
    file_descriptor = fopen(buf, "w+");

    //printf("%d\n", file_descriptor);
    if (file_descriptor > 0) {
        printf("Błąd przy próbie TWORZENIA pliku!\n");
        printf("Podany plik o danej nazwie juz istnieje!\n");
        printf("Sciezka istniejacego pliku: \n\t%s\n", buf);
    }
    else{
        file_descriptor = fopen(buf, "w");
        printf("Otworzono plik o podanej nazwie pod sciezka: \n\t%s\n", buf);
    }

    client_data->file_descriptor = file_descriptor->_fileno;

    printBreak();
    free(buf);
}



#endif /* !SERWER_ENTER_H */
