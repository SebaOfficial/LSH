#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lsh.h"
#include "lsh_builtin.h"
#include "lsh_helpers.h"
#include "lsh_colors.h"

int last_exit_code = 0;

extern char *builtin_str[];
extern int (*builtin_func[])(char **);

/**
 * @brief Launch a program and wait for it to terminate.
 * @param args Null terminated list of arguments (including program).
 * @return Always returns 1, to continue execution.
 */
int lsh_launch(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        // Child process
        if (execvp(args[0], args) == -1)
        {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        // Error forking
        perror("lsh");
    }
    else
    {
        // Parent process
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        last_exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : (WIFSIGNALED(status) ? 128 + WTERMSIG(status) : 1);
    }

    return 1;
}

/**
 * @brief Execute shell built-in or launch program.
 * @param args Null terminated list of arguments.
 * @return 1 if the shell should continue running, 0 if it should terminate
 */
int lsh_execute(char **args)
{
    int i;

    if (args[0] == NULL)
    {
        // An empty command was entered.
        return 1;
    }

    for (i = 0; i < lsh_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }

    return lsh_launch(args);
}

/**
 * @brief Read a line of input from stdin.
 * @return The line from stdin.
 */
char *lsh_read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t bytes_read;

    bytes_read = getline(&line, &bufsize, stdin);

    if (bytes_read == -1)
    {
        if (feof(stdin))
        {
            free(line);
            return NULL;
        }
        else
        {
            perror("lsh: getline");
            free(line);
            return NULL;
        }
    }

    if (bytes_read > 0 && line[bytes_read - 1] == '\n')
    {
        line[bytes_read - 1] = '\0';
    }

    return line;
}

/**
 * @brief Split a line into tokens (very naively).
 * @param line The line.
 * @return Null-terminated array of tokens.
 */
char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token, **tokens_backup;

    if (!tokens)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += LSH_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char *));

            if (!tokens)
            {
                free(tokens_backup);
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

void lsh_print_prompt(void)
{
    char *user_information = get_user_at_hostname();
    char *cwd = get_current_dir();
    char *prompt = last_exit_code != 0 ? COLOR_RED ">" COLOR_RESET : ">";
    printf("%s:%s%s ", user_information, cwd, prompt);
    fflush(stdout);
    free(user_information);
    free(cwd);
}

void lsh_loop(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        lsh_print_prompt();

        line = lsh_read_line();

        if (line == NULL) // EOF
        {
            free(line);
            printf("\n");
            break;
        }

        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);

    } while (status);
}