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
    char name_identificator;    //<---identyfikator klienta (klient na start wpisuje). Tworzony na podstawie tego jest tworzony/otwierany odpowiedni folder z dokumentami
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


#endif /* !SERWER_STRUCTS_H */
