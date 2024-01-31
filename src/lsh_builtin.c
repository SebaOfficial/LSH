#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lsh_builtin.h"
#include "lsh.h"

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[LSH_NUM_BUILTIN_FUNCTIONS]) (char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int lsh_num_builtins()
{
    return LSH_NUM_BUILTIN_FUNCTIONS;
}

int lsh_cd(char **args)
{
    if (args[1] == NULL) {
        // No argument passed, change to the user's home directory
        char *home_dir = getenv("HOME");
        if (home_dir == NULL) {
            fprintf(stderr, "lsh: cd: could not determine the home directory\n");
            return 1;
        }

        if (chdir(home_dir) != 0) {
            perror("lsh: cd");
            return 1;
        }
    } else {
        if (chdir(args[1]) != 0) {
            perror("lsh: cd");
            return 1;
        }
    }
    return 1;
}

int lsh_help(char **args)
{
    printf("Sebastiano Racca's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (int i = 0; i < lsh_num_builtins(); i++) {
        printf("    %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}


int lsh_exit(char **args)
{
    return 0;
}