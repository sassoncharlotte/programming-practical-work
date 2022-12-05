/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_2.c
 */

#include <stdbool.h>
// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>
#include <signal.h>

bool running = 1;

void stop_handler( int sig ) {
    printf("%d\n", sig);
    printf("Message reçu\n");
    running = !running;
}

void exit_message() {
    printf("End of the program\n");
}

int main()
{
    printf( "Hello world\n" );
    struct sigaction act;
    act.sa_handler = &stop_handler;
    sigfillset(&act.sa_mask);
    act.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &act, NULL)==-1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    // Questions 1.2.:
    // 1. In order to make it work by writing kill id_process we need to replace SIGINT with SIGTERM
    // 2. If we use kill -9 the message isn't printed and it is not possible because we cannot catch SIGKILL
    // 3. If we use kill father_id, nothing happens
    // 4. If we use kill -9 father_id it stops the program and closes the terminal
    // 5. If we on't modify running in stop_handler :
    // - with CTRL-C it doesn't stop,
    // - with kill pid it stops
    // - with kill -9 pid it stops
    // 6. Is exit_message activated with :
    // - CTRL-C ? YES
    // - kill ? NO
    // - kill -9 ? NO

    atexit(exit_message);

    while ( running )
    {
        printf("%d\n", getpid());
        printf("%d\n", getppid());
        printf("Rand %d\n", rand()%100);
        sleep(1);
    }
    printf( "Hello world again\n" );
    return EXIT_SUCCESS;
}
