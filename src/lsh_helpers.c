#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/**
 * @brief Signal handler for SIGINT.
 * @param signum The signal number.
 */
void sigint_handler(int signum) { }

/**
 * @brief Get the current username.
 * @return A pointer to the current username string.
 */
char *get_current_username()
{
    return getlogin();
}

/**
 * @brief Get the hostname.
 * @return A pointer to the hostname string.
 */
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

/**
 * @brief Expand a tilde (~) in a path to the home directory.
 * @param path The path containing a tilde (~).
 * @return A pointer to the resulting string.
 */
char *expand_tilde(const char *path) {
    const char *home = getenv("HOME");
    if (home == NULL) {
        fprintf(stderr, "Unable to get the home directory.\n");
        return NULL;
    }

    char *result = NULL;
    if (strstr(path, home) == path) {
        size_t new_size = strlen(path) + strlen(home) + 1;
        result = (char *)malloc(new_size);
        if (result == NULL) {
            perror("malloc");
            return NULL;
        }

        snprintf(result, new_size, "~%s", path + strlen(home));
    } else {
        result = strdup(path);
        if (result == NULL) {
            perror("strdup");
            return NULL;
        }
    }

    return result;
}

char *get_current_dir() {
    char *cwd = NULL;
    size_t size = 1024; // Initial buffer size

    do {
        cwd = (char *)realloc(cwd, size);
        if (cwd == NULL) {
            perror("realloc");
            return NULL;
        }

        if (getcwd(cwd, size) != NULL) {
            char *expanded = expand_tilde(cwd);
            free(cwd);
            return expanded;
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