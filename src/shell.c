#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define LSH_RL_BUFSIZE 1024       // Reading a Line
#define LSH_TOK_BUFSIZE 64        // Parsing the Line
#define LSH_TOK_DELIM " \t\r\n\a" // Parsing the Line

// Function Declarations for builtin shell commands
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

// List of builtin commands, followed by their corresponding functions
char *builtin_str[] = {"cd", "help", "exit"};
int (*builtin_fnc[])(char **) = {&lsh_cd, &lsh_help, &lsh_exit}; // Array of function pointers
int lsh_num_builtins() { return sizeof(builtin_str) / sizeof(char *); }

// Builtin function implementations

int lsh_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "lsh: expected arguement to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("lsh");
        }
    }
    return 1; // to continue executing
}
int lsh_help(char **args)
{
    int i;
    printf("Basic Linux Shell in C\n");
    printf("Type program names and arguements\n");
    printf("The following are built in:\n");
    for (i = 0; i < lsh_num_builtins(); i++)
    {
        printf("  %s\n", builtin_str[i]);
    }
    printf("Use the man command for information on other programs\n");
    return 1;
}
int lsh_exit(char **args)
{
    return 0; // Return 0 to terminate execution
}

// Starting Shell Processes --> Launch a program
int lsh_launch(char **args)
{
    __pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) // Child Process
    {
        if (execvp(args[0], args) == -1)
        {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) // Error Forking
    {
        perror("lsh");
    }
    else // Parent Process
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

// Execution Block
int lsh_execute(char **args)
{
    int i;
    if (args[0] == NULL)
    {
        return 1; // Empty command was entered
    }
    for (i = 0; i < lsh_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_fnc[i])(args);
        }
    }
    return lsh_launch(args);
}

// Reading a Line
char *lsh_read_line(void)
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // Read a character
        c = getchar(); // Returns ASCII value of character

        // If we hit EOF, replace it with a null-terminator and return
        // Note: EOF is an int, so to compare to c, c must be an int
        if (c == EOF)
        {
            exit(EXIT_SUCCESS);
        }
        else if (c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate
        if (position >= bufsize)
        {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

// Parsing the Line
char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

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
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

// Basic Loop of Shell
void lsh_loop(void)
{
    char *line;
    char **args;
    int status;

    // Use do-while loop since it is more convenient for checking status variable
    do
    {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args); // Determines when to exit as well

        free(line);
        free(args);

    } while (status);
}

int main(int argc, char **argv)
{
    // Load Configuration files, if any

    // Run Command Loop --> will interpret commands
    lsh_loop();

    // Perform any shutdown/cleanup

    return EXIT_SUCCESS;
}