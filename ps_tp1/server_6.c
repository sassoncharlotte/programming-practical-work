/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_6.c
 */

#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)
#include <unistd.h> // read(), write(), close()
#define MAX 80
#define LISTEN_BACKLOG 50
#define PORT 8080
#define SA struct sockaddr


bool running = 1;

void stop_handler( int sig ) {
    printf("\nSIG received: %d\n", sig);
    printf("Changing running value\n");
    running = !running;
}
void exit_message() {
    printf("\nEnd of the program\n");
}

 
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    socklen_t peer_addr_size;
 
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    if (bind(sockfd, (struct sockaddr *) &servaddr,
            sizeof(servaddr)) == -1)
        handle_error("bind");
    if (listen(sockfd, LISTEN_BACKLOG) == -1)
        handle_error("listen");

    /* Now we can accept incoming connections one
        at a time using accept(2). */

    peer_addr_size = sizeof(cli);
    connfd = accept(sockfd, (struct sockaddr *) &cli, &peer_addr_size);
    if (connfd == -1) handle_error("accept");
    else printf("Server accepted the client\n");

    // sigaction
    struct sigaction act;
    act.sa_handler = &stop_handler;
    sigfillset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    if (
        sigaction(SIGINT, &act, NULL)==-1 ||\
        sigaction(SIGTERM, &act, NULL)==-1 ||\
        sigaction(SIGPIPE, &act, NULL)==-1
    ) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // atexit
    atexit(exit_message);

    while (running) {
        int id = getpid();
        int fid = getppid();
        int randval = rand()%100;
        write(connfd, &id, sizeof(id));
        write(connfd, &fid, sizeof(fid));
        write(connfd, &randval, sizeof(randval));
        sleep(1);
    }
 
    // close the socket
    close(sockfd);

    printf( "\nEnd of main\n" );
    return EXIT_SUCCESS;
}
