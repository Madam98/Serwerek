#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_LIST_H
#define SERWER_LIST_H

void listCommand(struct clients_struct *client_data, char *arguments[], int size_of_array){

    struct node *foundLink;

    printf("ILOSC KLIENTOW: %d\n", length());
    reset();
    //printf("KLIENCI\n");
    int i;
    char* client_name[100];
    memset(&client_name, 0, 100);
    for (i = 0; i < length(); i++){
        foundLink = find(i);
        //if(strcmp(foundLink->client.name, client_data->name) != 0) {
            printf("\n");
            printf("Nazwa klienta:\t\t\t %s\n", foundLink->client.name);
            printf("Numer socketa:\t\t\t %d\n", foundLink->client.client_socket);
            printf("File descriptor: \t\t %d\n", foundLink->client.file_descriptor);

            strcpy(client_name, "l:");
            strcat(client_name, foundLink->client.name);
            strcat(client_name, "\n");

            write(client_data->client_socket, client_name, strlen(client_name));
            memset(&client_name, 0, 100);

            //printf("Share descriptor:\t\t %d\n", foundLink->client.share_file_descriptor);
            //printf("Share with_me_descriptor:%d\n", foundLink->client.share_file_descriptor);
        //}
    }
    //char end_m[6] = "l:EOF\n";
    //printf("%s", end_m);
    //write(client_data->client_socket, end_m, 6);
}

#endif /* !SERWER_LIST_H */
