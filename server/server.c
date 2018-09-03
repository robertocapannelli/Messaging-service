#include "server.h"

#define PORT 8888
#define BACKLOG 10

void *connection_handler(void *socket_desc);

int run_server(){

    int socket_desc, client_socket, c, *new_sock;
    struct sockaddr_in server, client;

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        handle_error("Could not create socket!");
    }
    printf("Socket created\n");


    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);


    //Bind a name to a socket assign the address to the socket
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
        handle_error("Bind failed");
    }
    puts("Bind done!\n");

    //Listen for connection, 3 is the maximum accepted in the que
    listen(socket_desc, BACKLOG); //TODO select or poll handle multiple file descriptor at time

    puts("Waiting for incoming connections...\n");

    c = sizeof(struct sockaddr_in);

    //Loop that accepts the connections
    while ((client_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &c))) {
        puts("Connection accepted\n");

        new_sock = malloc(1);
        *new_sock = client_socket;
        pthread_t thread;

        //TODO we have to accept a predefined number of maximum thread to avoid server overhead and print out the # of the thread

        if (pthread_create(&thread, NULL, connection_handler, (void *) new_sock) < 0) {
            handle_error("Could not create thread");
        }

        puts("Handler assigned\n");
    }

    if (client_socket < 0) {
        handle_error("Accept failed");
    }

    return 0;
}

/**
 * Handle the connection for each client
 * @param socket_desc file descriptor
 */
//TODO this function should have the login inside, one for each thread, one for each client and check the database
void *connection_handler(void *socket_desc) {
    //Get the socket descriptor
    int sock = *(int *) socket_desc;
    int read_size;
    char *message, client_message[2000];

    //Send some messages to the client
    message = "Now type something and i shall repeat what you type \n";
    if (write(sock, message, strlen(message)) == -1) {
        handle_error("Write error");
    }

    //TODO before accept any messages the user has to login and authenticate

    //Receive a message from client
    while ((read_size = (int) recv(sock, client_message, 2000, 0)) > 0) {

        //printf("message from client: %s", client_message);

        //TODO here we receive messages from client and handle to one another through the database

        //Send the message back to client
        if(write(sock, client_message, strlen(client_message)) == -1){
            handle_error("Write error");
        }
    }

    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        handle_error("recv failed");
    }

    //Free the socket pointer
    free(socket_desc);

    return 0;
}

int main(int argc, char *argv[]) {

    run_server();
}
