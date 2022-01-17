#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#ifndef SERWER_HANDLEARRAYOFCLIENTS_H
#define SERWER_HANDLEARRAYOFCLIENTS_H


void *ThreadArray(void *a_data){
    pthread_detach(pthread_self());     //<--wątek odłączony, jak się odblokuje watek skończy automatycznie zwalniane zasoby
    struct array_data_clients *a_data_ptr = (struct array_data_clients *)a_data;

    while(1){
        sleep(10);

        printf("Sprawdzam tablice...\n");
        //sprawdz wszystkie adresy w tablicy czy wciaz tam sa
        int i;
        for(i = 0; i < a_data_ptr->counter; i++){
            printf("Wysylam na deskryptor: %d zapytanie czy jest\n", a_data_ptr->descriptor[i]);
            write(a_data_ptr->descriptor[i], "0123456789", 10);
        }
    }

    return 0;
}


handleArrayOfClients(int connection_socket_descriptor, struct array_data_clients *a_data_ptr){
    struct array_data_clients array[1000];

    pthread_t thread0;
    pthread_mutex_lock(&(a_data_ptr->thread_data_mutex));
    a_data_ptr->counter = 0;
    a_data_ptr->first_empty = 0;

    printf("WATEK ARRAY\n");
    int create_result = pthread_create(&thread0, NULL, ThreadArray, (void *)a_data_ptr);
    createInfo(create_result);
}

#endif /* !SERWER_HANDLEARRAYOFCLIENTS_H */
