#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void sigint_handler(int signum) { }


char *get_current_username()
{
    return getlogin();
}

char *get_hostname()
{
    char *hostname = (char *)malloc(256);
    if (hostname != NULL) {
        if (gethostname(hostname, 256) == 0) {
            return hostname;
        } else {
            free(hostname);
            return NULL;
        }
    } else {
        perror("malloc");
        return NULL;
    }
}

char *get_user_at_hostname()
{
    char *username = get_current_username();
    char *hostname = get_hostname();

    if (username != NULL && hostname != NULL) {
        char *result = (char *)malloc(strlen(username) + strlen(hostname) + 2);
        if (result != NULL) {
            sprintf(result, "%s@%s", username, hostname);
            return result;
        } else {
            perror("malloc");
            return NULL;
        }
    } else {
        return NULL;
    }
}


char *get_current_dir()
{
    char *cwd = NULL;
    size_t size = 1024; // Initial buffer size

    do {
        cwd = (char *)realloc(cwd, size);
        if (cwd == NULL) {
            perror("realloc");
            return NULL;
        }

        if (getcwd(cwd, size) != NULL) {
            return cwd;
        } else if (errno == ERANGE) {
            // The buffer was too small; try again with a larger size.
            size *= 2;
        } else {
            perror("getcwd() error");
            free(cwd);
            return NULL;
        }
    } while (1);
}