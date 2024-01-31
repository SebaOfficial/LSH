#ifndef LSH_H
#define LSH_H

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

/**
 * @brief Loop getting input and executing it.
*/
void lsh_loop(void);

/**
 * @brief Signal handler for SIGINT (Ctrl+C). Forces the user to use 'exit' to quit the shell.
 * @param signum The signal number (should be SIGINT).
 * @return void.
 */
void sigint_handler(int signum);

#endif