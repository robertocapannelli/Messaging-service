#ifndef MESSAGING_SERVICE_UTILS_H
#define MESSAGING_SERVICE_UTILS_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

#define DATABASE "../database/test.db"

#define USER_TABLE "user"
#define MESSAGE_TABLE "message"

#define EMAIL_COLUMN "email"
#define PASSWORD_COLUMN "password"
#define FROM_COLUMN "from_user"
#define TO_COLUMN "to_user"
#define MESSAGE_COLUMN "message"
#define TIMESTAMP_COLUMN "timestamp"
#define ROWID_COLUMN "rowid"

//Instance of the database
sqlite3 *db;
sqlite3_stmt *stmt;

int open_connection(int result);

#endif //MESSAGING_SERVICE_UTILS_H