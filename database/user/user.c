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

//TODO we should make just one call with email and password together and not just one and then the other so save memory
int select_user(const char *email_user, const char *password_user) {
    char *sql;
    int result = 0;

    //Open connection
    open_connection(result);

    //Add the SQL query to the allocated memory
    sql = malloc(sizeof(const char *) * 30);

    //Add the SQL query to the allocated memory
    sprintf(sql,"SELECT email FROM %s WHERE %s = '%s' AND %s = '%s'", USER_TABLE, EMAIL_COLUMN, email_user, PASSWORD_COLUMN, password_user );

    //Prepare statement to be executed
    int prepare = sqlite3_prepare_v2(db, sql, (int) strlen(sql), &stmt, 0);
    if(prepare != SQLITE_OK){
        fprintf(stderr, "SQL error: %s", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }

    //Loop over the rows
    while(sqlite3_step(stmt) == SQLITE_ROW){
        if(sqlite3_step(stmt) == SQLITE_DONE){
            //char *email = (char *) sqlite3_column_text(stmt, 0);
            puts("User found!");
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}

#if DB_USER_DEBUG
int main(int argc, char* argv[]) {
    int select = select_user("roberto@nwdesigns.it", NULL);
    if(select != 0){
        perror("err");
        exit(EXIT_FAILURE);
    }
    int delete = delete_user("robee");
    if(delete != 0){
        perror("Could not delete the user");
        exit(EXIT_FAILURE);
    }
    int insert = insert_user("roberto@nwdesigns.it","rob");
    if(insert != 0){
        perror("Could not insert");
        exit(EXIT_FAILURE);
    }
    return 0;
}
#endif