#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#ifndef SERWER_THREADFUNCTIONS_H
#define SERWER_THREADFUNCTIONS_H


void nowConnectedInfo(struct thread_data_t t_data_ptr){
    printBreak();
    printf("Obecnie połączone gniazda:\n");
    print_array_content(t_data_ptr.client_socketfd, t_data_ptr.max_number_of_clients);
    printBreak();
}

// funkcja opisująca zachowanie wątku - musi przyjmować argument typu (void *) i zwracać (void *)
void *KeyFunction(char* user_buffer, int client_socket, char* path){

    char* buf[40];
    char** tokens;
    int choose_command;
    int read_message;
    int i;

    struct user_data strUser;

    //char* path;
    //strcpy(path, strUser.path);
    //ODCZYTAJ WIADOMOSC OD KLIENTA OBSUGIWANEGO PRZEZ TEN WATKEK
    read_message = read(client_socket, buf, sizeof(buf));

    if (read_message > 0) {
        printBreak();
        printf("Odczytane:\t\t\t\t\t %s\n", buf);
        printf("Na sockecie:\t\t\t\t %d\n", client_socket);
        buf[strcspn(buf, "\n")] = 0; //<---- USUWA ENTER ZE STRINGA!
        if (read_message == -1) {
            printf("Błąd przy próbie odczytu z gniazda %d\n", client_socket);
            exit(-1);
        }
        char *arguments[100] = {};
        //memset(*arguments, 0, strlen(*arguments));
        //choose_command = readCommand(tokens, buf, arguments);
        printBreak();

        //char* temp;
        char* temp = malloc(strlen(path)+1);
        strcpy(temp, path);

        //strUser.user_socket = connection_socket_descriptor;
        strUser.path = path;

        for (i = 0; i < 5; i++) {
            printf("Wynik arguments[%d]: %s\n", i, arguments[i]);
        }
                printf("\n");
                printBreak();
                printf("Wynik rzutowania komendy: %d\n", choose_command);
                memset(buf, 0, 100);
                switch (choose_command) {
                    case 0:
                        printf("\t KOMENDA: TOUCH\n");
                        printBreak();
                        printf("\n");
                        touchCommand(strUser, arguments);
                        break;
                    case 1:
                        printf("\t KOMENDA: SHARE\n");
                        printBreak();
                        printf("\n");
                        //shareCommand();
                        break;
                    case 2:
                        printf("\t KOMENDA: LIST\n");
                        printBreak();
                        printf("\n");
                        //listCommand(user);
                        break;
                    case 3:
                        printf("KOMENDA: DELETE\n");
                        printBreak();
                        printf("\n");
                        //deleteCommand(user, arguments);
                        break;
                    case 4:
                        printf("KOMENDA: COPY\n");
                        printBreak();
                        printf("\n");
                        //copyCommand(user);
                        break;
                    case 5:
                        printf("KOMENDA: RENAME\n");
                        printBreak();
                        printf("\n");
                        //renameCommand(user, arguments);
                        break;
                    default:
                        printf("KOMENDA: NIEZNANA :-(\n");
                        printBreak();
                        printf("\n");
                        pthread_exit(NULL);
                        break;
                }
                for (i = 0; i < 40; i++) {
                    //free(arguments[i]);
                    arguments[i] = NULL;
                }
                //free(arguments);
                //printf("Zamykam watek\n");
            }
}



// funkcja opisująca zachowanie wątku - musi przyjmować argument typu (void *) i zwracać (void *)
void *ThreadBehavior(void *t_data){
    pthread_detach(pthread_self()); //<--wątek odłączony, jak się odblokuje watek skończy automatycznie zwalniane zasoby

    //struct thread_data_t *t_data_ptr = (struct thread_data_t *)t_data;
    struct user_data *user = (struct user_data*)t_data;

    //int client_socket =  t_data_ptr->last_connected;
    int client_socket = user->user_socket;

    char user_buffer[100];              //<--do czytania NAZWY UZYTKOWNIKA
                     //<--do czytania WIADOMOSCI OD UZYTKOWNIKA
    int write_result;
    char** tokens;
    int choose_command;

    //nowConnectedInfo(*t_data_ptr);
    //pthread_mutex_unlock(&(t_data_ptr->thread_data_mutex));

    //PODLACZENI UZYTKOWNICY
    printf("Cos sie dzieje!!!!! \n");
    //char want[10];
    //read(client_socket, want, sizeof(user_buffer));
    //char answer[6] = "answer";
    //send(client_socket, answer, sizeof(answer), MSG_NOSIGNAL);
    //memset(client_socket, 0, 100);
    int read_user = read(client_socket, user_buffer, sizeof(user_buffer));
    //connectUser_user_data(user_buffer, );

    //ODCZYTAJ WIADOMOSC OD KLIENTA OBSUGIWANEGO PRZEZ TEN WATKEK

    while (choose_command != "q") {
        if (user->epoll_events[1].data.fd == 0) {

            //read(client_socket, want, sizeof(user_buffer));
            //printf("%s\n", want);

            //send(client_socket, answer, sizeof(answer), MSG_NOSIGNAL);
            char buf[100];

            int read_message;

            read_message = read(client_socket, buf, sizeof(user));


            if (read_message > 0) {
                printBreak();
                printf("Odczytane:\t\t\t\t\t %s\n", buf);
                printf("Na sockecie:\t\t\t\t %d\n", client_socket);
                buf[strcspn(buf, "\n")] = 0; //<---- USUWA ENTER ZE STRINGA!
                if (read_message == -1) {
                    printf("Błąd przy próbie odczytu z gniazda %d\n", client_socket);
                    exit(-1);
                }

                int i;

                char *arguments[40];
                //choose_command = readCommand(tokens, buf, arguments);
                printBreak();

                for (i = 0; i < 5; i++) {
                    printf("Wynik arguments[%d]: %s\n", i, arguments[i]);
                }

                printf("\n");

                printBreak();
                printf("Wynik rzutowania komendy: %d\n", choose_command);
                memset(buf, 0, 100);
                switch (choose_command) {
                    case 0:
                        printf("\t KOMENDA: TOUCH\n");
                        printBreak();
                        printf("\n");
                        touchCommand(user, arguments);
                        break;
                    case 1:
                        printf("\t KOMENDA: SHARE\n");
                        printBreak();
                        printf("\n");
                        shareCommand();
                        break;
                    case 2:
                        printf("\t KOMENDA: LIST\n");
                        printBreak();
                        printf("\n");
                        listCommand(user);
                        break;
                    case 3:
                        printf("KOMENDA: DELETE\n");
                        printBreak();
                        printf("\n");
                        deleteCommand(user, arguments);
                        break;
                    case 4:
                        printf("KOMENDA: COPY\n");
                        printBreak();
                        printf("\n");
                        copyCommand(user);
                        break;
                    case 5:
                        printf("KOMENDA: RENAME\n");
                        printBreak();
                        printf("\n");
                        renameCommand(user, arguments);
                        break;
                    default:
                        printf("KOMENDA: NIEZNANA :-(\n");
                        printBreak();
                        printf("\n");
                        pthread_exit(NULL);
                        break;
                }
                for (i = 0; i < 40; i++) {
                    //free(arguments[i]);
                    arguments[i] = NULL;
                }
                //free(arguments);
                //printf("Zamykam watek\n");
            }
        }
    }
    printf("Zamykam watek\n");

}

#endif /* !SERWER_THREADFUNCTIONS_H */
