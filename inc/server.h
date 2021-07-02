#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <../cjson/inc/cJSON.h>
#include <../Libmx/inc/libmx.h>
#include <signal.h>
#include "sqlite3.h"
// #include <bits/sigaction.h>
// #include <features.h>
// #include <bits/types.h>
// #include <bits/signum.h>
// #include <bits/types/sig_atomic_t.h>
// #include <bits/types/sigset_t.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

// #include <../../datab/inc/database.h>
// #include <../../datab/inc/sqlite3.h>

#define MAX_BUFF 2000
#define MAX_CONNECT 156
#define MX_CHEAT_MESSAGE "Just stay"

typedef struct s_sock {
    int num;
    int sockfd1;
    int client;
    int log_sescr;
    char *id;
    char *reciverid;
    sqlite3 *bd;
    pthread_mutex_t mutex;
    struct s_sock *next;
    struct s_sock *prev;
} t_sock;

// typedef struct s_clients {
//     int fd;
//     int user_id;
//     char *token;
//     struct s_clients *first;
//     struct s_clients *next;
// }               t_clients;


int main(int argc, char **argv);
void mx_daemon(void);
void *procces (void *data);
void print_error(char *str);
//t_buf_do_proc mx_handle_one(t_buf_do_proc buf_do_proc, t_sockbd sockbd);


//----------------------------------------/*sockets.db*/------------------------------------------
//------------------------------------------------------------------------------------------------

/*вставляет текущего клиента (его сокет) в БД*/
void insert_curr_client(int curr_socket);

/*обновляет айди клиента, связанного с его сокетом в БД*/
void update_uid(char **curr_client_id, int curr_client_socket);

/*достает сокет клиента-получателя из БД по айди получателя*/
int select_client_socket(char **receiver_id);

void delete_client_from_db(int socket_to_delete);

#endif
