#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_STRUCTS_H
#define SERWER_STRUCTS_H

// struktura zawierająca dane, które zostaną przekazane do wątku "klienta"
struct thread_data_t
{
    int max_number_of_clients;  //<---maksymalny rozmiar klientow
    //musimy dodac dynamiczna tablice client_socketfd
    int *client_socketfd;
    int number_of_clients;      //<---teraz zalogowanych
    int last_connected;         //<---ostatnio polaczony
    char* name_identificator;    //<---identyfikator klienta (klient na start wpisuje). Tworzony na podstawie tego jest tworzony/otwierany odpowiedni folder z dokumentami
    char* path;

    // mutex do operacji na danych w strukturze
    pthread_mutex_t thread_data_mutex;
};



struct array_data_clients
{
    int* descriptor;
    char* name;
    pthread_mutex_t thread_data_mutex;
    int counter;
    int first_empty;
};

struct user_data
{
    char* path;
    int user_socket;
    int epoll_fd;
    struct epoll_event epoll_event;
    struct epoll_event *epoll_events;
};

struct clients_struct
{
    int     FLAG_DELETED;

    int     client_socket;
    char*   name;
    char*   path;
    char*   global_path;
    int     file_descriptor;

    char    share_path[1000];                 //<---przerobic na tablice
    int     send_owner_file_descriptor;       //<---przerobic na tablice
    int     send_share_file_descriptor;
    char    enter_path[1000];


    int     FLAG_TO_SENT;

    char    open_file_descriptor_path[1000];
    int     shared_with_me_descriptors;
    int     counter;
};

#endif /* !SERWER_STRUCTS_H */
