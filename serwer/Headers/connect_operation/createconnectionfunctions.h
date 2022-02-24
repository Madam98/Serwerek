#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>


void red () {
    printf("\033[1;31m");
}

void green () {
    printf("\033[1;32m");
}

void yel () {
    printf("\033[1;33m");
}

void blue () {
    printf("\033[1;34m");
}

void mag () {
    printf("\033[1;35m");
}

void reset () {
    printf("\033[0m");
}

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
    //t_data_ptr->name_identificator = "";
    strcpy(t_data_ptr->name_identificator, "");
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
//INIT
void initAdreessServer(struct sockaddr_in *server_address){
    // Inicjalizacja adresu serwera
    memset(server_address, 0, sizeof(struct sockaddr));    //<---- UWAGA!!! Korci cie aby wrzucic to do maina? Chcesz mocno? Pamietaj aby dopisac & do server_address!!!
    server_address->sin_family = AF_INET;
    server_address->sin_addr.s_addr = htonl(INADDR_ANY);
    server_address->sin_port = htons(SERVER_PORT);
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
//SOCKET
void checkServerSocketDescriptor(int server_socket_descriptor, char* argv){
    if (server_socket_descriptor < 0){
        fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda..\n", argv);
        exit(1);
    }
}

void socketInfo(int server_socket_descriptor){
    printf("\n");
    printBreak();
    yel();
    printf("SOCKET ");
    reset();
    printf("zostal poprawnie skonfigurowany\n");
    printf("server_socket_descriptor:\t %d\n", server_socket_descriptor);
    printf("SOL_SOCKET:\t\t\t\t\t %d\n", SOL_SOCKET);
    printf("SO_REUSEADDR\t\t\t\t %d\n", SO_REUSEADDR);
    printBreak();
    printf("\n");
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
//BIND
void checkBindResult(int bind_result, char* argv){
    while (bind_result < 0){
        fprintf(stderr, "%s: Błąd przy próbie dowiązania adresu IP i numeru portu do socketu.\n", argv);
        printf("Port zajety\n\n");
        sleep(1);
        //exit(1);
    }
}

void bindInfo(){
    printBreak();
    yel();
    printf("BIND ");
    reset();
    printf("zostal poprawnie skonfigurowany\n");
    printBreak();
    printf("\n");
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
//LISTEN
void checkListen(int listen_result, char* argv){
    if (listen_result < 0) {
        fprintf(stderr, "%s: Błąd przy próbie ustawienia wielkości kolejki.\n", argv);
        exit(1);
    }
}

void infoListen(){
    printBreak();
    yel();
    printf("LISTEN ");
    reset();
    printf("zostal poprawnie utworzony\n");
    printf("QUEUE_SIZE:\t\t\t\t\t %d\n", QUEUE_SIZE);
    printBreak();
    printf("\n");
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
//EPOLL
void createEpollEvDataServer(int epoll_fd, struct epoll_event event){
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket_descriptor, &event) == -1) {
        fprintf(stderr, "Blad epoll_ctl ADD dla serwer socket\n");
        close(epoll_fd);
    }
}

void createEpollEvDataClient(int epoll_fd, struct epoll_event event){
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event) == -1) {
        fprintf(stderr, "Blad epoll_ctl ADD dla serwer socket\n");
        close(epoll_fd);
    }
}

int createEpoll() {
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        red();
        fprintf(stderr, "Failed to create epoll file descriptor\n");
        reset();
        exit(-1);
    }
    printBreak();
    yel();
    printf("EPOLL ");
    reset();
    printf("zostal poprawnie skonfigurowany\n");
    printf("Epoll deskryptor:\t\t\t %d\n", epoll_fd);
    printBreak();
    printf("\n");
    return epoll_fd;
}
//-------------------------------------------------------------------------------

#ifndef SERWER_CREATECONNECTIONFUNCTIONS_H
#define SERWER_CREATECONNECTIONFUNCTIONS_H

#endif /* !SERWER_CREATECONNECTIONFUNCTIONS_H */
