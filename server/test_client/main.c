/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** main
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

char *get_cmd(void)
{
    char *buff = NULL;
    size_t size = 0;

    if (getline(&buff, &size, stdin) == -1)
        return NULL;
    size = strlen(buff);
    if (buff[size - 1] == '\n')
        buff[size - 1] = 0;
    return buff;
}

/*"cr" create a '\n' rather than a "\r\n"*/
static int write_command(int fd, char *cmd)
{
    char tempbuff[1024] = {0};
    size_t i = 0;
    size_t j = 0;

    while (cmd[i] != '\0' && j < sizeof(tempbuff) - 1) {
        if (cmd[i] == 'c' && cmd[i + 1] == 'r') {
            tempbuff[j] = '\n';
            j += 1;
            i += 2;
        } else {
            tempbuff[j] = cmd[i];
            i += 1;
            j += 1;
        }
    }
    write(fd, tempbuff, j);
    return 0;
}

static int send_server(int clientfd)
{
    char *cmd = get_cmd();

    if (cmd == NULL) {
        close(clientfd);
        return -1;
    } else if (strcmp(cmd, "close") == 0) {
        close(clientfd);
        free(cmd);
        return -1;
    } else {
        write_command(clientfd, cmd);
    }
    free(cmd);
    return 0;
}

static int read_server(int fd)
{
    char bufferin[BUFSIZ] = {0};
    int rc = 0;

    rc = read(fd, bufferin, BUFSIZ - 1);
    if (rc > 0)
        printf("SERVER : %s\n", bufferin);
    return 0;
}

static int listen_fds(struct pollfd *fds, int client_fd, int *run)
{
    int rc = -1;

    rc = poll(fds, 2, -1);
    if (rc < 0) {
        perror("poll error\n");
        return EXIT_FAILURE;
    } else if (rc == 0) {
        perror("poll timeout\n");
        return EXIT_SUCCESS;
    }
    if (fds[0].revents & POLLIN)
        read_server(client_fd);
    if (fds[1].revents & POLLIN) {
        if (send_server(client_fd) == -1)
            run = 0;
    }
    return EXIT_SUCCESS;
}

static int setup(struct pollfd *fds, int port)
{
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    int rc = -1;
    struct sockaddr_in servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    rc = connect(client_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (rc < 0)
        return -1;
    fds[0].fd = client_fd;
    fds[0].events = POLLIN | POLLOUT;
    fds[1].fd = 0;
    fds[1].events = POLLIN;
    return client_fd;
}

static int loop(int port)
{
    int rc = 0;
    struct pollfd *fds = malloc(sizeof(struct pollfd *) * 3);
    int client_fd = 0;
    int run = 1;

    client_fd = setup(fds, port);
    if (client_fd == -1)
        return 84;
    while (run == 1) {
        rc = listen_fds(fds, client_fd, &run);
        if (rc == EXIT_FAILURE)
            return 84;
    }
    close(client_fd);
    return 0;
}

int main(int argc, char const *argv[])
{
    int port = 0;

    if (argc != 2)
        return 84;
    port = atoi(argv[1]);
    if (port == 0)
        return 84;
    return loop(port);
}
