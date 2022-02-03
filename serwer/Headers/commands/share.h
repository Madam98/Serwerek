#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_SHARE_H
#define SERWER_SHARE_H

void shareCommand(struct clients_struct *client_data, char *arguments[], int size_of_array){

    client_data->share_file_descriptor;

    char* end;
    int number_temp = strtol(*(arguments + 0), &end, 10);

    client_data->share_file_descriptor = client_data->file_descriptor;
    client_data->share_user = "julia";





}


#endif /* !SERWER_SHARE_H */
