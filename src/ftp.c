/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** ftp
*/

#include "ftp.h"
#include "clientllist.h"
#include "lib.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/wait.h>

/**
 * @brief callback for SIGINT
 * @details exit the program by calling my_exit to free all the memory
 *     and correctly close the socket and the clients sockets.
*/
static void handle_sigint(UNUSED int sig)
{
    my_exit(0);
}

/**
 * @brief Initialize the server_info struct
 * @details correctly initialize the server_info struct with the port and the
 *    path of the server
 *
 * @param argv the arguments of the program
 *
 * @return the server_info struct
*/
static server_info_t init_server_info(char *argv[])
{
    server_info_t server_info = my_malloc(sizeof(struct server_info_s));

    server_info->port = atoi(argv[1]);
    server_info->path = get_current_dir();
    if (server_info->path == NULL)
        my_error("get_current_dir failed");
    if (server_info->path[strlen(server_info->path) - 1] == '/')
        server_info->path[strlen(server_info->path) - 1] = '\0';
    DEBUG_PRINT("Server path: %s\n", server_info->path);
    server_info->ip = my_malloc(sizeof(char) * INET_ADDRSTRLEN + 1);
    server_info->ip[INET_ADDRSTRLEN] = '\0';
    return server_info;
}

/**
 * @brief Analyze the fork status of the clients
 * @details if the fork is finished, the client status is set to WRITING
 *    and the current_code is set to 226
 *
 * @param client the client to analyze
*/
static void update_fork_status(client_t client)
{
    int status = 0;
    int result = waitpid(client->external_socket->pid, &status, WNOHANG);

    if (result == 0)
        return;
    if (result == -1)
        my_error("waitpid failed");
    client->data_status = WRITING;
    client->current_code = 226;
    client->external_socket->mode = NO_MODE;
    client->external_socket->fd = -1;
    client->external_socket->port = -1;
}

/**
 * @brief Add the clients to the write and read fd_sets
 * @details add the clients to the write and read fd_sets and update the
 *   max_sd variable, also update the fork status of the clients
 *
 * @param clients the clients to add to the fd_sets
 * @param readfds the read fd_set
 * @param writefds the write fd_set
 * @param max_sd the max_sd variable
*/
static void add_clients_to_set(
    client_t *clients,
    fd_set *readfds,
    fd_set *writefds,
    int *max_sd)
{
    client_t tmp = *clients;

    while (tmp) {
        if (tmp->data_status == WAITING_FOR_FORK)
            update_fork_status(tmp);
        if (tmp->data_status == READING)
            FD_SET(tmp->fd, readfds);
        if (tmp->data_status == WRITING)
            FD_SET(tmp->fd, writefds);
        if (tmp->fd > *max_sd)
            *max_sd = tmp->fd;
        tmp = tmp->next;
    }
}

/**
 * @brief Add a new client to the list of clients
 * @details add a new client to the list of clients by accepting a connexion
 *
 * @param socketFd the socket file descriptor
*/
static void add_new_client(int socketFd)
{
    int new_socket = 0;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    client_t *clients = get_clients();

    new_socket = accept(socketFd, (struct sockaddr *)&address,
        (socklen_t *)&addrlen);
    if (new_socket < 0)
        my_error("new client: accept failed");
    if (*clients == NULL)
        *clients = create_client(new_socket, inet_ntoa(address.sin_addr));
    else
        add_client(create_client(new_socket, inet_ntoa(address.sin_addr)));
}

/**
 * @brief Wrapper for the select function
 * @details wrapper for the select function, if the select function failed
 *   the program exit, else the function updates the fd_sets each 100ms.
 *
 * @param max_sd the max_sd variable
 * @param readfds the read fd_set
 * @param writefds the write fd_set
 * @param clients the list of clients
*/
static void select_wrapper(int max_sd, fd_set *readfds,
    fd_set *writefds, UNUSED client_t *clients)
{
    struct timeval timeout = {0, 100};
    int activity = 0;

    activity = select(max_sd + 1, readfds, writefds, NULL, &timeout);
    if (activity < 0)
        my_error("select wrapper failed");
}

/**
 * @brief Main FTP loop
 * @details the main loop of the FTP server, it accepts new clients and
 *  updates the clients status, also it calls the loop_clients function
 *  to handle the clients commands
 *
 * @param socketFd the socket file descriptor
 * @param server_info the server_info struct
*/
void ftp_loop(int socketFd, server_info_t server_info)
{
    fd_set readfds;
    fd_set writefds;
    int max_sd = 0;
    client_t *clients = NULL;

    while (1) {
        clients = get_clients();
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_SET(socketFd, &readfds);
        max_sd = socketFd;
        add_clients_to_set(clients, &readfds, &writefds, &max_sd);
        print_fd_set(&readfds);
        select_wrapper(max_sd + 1, &readfds, &writefds, clients);
        if (FD_ISSET(socketFd, &readfds))
            add_new_client(socketFd);
        loop_clients(clients, &readfds, &writefds, server_info);
    }
}

/**
 * @brief Main FTP function
 * @details the main function of the FTP server, it initializes the server_info
 * struct, the socket and the clients list, then it calls the ftp_loop function
 * to start the server
 *
 * @param argc the number of arguments
 * @param argv the arguments of the program
 *
 * @return 0 if the program exited correctly
*/
int ftp(int argc, char *argv[])
{
    int socketFd = -1;
    server_info_t server_info;

    errno = 0;
    DEBUG_PRINT("FTP server started\n");
    signal(2, handle_sigint);
    check_args(argc, argv);
    server_info = init_server_info(argv);
    socketFd = get_socket();
    DEBUG_PRINT("Socket fd: %d\n", socketFd);
    prepare_exit(socketFd);
    bind_socket(socketFd, server_info->port, &(server_info->ip));
    DEBUG_PRINT("Server info: %s:%d\n", server_info->ip, server_info->port);
    listen_socket(socketFd, 1024);
    ftp_loop(socketFd, server_info);
    close(socketFd);
    return 0;
}
