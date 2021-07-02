#include "server.h"

// static t_sock *create_client(int socketfd) {
//     t_sock *sock = (t_sock *)malloc(sizeof(t_sock));
//     sock->num = 0;
//     sock->client = socketfd;
//     //sock->log_sescr = create_log();
//     sock->id = "-1";
//     sock->next = NULL;
//     sock->prev = NULL;
//     if(head.changed != 1) {
//         head.start=sock;
//         head.changed = 1;
//     }
//     return sock;
// }

void push_client_front(t_sock** sock,int socketfd) {
    if(!*sock) {
        *sock=create_client(socketfd);
    }
    else {
        t_sock * new_head = create_client(socketfd);
        new_head->next = *sock;
        *sock = new_head;
    }
}
