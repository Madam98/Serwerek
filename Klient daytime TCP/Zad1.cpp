#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

// IPv4 AF_INET sockets:
struct sockaddr_in_my {
    short            	sin_family;   //AF_INET, AF_INET6
    unsigned short   	sin_port;     
    struct in_addr	    sin_addr;     
    char             	sin_zero[8];  // zero this if you want to
};

struct in_addr_my {
    unsigned long s_addr;          // load with inet_pton()
};

struct sockaddr_my {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};

char textTab[100];

int main(int argc, char *argv[]){
	struct sockaddr_in_my server_addr;
	int my_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	if (my_socket == -1){
		printf("Socket nie mowi dzien dobry\n");
		return -1;
	}
	else{
		printf("Udalo sie przypisac socket\n");
	}
	int port_name = strtol(argv[2], NULL, 10);
	
	memset(&server_addr, 0, sizeof(struct sockaddr_in_my));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_name);
	server_addr.sin_addr.s_addr = inet_pton(AF_INET, argv[1], &(server_addr.sin_addr));
	
	int des = connect(my_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	if (des != 0){
		printf("Nie udalo sie polaczyc\n");
		printf("%d",errno);
		return -1;
	}

	printf("Udało sie polaczyc! :%d\n", des);
	close(my_socket);
	return 0;
}
