/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_1.c
 */

// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>

int main()
{
    printf( "Hello world\n" );
    while ( 1 )
    {
        printf("%d\n", getpid());
        printf("%d\n", getppid());
        printf("Rand %d\n", rand()%100);
        sleep(1);
    }
    printf( "Hello world again\n" );
    return EXIT_SUCCESS;
}
