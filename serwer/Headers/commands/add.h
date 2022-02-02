#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_ADD_H
#define SERWER_ADD_H

//void addCommand(struct clients_struct* client_data, char *arguments[]){
void addCommand(struct clients_struct *client_data, char *arguments[], int size_of_array){

    //POPRAWIC!
    int i;
    char* name = strdup (arguments);

    for (i = 0; i < size_of_array; i++) {
        if(i == 0){
            strcpy(name, *(arguments + 0));
        }
        else {
            strcat(name, *(arguments + i));
        }

        if ((i + 1) != size_of_array)
            strcat(name, " ");
    }
    client_data->name = name;
    connectUser(client_data->name, client_data->path);

    char* path;

    strcpy(path, client_data->path);
    strcat(path, "/");
    strcat(path, client_data->name);

    strcpy(client_data->path, path);
};



#endif /* !SERWER_ADD_H */
