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


    //printf("Odebralem\n");
}

void *ThreadRequest(void *t_data){
    printf("Sprawdzam odpowiedz\n");

    struct thread_data_t *th_data = (struct thread_data_t*)t_data;
    //dostep do całej struktury: (*th_data).pole

    write((*th_data).server_descriptor, "", 0);

    //zamkniecie watku

    pthread_exit(NULL);

}

void handleRequest(int connection_socket_descriptor){
    //wynik funkcji tworzacej watek
    int create_result = 0;
    //uchwyt na watek
    pthread_t thread1;
    //dane, ktore zostana przekazane do watku
    struct thread_data_t t_data;

    create_result = pthread_create(&thread1, NULL, ThreadRequest, (void *)&t_data);
    //printf("%d\n", create_result);
    if (create_result){
        printf("Blad przy probie utworzenia watku, kod bledu: %d\n", create_result);
        exit(-1);
    }
}


int main (int argc, char *argv[])
{
    int connection_socket_descriptor;
    int connect_result;
    struct sockaddr_in server_address;
    struct hostent* server_host_entity;
    struct epoll_event events[MAX_EPOLL_EVENTS];

    argv[1] = "127.0.0.1";
    argv[2] = "1235";
    argv[3] = "Adam_Example"; //<----user


    server_host_entity = gethostbyname(argv[1]);
    if (! server_host_entity){
        fprintf(stderr, "%s: Nie mozna uzyskac adresu IP serwera.\n", argv[0]);
        exit(1);
    }

    connection_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (connection_socket_descriptor < 0){
        fprintf(stderr, "%s: Blad przy probie utworzenia gniazda.\n", argv[0]);
        exit(1);
    }


    memset(&server_address, 0, sizeof(struct sockaddr));
    server_address.sin_family = AF_INET;
    memcpy(&server_address.sin_addr.s_addr, server_host_entity->h_addr, server_host_entity->h_length);
    server_address.sin_port = htons(atoi(argv[2]));

    connect_result = connect(connection_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
    while (connect_result < 0)
    {
        fprintf(stderr, "%s: Blad przy probie podlaczenia z serwerem (%s:%i).\n", argv[0], argv[1], atoi(argv[2]));
        sleep(5);
        connect_result = connect(connection_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));

    }

    char* buf;

    char znaki[50];
    char want[4] = "want";
    char answer[20] = "";

    while(1){
        printf("\nWpisz cos\n");
        //scanf("%s",&znaki);

        fgets(znaki, 50, stdin);
        //scanf("%[^\n]%*c", znaki);

        //printf("Dlugosc wprowadzonego stringa: %c\n", sizeof(znaki));


        if(strcmp(znaki, "q\n") == 0){
            close(connect_result);
            return(0);
        }


        printf("Wysylam komende uzytkownika:\t %s\n", znaki);
        //send(connection_socket_descriptor, znaki, sizeof(znaki), MSG_CONFIRM);
        int rozmiar = strlen(znaki);

        //printf("Dlugosc wprowadzonego stringa: %d\n", strlen(znaki));
        //printf("Dlugosc wprowadzonego stringa: %d\n", sizeof(znaki));
        //printf("Dlugosc wprowadzonego stringa: %d\n", rozmiar);

        send(connection_socket_descriptor, znaki, rozmiar, MSG_CONFIRM);

    }

    // zamknięcie gniazda
    close(connection_socket_descriptor);

    // usuń mutexy
        //for (int i = 0; i < 3; i++)
            //pthread_mutex_destroy(locks[i]);
    //pthread_mutex_destroy(&(t_data_ptr->thread_data_mutex));


    sleep(10000);
    close(connect_result);
    return 0;
}


    return(0);
}
