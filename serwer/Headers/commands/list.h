#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_LIST_H
#define SERWER_LIST_H

void listCommand(struct thread_data_t *t_data_ptr){
    printf("KOMENDA W PRZYGOTOWANIU!!\n");
    printf("Obecnie połączone gniazda:\n");
    //print_array_content(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients);
}

#endif /* !SERWER_LIST_H */
