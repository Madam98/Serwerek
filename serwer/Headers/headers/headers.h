#pragma once

#ifndef SERWER_HEADERS_H
#define SERWER_HEADERS_H

#define __USE_GNU

#define _GNU_SOURCE
#ifndef REG_EIP
#define REG_EIP 0x23b46F
#endif

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/epoll.h> // for epoll_create1(), epoll_ctl(), struct epoll_event
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <ucontext.h>
#include <time.h>

#endif /* !SERWER_HEADERS_H */


