#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/insertchar.h>
#include <Headers/deletechar.h>

#ifndef SERWER_MESSAGE_H
#define SERWER_MESSAGE_H

void message(struct clients_struct *client_data, char *arguments[], int size_of_array){

    //SPOSOB UZYCIA
    //np. share:2 > r
    //share:[kursor] > [char]

    char* path = client_data->enter_path;
    FILE* file_descriptor = fopen(path, "rw+");
    char ch;
    int linesCount = 1;

    int client_cursor = strtol(arguments[0], NULL, 10);
    char client_char[1];
    if(strcmp(arguments[2], "SPACE") == 0){
        strcpy(client_char, " ");
    }
    else if (strcmp(arguments[2], "ENTER") == 0) {
        strcpy(client_char, "\n");
    }
    else {
        strcpy(client_char, arguments[2]);
    }

    while((ch = fgetc(file_descriptor)) != EOF){
        if(ch == '\n')
            linesCount++;
    }

    fseek(file_descriptor, client_cursor, SEEK_SET);
    int cursor_position = ftell(file_descriptor);

    //fputc(client_char[0], file_descriptor);

    if(strcmp(arguments[2], "BACK_SPACE") == 0){
        fdelete(file_descriptor);
    }
    else {
        finsert(file_descriptor, &client_char[0]);
    }
    printf("Ilosc linii: %d\n", linesCount);
    printf("Pozycja kursora: %d\n", cursor_position);

    fclose(file_descriptor);

    //tutaj musi pojawic sie send do klientow ktorzy maja ten plik


    int i;

    char message[40];
    memset(&message, 0, sizeof(message));
    strcat(message, arguments[0]);
    strcat(message, " ");
    strcat(message, arguments[1]);
    strcat(message, " ");
    strcat(message, arguments[2]);
    strcat(message, "\n");

    if (strstr(client_data->enter_path, client_data->name) == 0){
        write(client_data->send_owner_file_descriptor, message, strlen(message));
    }

    else if (strstr(client_data->enter_path, client_data->name) != 0){
        write(client_data->send_share_file_descriptor, message, strlen(message));
    }


    /*
    while (client_data->send_share_file_descriptor[i] != 0){
    //for (i = 0; i < 10; i++){
        printf("WYSYLAM DO DESKRYPTORA: %d, wiadomosc %s > %s\n", client_data->send_share_file_descriptor[i], arguments[0], arguments[2]);
        send(client_data->send_share_file_descriptor[i], arguments, strlen(arguments), 0);
        //printf();
    }
    */
}


#endif /* !SERWER_MESSAGE_H*/
