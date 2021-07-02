#include "server.h"
#include "database.h"
#include "sqlite3.h"

static void err_accept(int socketfd) {
    if (socketfd < 0) {
        delete_client_from_db(socketfd);
        perror("ERROR ACCEPTING\n");
        exit(1);
    }
    else {
        printf("%s", "User connected from socket ");
        printf("%s\n",mx_itoa(socketfd));
    }
}

// static t_sock *inv_socket1() {
//     t_sock *sock = (t_sock *)malloc(sizeof(t_sock));
//     sock->num = 0;
//     socketfd = 0;
//     sock->login = 0;
//     sock->next = NULL;
//     sock->prev = NULL;
//     return sock;
// }

static struct sockaddr_in init_server_address(int sockfd, int portno, int rc) {
    struct sockaddr_in servaddr;

    bzero((char *) &servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(portno);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&rc, sizeof(int));
    return servaddr;
}

// void logsescr(t_sock *sock) {
//     write(sock->log_sescr, "User connected from client ", 27);
//     write(sock->log_sescr, mx_itoa(sock->sockfd1), 1);
//     write(sock->log_sescr, "\n", 1);
// }

static void inv_port(int argc, char **argv,int serversock, struct sockaddr_in *servaddr) {
    int portno;
    int rc = 1;
    portno = atoi(argv[1]);

    if (argc != 2 || portno < 1025 || portno > 65535) {
        fprintf(stderr,"usage: %s port\n", argv[0]);
        exit(1);
    }
    //mx_daemon();
    // sock->sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
    // if (sock->sockfd1 < 0) {
    //     perror("ERROR CREATE SOCKET\n");
    //     exit(1);
    // }
    //inv_socket(sock);
    *servaddr = init_server_address(serversock, portno, rc);
}

int main(int argc, char **argv) {
    int clilen;
    struct sockaddr_in servaddr, cliaddr;
    pthread_t x = 0;
    int serversock;
    int socketfd;
    int *socketfd1;
    serversock = socket(AF_INET, SOCK_STREAM, 0);
    if (serversock < 0) {
        perror("ERROR CREATE SOCKET\n");
        exit(1);
    }

    inv_port(argc, argv,serversock, &servaddr);
    mx_daemon();

    if (bind(serversock, (struct sockaddr *) &servaddr,
        sizeof(servaddr)) < 0) {
        perror("ERROR BINDING\n");
        exit(1);
    }
    listen(serversock, MAX_CONNECT);
    clilen = sizeof(cliaddr);
    while (1) {
        socketfd = accept(serversock, (struct sockaddr *)&cliaddr,
                               (socklen_t *)&clilen);
        err_accept(socketfd);
        insert_curr_client(socketfd);
        socketfd1 = &socketfd;
        int errthread = pthread_create(&x, NULL, procces, (void *)socketfd1);
        if (errthread != 0)
            printf("\ncan't create thread :[%s]", strerror(errthread));
        // sock->next = create_client();
        // sock->next->prev = sock;
        // sock = sock->next;
    }
}
