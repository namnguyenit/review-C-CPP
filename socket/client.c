#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sock = -1;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    const char *message = (argc > 1) ? argv[1] : "Client chao";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Loi socket");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        fprintf(stderr, "Loi IP\n");
        close(sock);
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Loi connect");
        close(sock);
        return 1;
    }

    if (send(sock, message, strlen(message), 0) < 0) {
        perror("Loi send");
        close(sock);
        return 1;
    }

    ssize_t n = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (n < 0) {
        perror("Loi recv");
        close(sock);
        return 1;
    }

    buffer[n] = '\0';
    printf("Server: %s\n", buffer);

    close(sock);
    return 0;
}
