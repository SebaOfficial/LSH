#ifndef LSH_HELPERS_H
#define LSH_HELPERS_H

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

/**
 * @brief Signal handler for SIGINT (Ctrl+C).
 * @param signum The signal number (should be SIGINT).
 */
void sigint_handler(int signum);

#endif