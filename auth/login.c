#include "login.h"

/**
 * Asks for credential to the user
 * @return 0 in case of success or 1 in case the user is not in the database
 */
int authentication() {
    char email[30];
    char password[20];

    //Asks for email
    puts("Enter your email:");
    if (scanf("%s", email) == 0) {
        perror("email scanf error");
        exit(EXIT_FAILURE);
    }

    //Asks for password
    puts("Enter your password:");
    if (scanf("%s", password) == 0) {
        perror("password scanf error");
        exit(EXIT_FAILURE);
    }

    //Select a user in the database using the given credential
    if(select_user(email, password) != 0){
        puts("Your email or password are not correct");
        return 1;
    }

    printf("Your email is: %s\nYour password is: %s\n", email, password);
    return 0;
}

#if AUTH_LOGIN_DEBUG
int main(void) {

    authentication();

    return 0;
}
#endif