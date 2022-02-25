#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/lists.h>

#ifndef SERWER_SHARE_H
#define SERWER_SHARE_H

void shareCommand(struct clients_struct *client_data, char *arguments[], int size_of_array){

    //SPOSOB UZYCIA
    //np. share:adam > plik
    //share:[KOMU] > [JAKI PLIK]

    int client_socket   = client_data->client_socket;
    char user[200];
    char user_path[1000];
    char file_name[200];

    strcpy(user_path, client_data->global_path);

    //printBreak();
    //printf("%s\n", user_path);
    if(ExistsFolder(user_path) == 1){
        printf("BRAK GLOWNEGO FOLDERU UZYTKOWNIKA!!\n");
        //perror("1");
    }
    //printf("Odczytane:\t\t\t\t %s\n", arguments[0]);
    //printf("Na sockecie:\t\t\t %d\n", client_socket);

    //printBreak();
    //printf("\n");

    //printBreak();

    int i = 0;
    while(arguments[i] != NULL && strcmp(arguments[i], ">") != 0 ) {
        strcpy(user, arguments[i]);
        if(arguments[i + 1] != NULL && strcmp(arguments[i + 1], ">") != 0 )
            strcpy(user, " ");
        i++;
    }
    if(strcmp(arguments[i], ">") == 0){
        i++;
        while(arguments[i] != NULL) {
            strcpy(file_name, arguments[i]);
            if(arguments[i + 1] != NULL)
                strcpy(file_name, " ");
            i++;
        }
    }
    strcat(file_name, ".txt");
    strcat(user_path, "/");
    strcat(user_path, client_data->name);
    strcat(user_path, "/");
    strcat(user_path, file_name);


    //printf("Sciezka zmienianego pliku: \n\t%s\n", user_path);

    //MUSIMY ZNALEZC UZYTKOWNIKA KTOREMU UDOSTEPNIAMY PLIK A NASTEPNIE WPISAC DESKRYPTOR UZYTKOWNIKA ABY WYSYLAC DO NIEGO INFORMACJE O ZMIANACH W PLIKU
    struct node *foundLink;
    //printf("SZUKAM DANEGO KLIENTA: %d\n", length());

    int j;
    int find_j;
    for (i = 0; i < length(); i++){
        foundLink = find(i);
        if(strcmp(foundLink->client.name, user) == 0) {
            //printf("\nZNALAZLEM KLIENTA\n");
            green();
            printf("UDOSTEPNIAM PLIK KLIENTOWI: \t\t%s\n", foundLink->client.name);
            reset();

            strcpy(foundLink->client.share_path, user_path);
            foundLink->client.send_owner_file_descriptor = client_data->client_socket;
            foundLink->client.FLAG_TO_SENT = 1;
            client_data->send_share_file_descriptor = foundLink->client.client_socket;
            //strcpy(foundLink->client.share_path, user_path);
        }
    }


}


#endif /* !SERWER_SHARE_H */
