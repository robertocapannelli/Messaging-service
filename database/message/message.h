#ifndef MESSAGING_SERVICE_MESSAGE_H
#define MESSAGING_SERVICE_MESSAGE_H

#include "../utils.h"

int insert_message(char *from, char *to, char *message, int timestamp);
int delete_message(int rowid);

#endif //MESSAGING_SERVICE_MESSAGE_H