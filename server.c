#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int serverSocket;
    int clientSocket;
    int state;

    struct sockaddr_in server_addr, client_addr;
    socklen_t clientAddrLen = sizeof(client_addr);


    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        printf("Error while creating server socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
 

    bind(serverSocket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(serverSocket, 10);

    printf("SERVER STARTED LISTENING ON PORT 8080\n");

    while(1) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&client_addr, &clientAddrLen);

        if (clientSocket < 0){
            continue;
        }

        printf("CONNECTION ESTABLISHED\n");
        
        char buffer[1024];
        int recieved = recv(clientSocket, buffer, 1024, 0);
        printf("i recieved %s\n", buffer);
        if (strncmp(buffer, "INCR", 4)== 0) {
           state++;
           printf("I INCREMANTED THE STATE TO %d", state);
        }
        else if (strncmp(buffer, "DECR", 4)== 0) {
           state--;
           printf("I DECREMENTED THE STATE TO %d", state);
        }
        else {
            printf("UNKNOWN COMMAND");
        }
        send(clientSocket, "hello", 6, 0);
    }

    printf("CONNECTION CLOSED\n");
    close(serverSocket);

    return 0;
}


