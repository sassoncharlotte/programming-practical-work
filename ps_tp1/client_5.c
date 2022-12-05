/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_5.c
 */

// This side writes first, then reads
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>


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
    printf( "Hello world\n" );
    int fd;

    // FIFO file path
    char * myfifo = "/Users/cha/Desktop/3A/code/3if1020/myfifo";

    int read_id;
    int read_fid;
    int read_rand;

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
        // Open FIFO for Read only
        fd = open(myfifo, O_RDONLY);

        if (read(fd, &read_id, sizeof(read_id)) > 0) {
            read(fd, &read_fid, sizeof(read_fid));
            read(fd, &read_rand, sizeof(read_rand));
            printf("Read id: %d\n", read_id);
            printf("Read father id: %d\n", read_fid);
            printf("Read random number: %d\n", read_rand);
        }
        else {
            perror("read");
            break;
        }
        close(fd);
    }
    printf( "\nEnd of main\n" );
    return EXIT_SUCCESS;
}
