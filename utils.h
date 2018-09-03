#ifndef MESSAGING_SERVICE_UTILS_H
#define MESSAGING_SERVICE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/un.h>
#include <string.h>

#define handle_error(msg)\
    do {perror(msg); exit(EXIT_FAILURE);} while (0)

#endif //MESSAGING_SERVICE_UTILS_H
