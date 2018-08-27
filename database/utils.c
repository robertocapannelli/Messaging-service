#include "utils.h"

/**
 * Open a connection to DATABASE defined in the header
 * @param result get the result from sqlite3 functions
 * @return returns 0 in case of success
 */
int open_connection(int result){
    //Open a database that already exist
    result = sqlite3_open(DATABASE, &db);
    if (result) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    return 0;
}