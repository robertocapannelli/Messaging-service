#ifndef MESSAGING_SERVICE_USER_H
#define MESSAGING_SERVICE_USER_H

#define DB_USER_DEBUG 0

#include "../db_utils.h"
#include <string.h>

int insert_user(char *email, char *password);
int delete_user(char *email);
int select_user(const char *email_user, const char *password_user);

#endif //MESSAGING_SERVICE_USER_H