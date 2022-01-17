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
void *ThreadBehavior(void *t_data){
    pthread_detach(pthread_self()); //<--wątek odłączony, jak się odblokuje watek skończy automatycznie zwalniane zasoby
    struct thread_data_t *t_data_ptr = (struct thread_data_t *)t_data;
    int client_socket =  t_data_ptr->last_connected;
    char user_buffer[100];              //<--do czytania NAZWY UZYTKOWNIKA
    char buf[100];                      //<--do czytania WIADOMOSCI OD UZYTKOWNIKA
    int write_result;
    char** tokens;
    int choose_command;

    nowConnectedInfo(*t_data_ptr);
    pthread_mutex_unlock(&(t_data_ptr->thread_data_mutex));

    //PODLACZENI UZYTKOWNICY
    int read_user = read(client_socket, user_buffer, sizeof(user_buffer));
    connectUser(user_buffer, *t_data_ptr);

    //ODCZYTAJ WIADOMOSC OD KLIENTA OBSUGIWANEGO PRZEZ TEN WATKEK
    int read_message = read(client_socket, buf, sizeof(user_buffer));
    if(read_message > 0){
        printBreak();
        printf("Odczytane:\t\t\t\t\t %s\n", buf);
        printf("Na sockecie:\t\t\t\t %d\n", client_socket);
        buf[strcspn(buf, "\n")] = 0; //<---- USUWA ENTER ZE STRINGA!
        if ( read_message == -1 ) {
            printf("Błąd przy próbie odczytu z gniazda %d\n", client_socket);
            exit(-1);
        }

        //choose_command = readCommand(tokens, buf);
        /*
        char **arguments;
        int i;
        arguments = malloc(40 * sizeof(char*)); //<---nie ma sensu dawac wiecej argumentow
        for (i = 0; i < 40; i++){
            arguments[i] = malloc(50);
        }*/


        char* arguments[40];
        choose_command = readCommand(tokens, buf, arguments);
        printBreak();
        int i;
        for (i = 0; i < 5; i++){
            printf("Wynik arguments[%d]: %s\n", i, arguments[i]);
        }

        printf("\n");

        printBreak();
        printf("Wynik rzutowania komendy: %d\n", choose_command);
        memset(buf, 0, 100);
        switch(choose_command)
        {
            case 0:
                printf("\t KOMENDA: TOUCH\n");
                printBreak();
                printf("\n");
                touchCommand(t_data, arguments);
                //sleep(15);
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
                listCommand(t_data_ptr);
                break;
            case 3:
                printf("KOMENDA: DELETE\n");
                printBreak();
                printf("\n");
                deleteCommand(t_data_ptr);
                break;
            case 4:
                printf("KOMENDA: COPY\n");
                printBreak();
                printf("\n");
                copyCommand(t_data_ptr);
                break;
            case 5:
                printf("KOMENDA: RENAME\n");
                printBreak();
                printf("\n");
                renameCommand(t_data_ptr);
                break;
            default:
                printf("KOMENDA: NIEZNANA :-(\n");
                printBreak();
                printf("\n");
                break;
        }
        printf("Zamykam watek\n");
    }

    /*
            // obsłuż utratę połączenia z klientem
        else if ( read_result == 0)
        {
            //pthread_mutex_lock(&t_data_ptr->client_socketfd_lock);
            clear_array_cell(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients, client_socket);
            //pthread_mutex_unlock(&t_data_ptr->client_socketfd_lock);

            //pthread_mutex_lock(&t_data_ptr->number_of_clients_lock);
            t_data_ptr->number_of_clients--;
            //pthread_mutex_unlock(&t_data_ptr->number_of_clients_lock);

            printf("Połączenie z gniazdem %d zostało zakończone\nObecne połączone gniazda:\n", client_socket);
            print_array_content(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients);
        }

        // wyślij odczytaną wiadomość do wszystkich podłączonych klientów
        // (poza klientem obsługiwanym przez ten wątek)

        //pthread_mutex_lock(&t_data_ptr->client_socketfd_lock);
        for (int i = 0; i < t_data_ptr->max_number_of_clients; i++)
        {
            if(t_data_ptr->client_socketfd[i] != 0 && t_data_ptr->client_socketfd[i] != client_socket)
            {
                write_result = write(t_data_ptr->client_socketfd[i], buf, strlen(buf));
                if (write_result == -1)
                {
                    printf("Błąd przy próbie wysłania wiadomości do klienta\n");
                    exit(-1);
                }
            }
        }
        //pthread_mutex_unlock(&t_data_ptr->client_socketfd_lock);

        // wyczyść bufer
        memset(buf, 0, 100);
    */
    pthread_exit(NULL);
}

#endif /* !SERWER_THREADFUNCTIONS_H */
