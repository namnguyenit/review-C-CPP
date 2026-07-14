#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(void) {
    int server_fd = -1;
    int client_fd = -1;
    struct sockaddr_in addr;
    char buffer[BUFFER_SIZE];
    const char *reply = "Server chao";

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Loi socket");
        return 1;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Loi setsockopt");
        close(server_fd);
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Loi bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 1) < 0) {
        perror("Loi listen");
        close(server_fd);
        return 1;
    }

    printf("Port %d...\n", PORT);

    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) {
        perror("Loi accept");
        close(server_fd);
        return 1;
    }

    ssize_t n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (n < 0) {
        perror("Loi recv");
        close(client_fd);
        close(server_fd);
        return 1;
    }

    buffer[n] = '\0';
    printf("Client: %s\n", buffer);

    if (send(client_fd, reply, strlen(reply), 0) < 0) {
        perror("Loi send");
    }

    close(client_fd);
    close(server_fd);
    return 0;
}
