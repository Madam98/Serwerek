
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
#include <Headers/commands/enter_file.h>
#include <Headers/commands/message.h>


#ifndef SERWER_EXECUTECOMMAND_H
#define SERWER_EXECUTECOMMAND_H

void ExecuteCommand(char* user_message, int client_socket, struct clients_struct* client_data){
    int choose_command;
    int i;
    char* name = client_data->name;
    char* arguments[100] = {};

    //ODCZYTAJ WIADOMOSC OD KLIENTA OBSUGIWANEGO PRZEZ TEN WATKEKA FUNKCJE
    if (strlen(user_message) > 0) {
        //********************************************************************
        printBreak();
        printf("Jestem na kliencie:\t\t\t %d\n", client_socket);
        printf("Odczytane:\t\t\t\t\t %s\n", user_message);
        printf("\nPARAMETRY CLIENT\n");
        printf("client_data->client_socket:  %d\n", client_data->client_socket);
        printf("client_data->path:\t\t\t %s\n", client_data->path);
        printf("client_data->name:\t\t\t %s\n\n", client_data->name);
        //********************************************************************
        choose_command = readCommand(user_message, arguments);

        printBreak();

        for (i = 0; i < 5; i++) {
            printf("Wynik arguments[%d]: %s\n", i, arguments[i]);
        }

        printf("\n");
        printBreak();
        printf("Wynik rzutowania komendy: %d\n", choose_command);

        int size_of_array = 0;
        while (arguments[size_of_array] != NULL){
            ++size_of_array;
        }
        switch (choose_command) {
            case 0:
                printf("\t KOMENDA: ADD\n");
                addCommand(client_data, arguments, size_of_array);
                break;
            case 1:
                printf("\t KOMENDA: TOUCH\n");
                touchCommand(client_data, arguments, size_of_array);
                break;
            case 2:
                printf("\t KOMENDA: SHARE\n");
                shareCommand(client_data, arguments, size_of_array);
                break;
            case 3:
                printf("\t KOMENDA: LIST\n");
                //listCommand(user);
                break;
            case 4:
                printf("\t KOMENDA: DELETE\n");
                deleteCommand(client_data, arguments, size_of_array);
                break;
            case 5:
                printf("\t KOMENDA: COPY\n");
                copyCommand(client_data, arguments, size_of_array);
                break;
            case 6:
                printf("\t KOMENDA: NEWNAME\n");
                renameCommand(client_data, arguments, size_of_array);
                break;

            // OBSLUGA PLIKOW*********
            case 7:
                printf("\t KOMENDA: ENTER - OTWIERAM PLIK\n");
                enter_file(client_data, arguments, size_of_array);
                break;
            case 8:
                printf("\t KOMENDA: MESSAGE\n");
                message(client_data, arguments, size_of_array);
                break;


            // ***********************
            default:
                printf("\t KOMENDA: NIEZNANA :-(\n");
                break;
        }
        printBreak();
        printf("\n");
        for (i = 0; i < 40; i++) {
            arguments[i] = NULL;
        }
        printf("Zamykam funkcje\n");
    }
}

int ShowListFile(struct clients_struct* client_data){

    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(client_data->path);

    if (dr == NULL){  // opendir returns NULL if couldn't open directory
        printf("Could not open current directory" );
        return 0;
    }

    printBreak();
    printf("PLIKI ZNAJDUJACE SIE W FOLDERZE\n\n");
    while ((de = readdir(dr)) != NULL)
        printf("%s\n", de->d_name);
    printBreak();

    closedir(dr);
    return 0;
}

int ShowClients(struct clients_struct* client_data) {
    int i;
    printBreak();
    printf("KLIENCI\n");
    for (i = 0; i < 5; i++){
        if(client_data[i].client_socket != 0) {
            printf("\n");
            printf("Nazwa klienta:\t\t\t %s\n", client_data[i].name);
            printf("Numer socketa:\t\t\t %d\n", client_data[i].client_socket);
            printf("File descriptor: \t\t %d\n", client_data[i].file_descriptor);
            printf("Share descriptor:\t\t %d\n", client_data[i].share_file_descriptor);
            printf("Share with_me_descriptor:%d\n", client_data[i].share_file_descriptor);

            int j;
            for (j = 0; j < 5; j++){
                if(client_data[i].share_user = client_data[j].name && i != j)
                    client_data[j].shared_with_me_descriptors = client_data[i].share_file_descriptor;
            }
        }
    }
    printBreak();
}



void Example(char* user_message, int client_socket, struct clients_struct* client_data){

    char** tokens;
    int choose_command;
    int i;
    char* name = client_data->name;

    //ODCZYTAJ WIADOMOSC OD KLIENTA OBSUGIWANEGO PRZEZ TEN WATKEKA FUNKCJE
    if (strlen(user_message) > 0) {
        printBreak();
        printf("Jestem na kliencie:\t\t\t %d\n",    client_socket);
        printf("Odczytane:\t\t\t\t\t %s\n",         user_message);
        printf("\nPARAMETRY CLIENT\n");

        printf("client_data->client_socket: %d\n",  client_data->client_socket);
        printf("client_data->path:\t\t\t %s\n",     client_data->path);
        printf("client_data->name:\t\t\t %s\n\n",   client_data->name);


        //buf[strcspn(user_message, "\n")] = 0; //<---- USUWA ENTER ZE STRINGA!

        char *arguments[100] = {};
        //memset(*arguments, 0, strlen(*arguments));

        //choose_command = readCommand(tokens, user_message, arguments);
        printBreak();

        //char* temp = malloc(strlen(path)+1);
        //strcpy(temp, path);

        for (i = 0; i < 5; i++) {
            printf("Wynik arguments[%d]: %s\n", i, arguments[i]);
        }
        printf("\n");
        printBreak();
        printf("Wynik rzutowania komendy: %d\n", choose_command);

        int size_of_array = 0;
        while (arguments[size_of_array] != NULL){
            ++size_of_array;
        }

        switch (choose_command) {
            case 0:
                printf("\t KOMENDA: ADD\n");
                //char* path = client_data->path;
                //addCommand(client_data, arguments, size_of_array);
                printBreak();
                printf("\n");
                break;
            case 1:
                printf("\t KOMENDA: TOUCH\n");
                printBreak();
                //printf("\n");
                //touchCommand(&name, arguments);
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
                //pthread_exit(NULL);
                break;
        }
        for (i = 0; i < 40; i++) {
            //free(arguments[i]);
            arguments[i] = NULL;
        }
        //free(arguments);
        printf("Zamykam funkcje\n");
    }
}



#endif /* !SERWER_EXECUTECOMMAND_H */
