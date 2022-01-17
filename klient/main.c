#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/epoll.h>

#define MAXBUF 1024
#define NUM_THREADS 5
#define MAX_EPOLL_EVENTS 64

//STWORZENIE WATKU WYSYLAJACY ZAPYTANIA KONTROLNE
//co 20 sekund

//struktura zawierajaca dane, ktołre zostana przekazane do watku
struct thread_data_t
{
    int server_descriptor;
    char read;
};

//wskaznik na funkcjr opisujaca zachowanie watku
void *ThreadBehavior(void *t_data)
{
    struct thread_data_t *th_data = (struct thread_data_t*)t_data;
    //dostep do całej struktury: (*th_data).pole


    char buf0[12]  = "uzytkownik1";
    char buf1[30]  = "touch Adam lubi orzeszki";

    sleep(4);

    printf("Wysylam nazwe uzytkownika: %s\n", buf0);
    write((*th_data).server_descriptor, buf0, 12);

    sleep(2);

    printf("Wysylam nazwe uzytkownika: %s\n", buf1);
    write((*th_data).server_descriptor, buf1, 30);



    //send((*th_data).server_descriptor, (const void*)(*th_data).read, strlen((*th_data).read), 0);


    pthread_exit(NULL);
}


//funkcja obslugujacaca polaczenie z serwerem
void handleConnection(int connection_socket_descriptor) {
    //wynik funkcji tworzacej watek
    int create_result = 0;

    //uchwyt na watek
    pthread_t thread1;

    int i;
    int num_ready;

    /*---Wait for socket connect to complete---*/

    //num_ready = epoll_wait(epfd, events, MAX_EPOLL_EVENTS, 10000/*timeout*/);

    /*for(i = 0; i < num_ready; i++) {
        if(events[i].events & EPOLLIN) {
            printf("Socket %d connected\n", events[i].data.fd);
        }
    }
    char buffer[MAXBUF];
    */

    //dane, ktore zostana przekazane do watku
    struct thread_data_t t_data;

    t_data.server_descriptor = connection_socket_descriptor;
    //t_data.read = "touch";

    //printf("%s\n", t_data.read);

    create_result = pthread_create(&thread1, NULL, ThreadBehavior, (void *)&t_data);
    printf("%d\n", create_result);
    if (create_result){
        printf("Blad przy probie utworzenia watku, kod bledu: %d\n", create_result);
        exit(-1);
    }
    //printf("Czekam jak odbiore\n");
    //char buf[100];
    //read(connection_socket_descriptor, buf, 12);

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
    argv[2] = "1234";
    argv[3] = "Adam_Example"; //<----user

    // if (argc != 3){
    //     fprintf(stderr, "Zly sposob uzycia: %s server_name port_number\n", argv[0]);
    //     exit(1);
    // }

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

    //int epfd = epoll_create(1);
    //struct epoll_event event;
    //event.events = EPOLLIN; // Cann append "|EPOLLOUT" for write events as well
    //event.data.fd = connection_socket_descriptor;
    //epoll_ctl(epfd, EPOLL_CTL_ADD, connection_socket_descriptor, &event);

    memset(&server_address, 0, sizeof(struct sockaddr));
    server_address.sin_family = AF_INET;
    memcpy(&server_address.sin_addr.s_addr, server_host_entity->h_addr, server_host_entity->h_length);
    server_address.sin_port = htons(atoi(argv[2]));

    connect_result = connect(connection_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
    while (connect_result < 0)
    {
        fprintf(stderr, "%s: Blad przy probie podlczenia z serwerem (%s:%i).\n", argv[0], argv[1], atoi(argv[2]));
        sleep(5);
        connect_result = connect(connection_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
        //exit(1);
    }

    printf("Chce odebrac\n");
    //sleep(4);

    //printf("Halo\n");
    handleConnection(connection_socket_descriptor);

    sleep(20);
    char buf[100];
    while(1) {
        recv(connection_socket_descriptor, buf, 12, 0);
        printf("Odebralem wiadomosc\n");
    }
    //sleep(10000);
    close(connect_result);
    return 0;
}

