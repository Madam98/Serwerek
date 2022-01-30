#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#include <Headers/file_opearation/readstring.h>

#include <Headers/file_opearation/msleep.h>
#include <Headers/file_opearation/textAnimation.h>

#include <Headers/connect_operation/createconnectionfunctions.h>

#include <Headers/arrayfunctions.h>
#include <Headers/thread/threadfunctions.h>
#include <Headers/connect_operation/handleconnection.h>
#include <Headers/connect_operation/handlearrayofclients.h>

#include <Headers/handler/sigsegv.h>

#include <Headers/file_opearation/createfolder.h>

#include <Headers/commands/touch.h>
#include <Headers/commands/share.h>
#include <Headers/commands/list.h>
#include <Headers/commands/delete.h>
#include <Headers/commands/copy.h>
#include <Headers/commands/rename.h>

//-----------------------------------------------------------------------------
/*
TO DO user commands
1. Stworzyć plik
2. Udostępnić plik
3. Lista połączonych użytkowników
4. Usunąć plik
5. Skopiować plik
6. Zmienić nazwę pliku
 */
//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    struct thread_data_t *t_data_ptr = malloc(sizeof(struct thread_data_t));
    struct array_data_clients *array = malloc(sizeof(struct array_data_clients));
    struct epoll_event event, events[MAX_EVENTS];
    struct clients_tab_map map_clients[100];

    //PRZYGOTOWYWANIE STRUKTUR
    createThreadClient(max_num_of_clients, t_data_ptr);
    createArrayClient(array);

    initMutex(t_data_ptr);
    initAdreessServer(&server_address);


    //UTWORZENIE GNIAZDA DO POLACZENIA Z SERWEREM
    server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    checkServerSocketDescriptor(server_socket_descriptor, argv[0]);
    setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr_val, sizeof(reuse_addr_val));
    socketInfo(server_socket_descriptor);
    //fcntl(server_socket_descriptor, F_SETFL, O_NONBLOCK);


    //DOWIAZANIE ADRESU SERWERA DO STWORZONEGO GNIAZDA
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handler;
    sigaction(SIGSEGV, &action, NULL);


    //POWIAZANIE ADRESU Z GNIAZDEM
    bind_result = bind(server_socket_descriptor, (struct sockaddr *) &server_address, sizeof(struct sockaddr));
    while(bind_result == -1) {
        printf("Powyzszy port jest zajety! Czekam na zwolnienie portu...\n");
        textAnimation();
        bind_result = bind(server_socket_descriptor, (struct sockaddr *) &server_address, sizeof(struct sockaddr));
    }
    checkBindResult(bind_result, argv[0]);
    bindInfo();


    //WLACZENIE NASLUCHIWANIA NA UTWORZONYM GNIEZDZIE
    listen_result = listen(server_socket_descriptor, QUEUE_SIZE);
    checkListen(listen_result, argv[0]);
    infoListen();


    //STWORZENIE FOLDERU Z POTENCJLANYMI DOKUMENTAMI(jesli nie istnieja)
    char *path = getenv("PWD");
    char* info = "W folderu z wykonywanym plikiem musi znajdowac sie folder DOCUMENTS\n";
    folderInfo(path, info);


    //STWORZENIE EPOLL
    //https://www.programmerall.com/article/1404354560/
    memset(&events, 0, sizeof(struct epoll_event));
    int epoll_fd = createEpoll();
    //event.events = EPOLLIN|EPOLLET;
    event.events = EPOLLIN;
    event.data.fd = server_socket_descriptor;
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket_descriptor, &event) == -1){
        fprintf(stderr, "Blad epoll_ctl ADD dla serwer socket\n");
        close(epoll_fd);
        return 1;
    }
    event.data.fd = 0;
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event) == -1){
        fprintf(stderr, "Blad epoll_ctl ADD dla klawiatury\n");
        close(epoll_fd);
        return 1;
    }

    //OBSLUGA POLACZEN Z UZYTKOWNIKAMI
    int epoll_des;
    int i;
    int counter = 0;
    struct user_data strUser;
    char *temp;

    while(1){
        if((epoll_des = epoll_wait(epoll_fd, events,MAX_EVENTS, -1)) == -1) {
            printf("epoll wait\n");
        }
        printf("Wskaznik NFDS: %d\n", epoll_des);
        for (i = 0; i < epoll_des; ++i) {
            if (events[i].data.fd == server_socket_descriptor) {
                struct sockaddr_in client_sock;
                socklen_t slen = sizeof(client_sock);
                connection_socket_descriptor = accept(server_socket_descriptor, (struct sockaddr*)&client_sock, &slen);
                //fcntl(connection_socket_descriptor, F_SETFL, O_NONBLOCK); <--- ta komenda sprawia ze nie czeka na read
                if (connection_socket_descriptor < 0) {
                    fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda dla połączenia.\n", argv[0]);
                    exit(1);
                }

                event.events = EPOLLIN | EPOLLRDHUP;
                event.data.fd = connection_socket_descriptor;

                if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connection_socket_descriptor, &event) == -1) {
                    fprintf(stderr, "Blad epoll_ctl ADD dla klawiatury\n");
                    close(epoll_fd);
                    return 1;
                }

                char* buf[100] = {};
                int read_user = read(connection_socket_descriptor, buf, sizeof(buf));

                //char* temp;
                *temp = malloc(strlen(path)+1);
                strcpy(temp, path);

                connectUser(buf, temp);
                map_clients[counter].path = temp;

                printBreak();
                printf("Operacja ACCEPT dla deskryptora: %d zakonczona sukcesem\n", connection_socket_descriptor);
                printBreak();
                printf("\n");

                map_clients[counter].key = connection_socket_descriptor;
                map_clients[counter].var = " ";

                //handleConnection(connection_socket_descriptor, t_data_ptr, array, path, epoll_fd, &event, events);

            }
            else{
                printf("Tu beda komendy\n");
                printf("%d\n", events[i].data.fd);
                KeyFunction(events[i].data.fd, connection_socket_descriptor, temp);
            }
        }
    }

    // zamknięcie gniazda
    close(connection_socket_descriptor);

    // usuń mutexy
        //for (int i = 0; i < 3; i++)
            //pthread_mutex_destroy(locks[i]);
    //pthread_mutex_destroy(&(t_data_ptr->thread_data_mutex));

    // uwalnianie pamięci
    free(t_data_ptr->client_socketfd);
    free(t_data_ptr);

    return(0);
}
