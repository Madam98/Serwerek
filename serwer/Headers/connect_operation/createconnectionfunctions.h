#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

void printBreak(){
    printf("----------------------------------------------------------\n");
}

//-------------------------------------------------------------------------------

void createThreadClient(int max_num_of_clients, struct thread_data_t *t_data_ptr){
    t_data_ptr->client_socketfd = malloc(sizeof(int) * max_num_of_clients);
    t_data_ptr->number_of_clients = 0;
    t_data_ptr->max_number_of_clients = max_num_of_clients;
    t_data_ptr->last_connected = 0;
    for( int i = 0; i < max_num_of_clients; i++){
        t_data_ptr->client_socketfd[i] = 0;
    }
    t_data_ptr->name_identificator = "";
}

void createArrayClient(struct array_data_clients *array){
    array->descriptor = malloc(sizeof(int) * 1000);
    for( int i = 0; i < 1000; i++){
        array->descriptor[i] = 0;
    }
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
void initMutex(struct thread_data_t *t_data_ptr){
    if (pthread_mutex_init(&(t_data_ptr->thread_data_mutex), NULL) != 0){
        perror("\n Mutex init failed!\n");
        exit (1);
    }
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
void initAdreessServer(struct sockaddr_in *server_address){
    // Inicjalizacja adresu serwera
    memset(server_address, 0, sizeof(struct sockaddr));    //<---- UWAGA!!! Korci cie aby wrzucic to do maina? Chcesz mocno? Pamietaj aby dopisac & do server_address!!!
    server_address->sin_family = AF_INET;
    server_address->sin_addr.s_addr = htonl(INADDR_ANY);
    server_address->sin_port = htons(SERVER_PORT);
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
void checkServerSocketDescriptor(int server_socket_descriptor, char* argv[]){
    if (server_socket_descriptor < 0){
        fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda..\n", argv[0]);
        exit(1);
    }
}

void socketInfo(int server_socket_descriptor){
    printf("\n");
    printBreak();
    printf("SOCKET zostal poprawnie skonfigurowany\n");
    printf("server_socket_descriptor:\t %d\n", server_socket_descriptor);
    printf("SOL_SOCKET:\t\t\t\t\t %d\n", SOL_SOCKET);
    printf("SO_REUSEADDR\t\t\t\t %d\n", SO_REUSEADDR);
    printBreak();
    printf("\n");
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
void checkBindResult(int bind_result, char* argv[]){
    while (bind_result < 0){
        fprintf(stderr, "%s: Błąd przy próbie dowiązania adresu IP i numeru portu do socketu.\n", argv[0]);
        printf("Port zajety\n\n");
        sleep(1);
        //exit(1);
    }
}

void bindInfo(){
    printBreak();
    printf("Poprawnie utworzono BIND\n");
    printBreak();
    printf("\n");
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
void checkListen(int listen_result, char* argv[]){
    if (listen_result < 0) {
        fprintf(stderr, "%s: Błąd przy próbie ustawienia wielkości kolejki.\n", argv[0]);
        exit(1);
    }
}

void infoListen(){
    printBreak();
    printf("Poprawnie utworzono LISTEN\n");
    printf("QUEUE_SIZE:\t\t\t\t\t %d\n", QUEUE_SIZE);
    printBreak();
    printf("\n");
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
int createEpoll(){
    int epoll_fd = epoll_create1(0);
    if(epoll_fd == -1){
        fprintf(stderr, "Failed to create epoll file descriptor\n");
        exit (-1);
    }
    printBreak();
    printf("Poprawnie stworzono deskryptor EPOLL\n");
    printf("Epoll deskryptor:\t\t\t %d\n", epoll_fd);
    printBreak();
    printf("\n");
    return epoll_fd;
}
//-------------------------------------------------------------------------------

#ifndef SERWER_CREATECONNECTIONFUNCTIONS_H
#define SERWER_CREATECONNECTIONFUNCTIONS_H

#endif /* !SERWER_CREATECONNECTIONFUNCTIONS_H */
