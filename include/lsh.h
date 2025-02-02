#ifndef LSH_H
#define LSH_H

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

/**
 * @brief Loop getting input and executing it.
 */
void lsh_loop(void);

/**
 * @brief Prints the prompt line. 
 */
void lsh_print_prompt(void);

#endif