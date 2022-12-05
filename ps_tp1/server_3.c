/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_3.c
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
#include <sys/wait.h>


// Questions 1.2.:
    // 1. In order to make it work by writing kill id_process we need to use SIGTERM instead of SIGINT.
    // 2. If we use kill -9 the message isn't printed and it is not possible because
    // we cannot use SIGKILL in sigaction.
    // 3. If we use kill father_id, nothing happens.
    // 4. If we use kill -9 father_id it stops the program and closes the terminal.
    // 5. If we on't modify running in stop_handler :
    // - with CTRL-C it doesn't stop,
    // - with kill pid it stops,
    // - with kill -9 pid it stops.
    // 6. Is exit_message activated with :
    // - CTRL-C ? YES,
    // - kill ? NO,
    // - kill -9 ? NO.

// Questions 2.1.
    // 1. If c_pid == 0 the messages are sent from the child process
    // and from the father process if c_pid is not 0 nor 1.
    // 2. Both processes are killed with CTRL-C.
    // 3. If we use ps a then kill the child process, with ps a we can see that
    // the child process hasn't disapeared.
    // 4. If we kill the father, the child remains but changes father :
    // the father's id becomes 1. Than if we kill the child, the program stops.
    // 5. With wait(), if we kill the father and then the child with :
    // - CTRL-C : status 1.
    // - kill : status 1.
    // - kill -9 : status 0, because the child process was not exited correctly.


bool running = 1;

void stop_handler( int sig ) {
    printf("%d\n", sig);
    printf("Changing running value\n");
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
    if (sigaction(SIGTERM, &act, NULL)==-1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    atexit(exit_message);

    pid_t c_pid = fork();
    if (c_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (c_pid == 0) {
        printf("printed from child process - %d\n", getpid());
    } else {
        printf("printed from parent process - %d\n", getpid());
    }

    while ( running )
    {
        printf("Child id: %d\n", getpid());
        printf("Parent id: %d\n", getppid());
        printf("Rand: %d\n", rand()%100);
        sleep(1);
    }

    int status;
    if (wait(&status) == -1) {
        perror("wait");
        exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status)) {
    printf("Status: %d\n", WEXITSTATUS(status));
    }
    printf( "End of main\n" );
    return EXIT_SUCCESS;
}
