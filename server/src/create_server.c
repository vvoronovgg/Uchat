// #include "server.h"

// // static struct sockaddr_in inint_servaddr(int sockfd, int portno, int rc);
// static void inint_servaddr(struct sockaddr_in *servaddr);
// //static struct sockaddr_in inint_servaddr(t_sock *sock);
// static void init_socket(int sockfd, t_sock *sock);
// // static struct sockaddr_in inint_servaddr(int portno);
// static void init_bindarr(t_sock *sock, struct addrinfo **bindaddr);

// static void inint_servaddr(struct sockaddr_in *servaddr) {
//     //struct sockaddr_in servaddr;
//     char hostbuffer[256];
//     char *ip; 
//     struct hostent *hostserv; 
//     int hostname;
//     if ((hostname = gethostname(hostbuffer, sizeof(hostbuffer))) != -1) {
//         if ((hostserv = gethostbyname(hostbuffer)) != NULL) {
//             ip = inet_ntoa(*((struct in_addr*)hostserv->h_addr_list[0]));
//             inet_aton(ip, &servaddr->sin_addr);
//             //printf("ip: %s\n", ip);
//             return;
//         }
//     }
//     inet_aton("127.0.0.1", &(*servaddr).sin_addr);
//     //return servaddr;
// }

// // static struct sockaddr_in inint_servaddr(int sockfd, int portno, int rc) {
// //     struct sockaddr_in servaddr;
// //     char hostbuffer[256];
// //     char *ip; 
// //     struct hostent *hostserv; 
// //     int hostname;
// //     bzero((char *) &servaddr, sizeof(servaddr));
// //     servaddr.sin_family = AF_INET;
// //     servaddr.sin_port = htons(portno);
// //     if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &rc, 
// //                     sizeof(int)) < 0) {
// //         perror("Error setsockpot\n");
// //         exit(1);
// //     }
// //     if ((hostname = gethostname(hostbuffer, sizeof(hostbuffer))) != -1) {
// //         if ((hostserv = gethostbyname(hostbuffer)) != NULL) {
// //             ip = inet_ntoa(*((struct in_addr*)hostserv->h_addr_list[0]));
// //             inet_aton(ip, &servaddr.sin_addr);
// //             mx_strdel(&ip);
// //             //printf("ip: %s\n", ip);
// //             return;
// //         }
// //     }
// //    // inet_aton("127.0.0.1", &servaddr.sin_addr);
// //     return servaddr;
// // }

// static void init_socket(int sockfd, t_sock *sock) {
//     sock->num = 0;
//     sock->client = 0;
//     if (sockfd < 0) {
//         perror("Error create socket\n");
//         exit(1);
//     }
// }

// static void init_bindarr(t_sock *sock, struct addrinfo **bindaddr) {
//     struct addrinfo hints;
//     bzero(&hints, sizeof(hints));

//     hints.ai_family = AF_INET;
//     hints.ai_socktype = SOCK_STREAM;
//     hints.ai_flags = AI_PASSIVE;
//     getaddrinfo(0, sock->argv[1], &hints, bindaddr);
// }

// int create_server (t_sock *sock) {
//     struct addrinfo *bindaddr = NULL;
//     struct sockaddr_in servaddr;
//     int rc = 1;
//     int sockfd;

//     init_bindarr(sock, &bindaddr);
//     sockfd = socket(bindaddr->ai_family, bindaddr->ai_socktype, bindaddr->ai_protocol);
//     if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &rc, 
//                     sizeof(int)) < 0) {
//         perror("Error setsockpot\n");
//         exit(1);
//     }
//     servaddr.sin_family = AF_INET;
//     servaddr.sin_port = htons(sock->port);
//     //sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//     init_socket(sockfd,sock);
//     inint_servaddr(&servaddr);
//     //servaddr = inint_servaddr(sock);
//     // Binding newly created socket to given IP and verification 
//     // if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) { 
//     //     perror("Error binding\n");
//     //     close(sockfd);
//     //     exit(1);
//     // } 
//     // else
//     //     printf("Socket successfully binded..\n");
//     //start_server(sock,sockfd);

//     // Now server is ready to listen and verification 
//     // if ((listen(sockfd, MAX_CONNECT)) != 0) { 
//     //     write(sock->descr,"Listen FAILED...\n",17); 
//     //     exit(1); 
//     // } 
//     // else
//     //     printf("Server listening..\n"); 
//     //server_loop(sock);
//     return sockfd;
// }

