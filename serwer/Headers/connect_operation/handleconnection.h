#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#ifndef SERWER_HANDLECONNECTION_H
#define SERWER_HANDLECONNECTION_H

void createInfo(int create_result){
    if (create_result){
        printf("Błąd przy próbie utworzenia wątku, kod błędu: %d\n", create_result);
        exit(-1);
    }
    else{
        printf("Utworzono poprawnie WATEK\n");
    }
}

void handleInfo(struct thread_data_t t_data_ptr){
    printBreak();
    //printf("Nowe połączenie. Gniazdo klienta: %d\n", connection_socket_descriptor);
    printf("lock mutex: %d\n", t_data_ptr.thread_data_mutex);
    printBreak();
    printf("\n");
}

// funkcja obsługująca połączenie z nowym klientem
void handleConnection(int connection_socket_descriptor, struct thread_data_t *t_data_ptr, struct array_data_clients *array, char* path, int epoll_fd, struct epoll_event *event, struct epoll_event *events)
{
    // sprawdzenie, czy jest wolne miejsce w współdzielonej tablicy z numerami połączonych gniazd
    pthread_mutex_lock(&(t_data_ptr->thread_data_mutex));
    handleInfo(*t_data_ptr);
    int index = find_empty_cell(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients);

    if (t_data_ptr->max_number_of_clients == t_data_ptr->number_of_clients){
        printf("Limit polaczen osiagniety");
    }
    else{
        t_data_ptr->client_socketfd[index] = connection_socket_descriptor;

        struct user_data user;
        user.user_socket = connection_socket_descriptor;
        user.path = path;
        user.epoll_fd = epoll_fd;
        user.epoll_event = *event;
        user.epoll_events = events;

        //memcpy(&user.epoll_events, events, sizeof(user.epoll_events));

        pthread_t thread1;              //<--uchwyt na watek

        int create_result = pthread_create(&thread1, NULL, ThreadBehavior, &user);
        createInfo(create_result);
    }
}

#endif /* !SERWER_HANDLECONNECTION_H */
