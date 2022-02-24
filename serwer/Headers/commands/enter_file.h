#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_ENTER_H
#define SERWER_ENTER_H

void enter_file(struct clients_struct *client_data, char *arguments[], int size_of_array){

    if(strcmp(arguments[0], "m") == 0) {
        char *path = client_data->path;
        char *buf = strdup(client_data->path);
        strcpy(buf, path);

        printBreak();
        printf("%s\n", buf);
        //sprawdz czy istnieje
        if (ExistsFolder(path) == 1) {
            printf("BRAK GLOWNEGO FOLDERU UZYTKOWNIKA!!\n");
            //perror("1");
        }

        printf("Odczytane:\t\t\t\t %s\n", arguments[0]);
        //printf("Na sockecie:\t\t\t %d\n", client_socket);
        printBreak();
        printf("\n");

        printBreak();
        strcat(buf, "/");
        int i = 2;
        while (arguments[i] != NULL) {
            strcat(buf, arguments[i]);
            if (arguments[i + 1] != NULL)
                strcat(buf, " ");
            i++;
        }
        strcat(buf, ".txt");
        printf("Sciezka otwieranego pliku: \n\t%s\n", buf);


        strcpy(client_data->open_file_descriptor_path, buf);
        FILE *file_descriptor;
        file_descriptor = fopen(buf, "rw+");

        //WYSYLAMY PLIK UZYTKOWNIKOWI
        char c;
        char temp[2] = "";
        temp[1] = '\0';

        char message[10];
        memset(&message[0], 0, sizeof(message));
        int counter = 0;

        printf("WYSYLAM MESSAGE: ");
        while (c != EOF) {
            c = fgetc(file_descriptor);
            temp[0] = c;
            strcat(message, temp);
            counter++;

            if (counter >= 10) {
                counter = 0;
                printf("\n*****\n%s\n*****\n", message);
                write(client_data->client_socket, c, 10);
                memset(&message[0], 0, sizeof(message));
            }
        }
        if (message != NULL) {
            printf("\n*****\n%s\n*****\n", message);
            write(client_data->client_socket, c, strlen(message));
        }

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
    else if(strcmp(arguments[0], "i") == 0){
        //char *path = client_data->path;
        //char *buf = strdup(client_data->path);
        //strcpy(buf, path);

        printBreak();
        printf("%s\n", arguments[2]);
        //sprawdz czy istnieje
        //if (ExistsFolder(arguments[2]) == 1) {
        //    printf("BRAK GLOWNEGO FOLDERU UZYTKOWNIKA!!\n");
            //perror("1");
        //}

        printf("Odczytane:\t\t\t\t %s\n", arguments[0]);
        //printf("Na sockecie:\t\t\t %d\n", client_socket);
        printBreak();
        printf("\n");

        printBreak();
        /*
        strcat(buf, "/");
        int i = 2;
        while (arguments[i] != NULL) {
            strcat(buf, arguments[i]);
            if (arguments[i + 1] != NULL)
                strcat(buf, " ");
            i++;
        }
        strcat(buf, ".txt");
        printf("Sciezka otwieranego pliku: \n\t%s\n", buf);

        */

        //strcpy(client_data->open_file_descriptor_path, buf);
        FILE *file_descriptor;
        file_descriptor = fopen("/home/oem/Desktop/23.02/Serwerek/serwer/cmake-build-debug/DOCUMENTS/adam/1.txt", "rw+");


        //WYSYLAMY PLIK UZYTKOWNIKOWI
        char c;
        char temp[2] = "";
        temp[1] = '\0';

        char message[10];
        memset(&message[0], 0, sizeof(message));
        int counter = 0;

        printf("WYSYLAM MESSAGE: ");
        while (c != EOF) {
            c = fgetc(file_descriptor);
            temp[0] = c;
            strcat(message, temp);
            counter++;

            if (counter >= 10) {
                counter = 0;
                printf("\n*****\n%s\n*****\n", message);
                write(client_data->client_socket, c, 10);
                memset(&message[0], 0, sizeof(message));
            }
        }
        if (message != NULL) {
            printf("\n*****\n%s\n*****\n", message);
            write(client_data->client_socket, c, strlen(message));
        }

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
        //free(buf);
    }

}



#endif /* !SERWER_ENTER_H */
