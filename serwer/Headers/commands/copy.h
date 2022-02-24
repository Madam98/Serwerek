#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#ifndef SERWER_COPY_H
#define SERWER_COPY_H

void copyCommand(struct clients_struct *client_data, char *arguments[], int size_of_array){
    char buf[100];
    int client_socket   = client_data->client_socket;
    char* path      = strdup(client_data->path);
    strcpy(path, client_data->path);

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

    char* old_path = strdup(client_data->path);

    strcat(old_path, "/");
    strcat(path, "/");
    strcat(path, "COPY_");
    int i = 0;
    while(arguments[i] != NULL) {
        strcat(path, arguments[i]);
        strcat(old_path, arguments[i]);
        if(arguments[i + 1] != NULL) {
            strcat(path, " ");
            strcat(old_path, " ");
        }
        i++;
    }
    strcat(path, ".txt");
    strcat(old_path, ".txt");
    printf("Sciezka zmienianego pliku: \n\t%s\n", old_path);
    FILE* file_descriptor = fopen(old_path, "r");
    if (file_descriptor == 0) {
        printf("Błąd przy próbie ZMIENIANIA NAZWY pliku!\n");
        printf("Podany plik o danej nazwie nie istnieje!\n");
    }
    else{
        char ch;
        FILE* new_file_descriptor = fopen(path, "w");

        printf("Sciezka tworzonego pliku: \n\t%s\n", path);

        //rename(path, path);

        // Read contents from file
        ch = fgetc(file_descriptor);
        while (ch != EOF)
        {
            fputc(ch, new_file_descriptor);
            ch = fgetc(file_descriptor);
        }

        green();
        printf("Udalo sie STWORZYC kopie pliku!\n");
        reset();
        fclose(new_file_descriptor);
    }
    fclose(file_descriptor);

    free(path);
    free(old_path);
};


#endif //SERWER_COPY_H
