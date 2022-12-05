/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_4.c
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
#include <sys/types.h>
#include <string.h>


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

// Question 2.2.
    // In order for the father to print its end message when we stop the child
    // we need to catch SIGPIPE with sigaction.


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

    // Variable for printing the ids and random number
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

    // pipe
    int pipefd[2];
    pipe(pipefd);

    // fork
    pid_t c_pid = fork();
    if (c_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (c_pid == 0) {
        close(pipefd[1]);
        printf("printed from child process - %d\n", getpid());
    } else {
        close(pipefd[0]);
        printf("printed from parent process - %d\n", getpid());
    }

    while ( running )
    {
        int id = getpid();
        int fid = getppid();
        int randval = rand()%100;

        // The child : reading pipe and printing
        if (c_pid == 0) {
            if (read(pipefd[0], &read_id, sizeof(read_id)) > 0) {
                read(pipefd[0], &read_fid, sizeof(read_fid));
                read(pipefd[0], &read_rand, sizeof(read_rand));
                printf("Read id: %d\n", read_id);
                printf("Read father id: %d\n", read_fid);
                printf("Read random number: %d\n", read_rand);
            } else {
                perror("read");
                break;
            }
        }

        // The parent : writing in the pipe
        else {
            write(pipefd[1], &id, sizeof(id));
            write(pipefd[1], &fid, sizeof(fid));
            write(pipefd[1], &randval, sizeof(randval));
            sleep(1);
        }
    }
    close(pipefd[1]);
    close(pipefd[0]);

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
