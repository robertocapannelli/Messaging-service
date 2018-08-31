#include "message.h"
#include <string.h>

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

    //Add the sql query string to the allocated memory
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

    //Add the sql query to the allocated memory
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

/**
 * Get all the messages received for a specific user
 * @param email_user
 * @return returns 0 if the query was successful
 */
int get_received_messages(char *email_user){
    char *sql = NULL;
    int result = 0;

    //Open connection
    open_connection(result);

    //Allocate enough memory to store the sql statement
    sql = malloc(sizeof(char *) * 1000);

    //Add the SQL query to the allocated memory
    sprintf(sql,"SELECT rowid, * FROM %s WHERE %s = '%s'", MESSAGE_TABLE, TO_COLUMN, email_user);

    //Prepare statement to be executed
    int prepare = sqlite3_prepare_v2(db, sql, (int) strlen(sql), &stmt, 0);
    if(prepare != SQLITE_OK){
        fprintf(stderr, "SQL error: %s", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }

    //TODO this is just to test the loop, we should print out to the application
    //Loop over the rows
    while(sqlite3_step(stmt) == SQLITE_ROW){
        printf("\nMESSAGE #%d\nFrom: %s\n%s\n",
                sqlite3_column_int(stmt, 0),
                sqlite3_column_text(stmt, 1),
                sqlite3_column_text(stmt, 3));
        puts("--------------------");
    }

    //Delete the prepared statement
    sqlite3_finalize(stmt);

    //Close the db connection
    sqlite3_close(db);

    //Free the memory allocated
    free(sql);

    return 0;
}

#if DB_MESSAGE_DEBUG
int main(int argc, char* argv[]) {
    int get_msg = get_received_messages("roberto.capannelli@gmail.com");
    if(get_msg != 0){
        perror("Could not get messages");
        exit(EXIT_FAILURE);
    }
    int del_msg = delete_message(2);
    if(del_msg != 0){
        perror("Could not delete the message");
        exit(EXIT_FAILURE);
    }
    int message = insert_message("roberto@nwdesigns.it", "roberto.capannelli@gmail.com", "HEY HEY HEY", 126389289);
    if(message != 0){
        perror("Could not insert the message");
        exit(EXIT_FAILURE);
    }
    return 0;
}
#endif