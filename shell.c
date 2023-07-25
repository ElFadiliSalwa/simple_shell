#include "main.h"

/**
 * main - interpretes a command
 *
 * Return: int
 */
int main(void)
{
        char *command;

        while (1)
        {
                display_prompt();
                command = read_input();

                if (command == NULL)
                {
                        printf("\n");
                        break;
                }

                if (*command != '\0')
                        execute_command(command);

                free(command);
        }
        return EXIT_SUCCESS;
}

/**
 * display_prompt - displays a prompt and waits for the user to type a cmd
 */
void display_prompt()
{
        printf("#cisfun$ ");
}

/**
 * read_input - reads the input
 *
 * Return: char
 */
char *read_input()
{
        ssize_t buffer_size = BUFFER_SIZE;
        char *buffer = malloc(buffer_size);
        ssize_t characters_read;

        if (buffer == NULL)
        {
                perror("malloc");
                exit(EXIT_FAILURE);
        }

        characters_read = getline(&buffer, &buffer_size, stdin);
        if (characters_read == -1)
        {
                free(buffer);
                return NULL;
        }

        buffer[characters_read - 1] = '\0';
        return buffer;
}

/**
 * execute_command - executes the command
 * @command: the command to execute
 */
void execute_command(char *command)
{

        pid_t child_pid;
        int status;

        child_pid = fork();
        if (child_pid == -1)
        {
                perror("fork");
                exit(EXIT_FAILURE);
        }
        if (child_pid == 0)
        {
                char *argv[] = {command, NULL};
                execve(command, argv, NULL);
                perror(command);
                _exit(EXIT_FAILURE);
        }
        else
                waitpid(child_pid, &status, 0);
}
