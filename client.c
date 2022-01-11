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

#define BUF_SIZE 1024
#define NUM_THREADS 5

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

    char* data;
    data = "data";
    printf("%s\n", data);

    printf("%s\n", th_data->read);

    printf("%s\n", data);

    //write((*th_data).server_descriptor, "Adam_Dokumenty", 6);

    write((*th_data).server_descriptor, "list", 6);
    //send((*th_data).server_descriptor, (const void*)(*th_data).read, strlen((*th_data).read), 0);

    //zamkniecie watku

    pthread_exit(NULL);
}


//funkcja obslugujacaca polaczenie z serwerem
void handleConnection(int connection_socket_descriptor) {
    //wynik funkcji tworzacej watek
    int create_result = 0;

    //uchwyt na watek
    pthread_t thread1;

    //dane, ktore zostana przekazane do watku
    struct thread_data_t t_data;

    t_data.server_descriptor = connection_socket_descriptor;
    //t_data.read = "touch";

    printf("%s\n", t_data.read);

    create_result = pthread_create(&thread1, NULL, ThreadBehavior, (void *)&t_data);
    printf("%d\n", create_result);
    if (create_result){
        printf("Blad przy probie utworzenia watku, kod bledu: %d\n", create_result);
        exit(-1);
    }
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
    printf("%s\n", t_data.read);

    create_result = pthread_create(&thread1, NULL, ThreadRequest, (void *)&t_data);
    printf("%d\n", create_result);
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

    connection_socket_descriptor = socket(PF_INET, SOCK_STREAM, 0);
    if (connection_socket_descriptor < 0){
        fprintf(stderr, "%s: Blad przy probie utworzenia gniazda.\n", argv[0]);
        exit(1);
    }

    memset(&server_address, 0, sizeof(struct sockaddr));
    server_address.sin_family = AF_INET;
    memcpy(&server_address.sin_addr.s_addr, server_host_entity->h_addr, server_host_entity->h_length);
    server_address.sin_port = htons(atoi(argv[2]));

    connect_result = connect(connection_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
    if (connect_result < 0)
    {
        fprintf(stderr, "%s: Blad przy probie podlczenia z serwerem (%s:%i).\n", argv[0], argv[1], atoi(argv[2]));
        exit(1);
    }

    //printf("Halo\n");
    handleConnection(connection_socket_descriptor);

    while(1){
        handleRequest(connection_socket_descriptor);
    }

    sleep(5);
    close(connection_socket_descriptor);
    return 0;
}

/* CONFIGURE FILE
cmake_minimum_required(VERSION 3.21)
project(client C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS -pthread)

find_package(Threads REQUIRED)

add_executable(client main.c)
target_link_libraries(client pthread)


*/
