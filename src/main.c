#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "lsh.h"
#include "lsh_helpers.h"

int main(int argc, char **argv)
{
    printf("Welcome to LSH!\nType help to get more information\n");

    signal(SIGINT, sigint_handler);

    lsh_loop();

    printf("Bye!\n");

    return EXIT_SUCCESS;
}