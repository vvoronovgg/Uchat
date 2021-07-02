#include "client.h"

static int client_validator(int argc, char **argv) {
	int port;

	if (argc != 3)
		perror("usage: ./client ip_address port\n");
	port = atoi(argv[2]);
	if (!port)
		perror("Invalid port number\n");
	return port;
}

int main(int argc, char **argv) {
	int port = client_validator(argc, argv);
    struct sockaddr_in serv_addr;
    struct hostent *server;
    // int enable = 0;

	int fdsocket = socket(AF_INET, SOCK_STREAM, 0);
	if (fdsocket < 0)
		perror("Error while creating socket");
    

    server = gethostbyname(argv[1]);
    if (server == NULL)
        perror("NO SUCH HOST\n");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    while (1) {
	   int res = connect(fdsocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	   if (res < 0) {
        	perror("Error while connection\n");
            exit(1);
       }
       mx_interface(argc, argv, fdsocket); 
    }
    close(fdsocket);
}