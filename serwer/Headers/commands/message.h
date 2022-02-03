#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_MESSAGE_H
#define SERWER_MESSAGE_H

void message(struct clients_struct *client_data, char *arguments[], int size_of_array){

    int descriptor = client_data->file_descriptor;

    write(descriptor, "example", 7);
    printf("WPISALEM: example do pliku\n");


    fclose(descriptor);
}


#endif /* !SERWER_MESSAGE_H*/
