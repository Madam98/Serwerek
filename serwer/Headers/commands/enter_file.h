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
        //perror("1");
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


    strcpy(client_data->open_file_descriptor_path, buf);
    FILE* file_descriptor;
    file_descriptor = fopen(buf,  "rw+");

    //WYSYLAMY PLIK UZYTKOWNIKOWI
    char c;
    char message[10] = "";
    int counter = 0;

    while (c != EOF){
        c = fgetc(file_descriptor);
        strcat(message, c);
        counter++;
        if (counter <= 10){
            counter = 0;
            write(client_data->client_socket, c, 10);
        }
    }

    //printf("%d\n", file_descriptor);
    /*
    if (file_descriptor > 0) {
        printf("Otworzono plik o podanej nazwie pod sciezka: \n\t%s\n", buf);
        client_data->open_file_descriptor = file_descriptor;
    }
    else{
        printf("Błąd przy próbie OTWORZENIA pliku!\n");
    }
    */



    printBreak();
    free(buf);
}



#endif /* !SERWER_ENTER_H */
