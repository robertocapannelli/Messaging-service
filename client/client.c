#include "client.h"

int main(int argc, char *argv[]){

    int sock; //the socket file descriptor
    struct sockaddr_in server; //the struct we need to handle socket
    char message[1000], server_reply[2000]; // array string to contain messages

    //Create socket

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("Could not creat socket");
        exit(EXIT_FAILURE);
    }
    puts("Socket created!\n");

    //Init the struct
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); //Set localhost as address
    server.sin_family = AF_INET; // Ipv4 internet protocol
    server.sin_port  = htons(8888); //Set the port to use for connections

    //Connect to remote server

    if(connect(sock, (struct sockaddr *)&server, sizeof(server)) == -1){
        perror("Could not connect to the server");
        exit(EXIT_FAILURE);
    }

    fflush(stdout);

    puts("Connection established!\n");

    //Communicate with the server

    while(1){
        //printf("Enter the message:\n");

        //TODO we have to ask authentication here

        int auth = authentication();

        if(scanf("%s", message) == 0){
            perror("Scanf error");
            exit(EXIT_FAILURE);
        }

        //Sent data
        if(send(sock, message, strlen(message), 0) < 0){
            perror("Send failed");
            exit(EXIT_FAILURE);
        }

        //Receive an answer from server
        if(recv(sock, server_reply, 2000, 0) < 0){
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }
        puts("Server reply:\n");
        puts("\n");
        puts(server_reply);

    }

    //TODO here the infinite loop should actually finish and let close the socket somehow

    close(sock);

    return 0;
}