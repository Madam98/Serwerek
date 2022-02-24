#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/insertchar.h>

#ifndef SERWER_MESSAGE_H
#define SERWER_MESSAGE_H

void message(struct clients_struct *client_data, char *arguments[], int size_of_array){

    //SPOSOB UZYCIA
    //np. share:2 > r
    //share:[kursor] > [char]

    char* path = client_data->open_file_descriptor_path;
    FILE* file_descriptor = fopen(path, "rw+");
    char ch;
    int linesCount = 0;

    int client_cursor = strtol(arguments[0], NULL, 10);
    char client_char[1];
    strcpy(client_char, arguments[2]);

    while((ch = fgetc(file_descriptor)) != EOF){
        if(ch == '\n')
            linesCount++;
    }

    fseek(file_descriptor, client_cursor, SEEK_SET);
    int cursor_position = ftell(file_descriptor);

    //fputc(client_char[0], file_descriptor);
    finsert(file_descriptor, &client_char[0]);

    printf("Ilosc linii: %d\n", linesCount);
    printf("Pozycja kursora: %d\n", cursor_position);

    fclose(file_descriptor);

    //tutaj musi pojawic sie send do klientow ktorzy maja ten plik


    int i;
    while (client_data->send_share_file_descriptor[i] != 0){
    //for (i = 0; i < 10; i++){
        printf("WYSYLAM DO DESKRYPTORA: %d, wiadomosc %s > %s\n", client_data->send_share_file_descriptor[i], arguments[0], arguments[2]);
        send(client_data->send_share_file_descriptor[i], arguments, strlen(arguments), 0);
        //printf();
    }
}


#endif /* !SERWER_MESSAGE_H*/
