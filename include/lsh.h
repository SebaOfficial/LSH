#ifndef LSH_H
#define LSH_H

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

int lsh_num_builtins();

/**
 * @brief Launch a program and wait for it to terminate.
 * @param args Null terminated list of arguments (including program).
 * @return Always returns 1, to continue execution.
 * 
*/
int lsh_launch(char **args);

/**
 * @brief Execute shell built-in or launch program.
 * @param args Null terminated list of arguments.
 * @return 1 if the shell should continue running, 0 if it should terminate
*/
int lsh_execute(char **args);

/**
 * @brief Read a line of input from stdin.
 * @return The line from stdin.
*/
char *lsh_read_line(void);

/**
 * @brief Split a line into tokens (very naively).
 * @param line The line.
 * @return Null-terminated array of tokens.
*/
char **lsh_split_line(char *line);

/**
 * @brief Loop getting input and executing it.
*/
void lsh_loop(void);

#endif