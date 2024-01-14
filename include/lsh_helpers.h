#ifndef LSH_HELPERS_H
#define LSH_HELPERS_H

/**
 * @brief Signal handler for SIGINT (Ctrl+C). Forces the user to use 'exit' to quit the shell.
 * @param signum The signal number (should be SIGINT).
 * @return void.
 */
void sigint_handler(int signum);

/**
 * @brief Gets the the the username followed by '@' and the hostname.
 * @return The pointer to the string.
*/
char *get_user_at_hostname();

/**
 * @brief Gets the current working directory.
 * @return The pointer to the string.
*/
char *get_current_dir();

#endif