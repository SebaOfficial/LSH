#ifndef LSH_BUILTIN_H
#define LSH_BUILTIN_H

#define LSH_NUM_BUILTIN_FUNCTIONS 3

/**
 * @brief Builtin command: change directory.
 * @param args List of args.  args[0] is "cd".  args[1] is the directory.
 * @return Always returns 1, to continue executing.
*/
int lsh_cd(char **args);

/**
 * @brief Builtin command: print help.
 * @param args List of args.  Not examined.
 * @return Always returns 1, to continue executing.
 * 
*/
int lsh_help(char **args);

/**
 * @brief Builtin command: exit.
 * @param args List of args.  Not examined.
 * @return Always returns 0, to terminate execution.
*/
int lsh_exit(char **args);

#endif