#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"


void main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = "INCR";

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("SOCKET CREATING FAILED");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0 ) {
        printf("INVALID ADDRESS");
        exit(1);
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("CONNECTION FAILED");
        exit(1);
    }
    
    send(sock, buffer, strlen(buffer), 0);

    int n = read(sock, buffer, sizeof(buffer));
    printf("Response is %s\n", buffer);

    close(sock);
}
