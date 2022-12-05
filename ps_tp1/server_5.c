/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_5.c
 */

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

    // FIFO
    char * myfifo = "/Users/cha/Desktop/3A/code/3if1020/myfifo";
    fd = open(myfifo, O_WRONLY); // Before the loop so that SIGPIPE is caught

    // sigaction
    struct sigaction act;
    act.sa_handler = &stop_handler;
    //sigfillset(&act.sa_mask);
    //act.sa_flags = SA_RESTART;
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
        write(fd, &id, sizeof(id));
        write(fd, &fid, sizeof(fid));
        write(fd, &randval, sizeof(randval));
        sleep(1);
    }
    close(fd);

    // wait for children
    int status;
    if (wait(&status) == -1) {
        perror("wait");
        exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status)) {
        printf("Child status: %d\n", WEXITSTATUS(status));
    }
    printf( "\nEnd of main\n" );
    return EXIT_SUCCESS;
}
