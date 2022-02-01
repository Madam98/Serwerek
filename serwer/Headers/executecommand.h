
#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#include <Headers/commands/add.h>
#include <Headers/commands/touch.h>
#include <Headers/commands/share.h>
#include <Headers/commands/list.h>
#include <Headers/commands/delete.h>
#include <Headers/commands/copy.h>
#include <Headers/commands/rename.h>


#ifndef SERWER_EXECUTECOMMAND_H
#define SERWER_EXECUTECOMMAND_H

void ExecuteCommand(char *user_message, int client_socket, struct clients_struct* client_data){

    char** tokens;
    int choose_command;
    int i;
    char* name = client_data->name;

    //ODCZYTAJ WIADOMOSC OD KLIENTA OBSUGIWANEGO PRZEZ TEN WATKEKA FUNKCJE
    if (strlen(user_message) > 0) {
        printBreak();
        printf("Jestem na kliencie:\t\t\t %d\n",    client_socket);
        printf("Odczytane:\t\t\t\t\t %s\n",         user_message);
        //buf[strcspn(user_message, "\n")] = 0; //<---- USUWA ENTER ZE STRINGA!

        /*
        if (read_message == -1) {
            printf("Błąd przy próbie odczytu z gniazda %d\n", client_socket);
            exit(-1);
        }
        */
        char *arguments[100] = {};
        //memset(*arguments, 0, strlen(*arguments));

        choose_command = readCommand(tokens, user_message, arguments);
        printBreak();

        //char* temp = malloc(strlen(path)+1);
        //strcpy(temp, path);

        for (i = 0; i < 5; i++) {
            printf("Wynik arguments[%d]: %s\n", i, arguments[i]);
        }
        printf("\n");
        printBreak();
        printf("Wynik rzutowania komendy: %d\n", choose_command);

        switch (choose_command) {
            case 0:
                printf("\t KOMENDA: ADD\n");
                printBreak();
                printf("\n");
                int rozmiar = strlen(arguments);
                char* path = client_data->path;
                //strcpy(path, &client_data->path);
                addCommand(path, name, arguments);
                break;
            case 1:
                printf("\t KOMENDA: TOUCH\n");
                printBreak();
                //printf("\n");
                touchCommand(&name, arguments);
                break;
            case 2:
                printf("\t KOMENDA: SHARE\n");
                printBreak();
                printf("\n");
                //shareCommand();
                break;
            case 3:
                printf("\t KOMENDA: LIST\n");
                printBreak();
                printf("\n");
                //listCommand(user);
                break;
            case 4:
                printf("KOMENDA: DELETE\n");
                printBreak();
                printf("\n");
                //deleteCommand(user, arguments);
                break;
            case 5:
                printf("KOMENDA: COPY\n");
                printBreak();
                printf("\n");
                //copyCommand(user);
                break;
            case 6:
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



#endif /* !SERWER_EXECUTECOMMAND_H */
