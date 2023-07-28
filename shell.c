#include "main.h"

/**
 * sig_handler - checks if Ctrl C is pressed
 * @sig_num: int
 */
void sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		_puts("\n#cisfun$ ");
	}
}

/**
* _EOF - handles the End of File
* @len: return value of getline function
* @buff: buffer
 */
void _EOF(int len, char *buff)
{
	(void)buff;
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(buff);
		}
		exit(0);
	}
}
/**
  * _isatty - verif if terminal
  */

void _isatty(void)
{
	if (isatty(STDIN_FILENO))
		_puts("#cisfun$ ");
}

/**
 * main - Shell
 * Return: 0 on success
 */

int main(void)
{
    char input[MAX_INPUT_LENGTH];
    char* arguments[MAX_ARGUMENTS];

    signal(SIGINT, sig_handler);

    while (1)
    {
        _isatty();

        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
	{
            _puts("\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) > 0)
	{
            char* token = strtok(input, " ");
            int argCount = 0;

            while (token != NULL && argCount < MAX_ARGUMENTS - 1)
	    {
                arguments[argCount] = token;
                argCount++;
                token = strtok(NULL, " ");
            }

            arguments[argCount] = NULL;

            if (execvp(arguments[0], arguments) == -1)
	    {
                _puts("./shell: No such file or directory\n");
            }
        }
    }
	return (0);
}
