#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_ADD_H
#define SERWER_ADD_H

//void addCommand(struct clients_struct* client_data, char *arguments[]){
void addCommand(char* path, char* name, char *arguments[]){


    //POPRAWIC!
    int i;
    for (i = 0; i < 1; i++) {
        strcpy(name, *(arguments + i));
        //if (st)
    }
    //client_data->name = "YOLO";
    connectUser(name, path);

};



#endif /* !SERWER_ADD_H */
