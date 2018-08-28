#include "user.h"

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
 * Insert a new user in the database
 * @param email
 * @param password
 * @return returns 0 if successful
 */
int insert_user(char *email, char *password){
    char *sql; //Store the sql statement string
    int result = 0; //Get the results from sqlite functions
    char *error; //Stores error messages
    //Open connection
    open_connection(result);

    //Allocate enough memory to store the sql statement
    sql = malloc(sizeof(char *) * 1000);

    //Add the sql statement string to the allocated memory
    sprintf(sql, "INSERT INTO %s (%s, %s) VALUES ('%s', '%s')", USER_TABLE, EMAIL_COLUMN, PASSWORD_COLUMN, email, password);

    //Execute a SQL statement
    result = sqlite3_exec(db, sql, callback, 0, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s", error);
        sqlite3_free(error);
        exit(EXIT_FAILURE);
    }
    puts("User added successfully!");

    //Close the connection
    sqlite3_close(db);

    //Free the memory allocated for the sql statement
    free(sql);

    return 0;
}

/**
 * Delete a user from the database
 * @param email
 * @return return 0 in case of success
 */
int delete_user(char *email){
    char *sql;
    int result = 0;
    char *error;
    //Open connection
    open_connection(result);

    //Allocate enough memory to store the sql statement
    sql = malloc(sizeof(char *) * 1000);

    //Add the sql statement string to the allocated memory
    sprintf(sql, "DELETE FROM %s WHERE %s = '%s'", USER_TABLE, EMAIL_COLUMN, email);

    //Execute a SQL statement
    result = sqlite3_exec(db, sql, callback, 0, &error);
    if(result != SQLITE_OK){
        fprintf(stderr, "SQL error: %s", error);
        sqlite3_free(error);
        exit(EXIT_FAILURE);
    }
    puts("The user has been deleted successfully!");

    //Close the connection
    sqlite3_close(db);

    //Free memory allocated for the sql statement
    free(sql);

    return 0;
}
