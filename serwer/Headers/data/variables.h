#pragma once

#ifndef SERWER_VARIABLES_H
#define SERWER_VARIABLES_H

#define SERVER_PORT 1235
#define QUEUE_SIZE 10
#define COMMAND_SIZE 6

#define MAX_EVENTS 20
#define MAXLINE 100
#define READ_SIZE 10
#define MAX_LENGTH 1000
//char* commands[6] = {"touch", "share", "list", "delete", "copy", "rename"};

enum commands{
    add,
    touch,
    share,
    list,
    delete,
    copy,
    newname
};

const static struct{
    const char* key;
    enum commands var;
}PKW_converter[]= {
        {"add",     add},
        {"touch",   touch},
        {"share",   share},
        {"list",    list},
        {"delete",  delete},
        {"copy",    copy},
        {"newname",  newname}
};
int server_socket_descriptor;
int client_socket_descriptor;
int bind_result = -1;
int listen_result;
char reuse_addr_val = 1;

struct sockaddr_in server_address;

int max_num_of_clients = 3;
char *dirname = "DOCUMENTS";





#endif /* !SERWER_VARIABLES_H */
