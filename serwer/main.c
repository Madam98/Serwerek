#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>
#include <Headers/file_opearation/readstring.h>
#include <Headers/file_opearation/textAnimation.h>
#include <Headers/connect_operation/createconnectionfunctions.h>
#include <Headers/handler/sigsegv.h>
#include <Headers/file_opearation/createfolder.h>
#include <Headers/executecommand.h>
#include <Headers/lists.h>                //<--- IMPLEMENTACJA LISTY!!! JEEEEEEJ
#include <Headers/insertchar.h>
#include <Headers/deletechar.h>
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
    //struct thread_data_t *t_data_ptr = malloc(sizeof(struct thread_data_t));
    struct epoll_event event, events[MAX_EVENTS];
    struct clients_struct our_clients_data;

    //PRZYGOTOWYWANIE STRUKTUR
    initAdreessServer(&server_address);

    //UTWORZENIE GNIAZDA DO POLACZENIA Z SERWEREM
    server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    checkServerSocketDescriptor(server_socket_descriptor, argv[0]);
    setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr_val, sizeof(reuse_addr_val));
    socketInfo(server_socket_descriptor);
    //fcntl(server_socket_descriptor, F_SETFL, O_NONBLOCK);

    //STWORZENIE EPOLL
    memset(&events, 0, sizeof(struct epoll_event));
    int epoll_fd    = createEpoll();
    //event.events    = EPOLLIN|EPOLLET;                 //event.events = EPOLLIN;
    event.events    = EPOLLIN;
    event.data.fd   = server_socket_descriptor;       //<---serwer
    createEpollEvDataServer(epoll_fd, event);
    event.data.fd   = 0;
    createEpollEvDataClient(epoll_fd, event);

    //DOWIAZANIE ADRESU SERWERA DO STWORZONEGO GNIAZDA
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_flags     = SA_SIGINFO;
    action.sa_sigaction = handler;
    sigaction(SIGSEGV, &action, NULL);

    //POWIAZANIE ADRESU Z GNIAZDEM
    bind_result = bind(server_socket_descriptor, (struct sockaddr *) &server_address, sizeof(struct sockaddr));
    while(bind_result == -1) {
        red();
        printf("Powyzszy port %d jest zajety! Czekam na zwolnienie portu...\n", SERVER_PORT);
        reset();
        textAnimation();
        bind_result = bind(server_socket_descriptor, (struct sockaddr *) &server_address, sizeof(struct sockaddr));
    }
    checkBindResult(bind_result, argv[0]);
    bindInfo();

    //WLACZENIE NASLUCHIWANIA NA UTWORZONYM GNIEZDZIE
    listen_result = listen(server_socket_descriptor, QUEUE_SIZE);
    checkListen(listen_result, argv[0]);
    infoListen();

    printf("\n\n\n");

    //STWORZENIE FOLDERU Z POTENCJLANYMI DOKUMENTAMI(jesli nie istnieja)
    char* path = getenv("PWD");
    char* info = "W folderu z wykonywanym plikiem musi znajdowac sie folder DOCUMENTS\n";
    folderInfo(path, info);

    //OBSLUGA POLACZEN Z UZYTKOWNIKAMI
    int nfds;
    int i;
    int counter = 0;
    int socket_fd;
    ssize_t n;
    char temp[MAXLINE];
    char line[MAXLINE];
    char *wsk_temp = temp;


    while(1){
        nfds = epoll_wait(epoll_fd, events,MAX_EVENTS, -1);
        printBreak();
        printf("Wskaznik NFDS:\t\t\t\t\t\t %d\n", nfds);
        for (i = 0; i < nfds; ++i) {
            if (events[i].data.fd == server_socket_descriptor) { //If a new SOCKET user is detected to be connected to a bound SOCKET port, establish a new connection.
                //---------------------------------
                struct sockaddr_in clientaddr;
                socklen_t clilen = sizeof(clientaddr);
                client_socket_descriptor = accept(server_socket_descriptor, (struct sockaddr *) &clientaddr, &clilen);
                //fcntl(client_socket_descriptor, F_SETFL, O_NONBLOCK, 1); //<--- ta komenda sprawia ze nie czeka na read
                if (client_socket_descriptor < 0) {
                    fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda dla połączenia.\n", argv[0]);
                    exit(1);
                }
                //---------------------------------

                //---------------------------------
                char *str = inet_ntoa(clientaddr.sin_addr);
                printf("Przylaczony klient o ");

                green();
                printf("DESKRYPTORZE: \t %d\n", client_socket_descriptor);
                reset();
                //---------------------------------

                //---------------------------------
                event.events = EPOLLIN|EPOLLRDHUP;                 //event.events = EPOLLIN | EPOLLRDHUP;

                event.data.fd = client_socket_descriptor;
                //printf("Przylaczam client_socket:\t %d\n", client_socket_descriptor);
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket_descriptor, &event) == -1) {
                    fprintf(stderr, "Blad epoll_ctl ADD dla klawiatury\n");
                    close(epoll_fd);
                    return 1;
                }

                //STWORZ STRUKTURE Z DANYMI KLIENTA (PRZYDA SIE DO PRZEKAZYWANIA DANYCH DO WYKONYWANIA POLECEN)
                our_clients_data.path = (char*)malloc(100);
                strcpy(our_clients_data.path, path);
                our_clients_data.name            = "";
                our_clients_data.client_socket   = client_socket_descriptor;
                our_clients_data.counter         = counter;
                our_clients_data.file_descriptor = 0;
                our_clients_data.global_path     = path;
                our_clients_data.FLAG_TO_SENT    = 0;
                our_clients_data.FLAG_DELETED    = 0;
                /*
                for (i = 0; i < 10; i++){
                    our_clients_data.share_path[i] = 0;
                }

                for (i = 0; i < 10; i++){
                    our_clients_data.send_share_file_descriptor[i] = 0;
                }*/
                //memset(our_clients_data.share_path, 0, 10);

                insertFirst(counter, our_clients_data);
                counter++;
                printBreak();
            }

            else if(events[i].events&EPOLLRDHUP){
                if ((socket_fd = events[i].data.fd) < 0)
                    continue;
                printList();
                printf("\n");
                red();
                printf("ZAMYKAM POLACZENIE!!!\n");
                reset();

                int j;
                int found;
                struct node *foundLink;
                printList();
                printf("\n");
                for (j = 0; j < length(); j++) {

                    //foundLink = find(our_clients_data.counter);
                    foundLink = find(j);
                    //foundLink = find(events[i].data.fd);
                    if (events[i].data.fd == foundLink->client.client_socket) {
                        found = j;
                        break;
                    }
                }
                foundLink->client.FLAG_DELETED = 1;
                //delete_list(our_clients_data.counter);
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, socket_fd, &event);
            }

            else if (events[i].events&EPOLLIN) { //If the user is already connected and receives data, read in.
                    printf("Event:\t\t\t\t\t\t\t\t EPOLLIN\n");
                    memset(line, 0, MAXLINE);
                    memset(temp, 0, MAXLINE);
                    if ((socket_fd = events[i].data.fd) < 0)
                        continue;
                    printf("Socket klienta:\t\t\t\t\t\t %d\n", socket_fd);
                    if ((n = read(socket_fd, line, MAXLINE)) < 0) {
                        if (errno == ECONNRESET) {
                            close(socket_fd);
                            events[i].data.fd = -1; //<-- ustawiamy -1 aby inne ify nie obslugiwaly juz zdarzenia
                        } else //<-- Jesli blad odczytu koncowego deskryptora
                            printf("readline error\n");
                    } else if (n == 0) {
                        close(socket_fd);
                        events[i].data.fd = -1;
                    }
                    if (n < MAXLINE - 2)
                        line[n] = '\0';

                    strncpy(temp, line, n);
                    temp[strcspn(line, "\n")] = 0; //<---- USUWA ENTER ZE STRINGA!
                    //-------------------------------------------------------------------------------
                    int j;
                    int found;
                    struct node *foundLink;
                    printList();
                    printf("\n");
                    for (j = 0; j < length(); j++) {

                        //foundLink = find(our_clients_data.counter);
                        foundLink = find(j);
                        //foundLink = find(events[i].data.fd);
                        if (events[i].data.fd == foundLink->client.client_socket) {
                            found = j;
                            break;
                        }
                    }
                    //printf("ExecuteCommand:\t\t\t\t\t\t %d\n", j);
                    //printf("Socket_fd: %d\n", socket_fd);

                    //-------------------------------------------------------------------------------
                    //struct clients_struct* temp_struct = &our_clients_data[found];
                    struct clients_struct* temp_struct = &foundLink->client;

                    //Example(wsk_temp, socket_fd, temp_struct);
                    ExecuteCommand(wsk_temp, socket_fd, temp_struct);
                    ShowListFile(temp_struct);
                    ShowClients();

                    //printf("WPISANY FILE DESCRIPTOR: %d\n", temp_struct->file_descriptor);

                    //ShowClients(our_clients_data);

                    //event.data.fd = socket_fd;
                    //Set Write Action Events for Annotation
                    //event.events = EPOLLOUT|EPOLLET;
                    //Modify the event to be handled on sockfd to EPOLLOUT
                    //epoll_ctl(epoll_fd, EPOLL_CTL_MOD, socket_fd, &event);
                    //printf("KONIEC EPOLLIN\n");
                    //printf("Socket_fd: %d\n", socket_fd);
                    printf("\n\n");
                }

            else if (events[i].events&EPOLLOUT){ //If there is data to send
                printf("Event:\t\t\t\t\t\t EPOLLOUT\n");
                socket_fd = events[i].data.fd;
                write(socket_fd, line, n);

                //Setting file descriptors for read operations
                //event.data.fd = socket_fd;

                //Set Read Action Events for Annotation
                //event.events = EPOLLIN|EPOLLET;

                //Modify the event to be processed on sockfd to EPOLIN
                //epoll_ctl(epoll_fd,EPOLL_CTL_MOD,socket_fd,&event);
            }

        }
    }
    return(0);
    close(server_socket_descriptor);
}