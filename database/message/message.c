#include "message.h"

/**
 * This a callback requested from the sqlite3 standard
 */
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

/**
 * Insert a new message in the database
 * @param from - the email where the message came from
 * @param to - the email where the message is going
 * @param message - the text sent
 * @param timestamp
 * @return returns 0 if the message has been successfully added
 */
int insert_message(char *from, char *to, char *message, int timestamp){
    char *sql;
    int result = 0;
    char *error;

    open_connection(result);

    //Allocate enough memory to store the sql statement
    sql = malloc(sizeof(char *) * 5000);

    //Add the sql statement string to the allocated memory
    sprintf(sql,
            "INSERT INTO %s (%s, %s, %s, %s) VALUES ('%s', '%s', '%s', %d )",
            MESSAGE_TABLE,
            FROM_COLUMN,
            TO_COLUMN,
            MESSAGE_COLUMN,
            TIMESTAMP_COLUMN,
            from,
            to,
            message,
            timestamp);

    printf("sql statement: %s", sql);
    //Execute a SQL statement
    result = sqlite3_exec(db, sql, callback, 0, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s", error);
        sqlite3_free(error);
        exit(EXIT_FAILURE);
    }

    //Close the connection
    sqlite3_close(db);

    //Free the memory allocated for the sql statement
    free(sql);

    return 0;
}

/**
 * Delete a message from the database
 * @param rowid the autoincrement int attached to each rows as sqlite3 standard such an ID unique
 * @return returns 0 if the message has been successfully deleted
 */
int delete_message(int rowid){
    char *sql;
    int result = 0;
    char *error;

    //Open connection
    open_connection(result);

    //Allocate enough memory to store the sql statement
    sql = malloc(sizeof(char *) * 1000);

    //Add the sql statement string to the allocated memory
    sprintf(sql, "DELETE FROM %s WHERE %s = '%d'", MESSAGE_TABLE, ROWID_COLUMN, rowid);

    //Execute a SQL statement
    result = sqlite3_exec(db, sql, callback, 0, &error);
    if(result != SQLITE_OK){
        fprintf(stderr, "SQL error: %s", error);
        sqlite3_free(error);
        exit(EXIT_FAILURE);
    }
    puts("The message has been deleted successfully!");

    //Close the connection
    sqlite3_close(db);

    //Free memory allocated for the sql statement
    free(sql);

    return 0;
}