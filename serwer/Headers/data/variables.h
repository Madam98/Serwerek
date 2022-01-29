#pragma once

#ifndef SERWER_VARIABLES_H
#define SERWER_VARIABLES_H

#define SERVER_PORT 1235
#define QUEUE_SIZE 5
#define COMMAND_SIZE 6

#define MAX_EVENTS 20
#define READ_SIZE 10
#define MAX_LENGTH 1000
char* commands[6] = {"touch", "share", "list", "delete", "copy", "rename"};
int server_socket_descriptor;
int connection_socket_descriptor;
int bind_result = -1;
int listen_result;
char reuse_addr_val = 1;
struct sockaddr_in server_address;
int max_num_of_clients = 3;
char *dirname = "DOCUMENTS";

#endif /* !SERWER_VARIABLES_H */
