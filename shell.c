#include "main.h"

/**
 * main - initialises the program's variables
 * @argc: count args
 * @argv: value args
 * @env: environ's values
 * Return: 0 in success
 */
int main(int argc, char *argv[], char *env[])
{
    data_of_program data_struct = {NULL}, *data = &data_struct;
    char *prompt = "";
    initializeData(data, argc, argv, env);
    signal(SIGINT, handle_ctrl_c);
    if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
    {
        errno = 2;
        prompt = PROMPT_MSG;
    }
    errno = 0;
    sisifo(prompt, data);

    return (0);
}

/**
 * handleCtrlC - prints the prompt in a new line
 * @UNUSED: unused property
 */
void handleCtrlC(int opr UNUSED)
{
    _print("\n");
    _print(PROMPT_MSG);
}

/**
 * initializeData - initialises the struct with the program's info
 * @data: pointer to the struct
 * @argv: value args
 * @env: passed environ
 * @argc: count args
 */
void initializeData(data_of_program *data, int argc, char *argv[], char **env)
{
    int i = 0;

    data->program_name = argv[0];
    data->input_line = NULL;
    data->command_name = NULL;
    data->exec_counter = 0;

    if (argc == 1)
    {
        data->file_descriptor = STDIN_FILENO;
    }
    else
    {
        data->file_descriptor = open(argv[1], O_RDONLY);
        if (data->file_descriptor == -1)
        {
            _printe(data->program_name);
            _printe(": 0: Can't open ");
            _printe(argv[1]);
            _printe("\n");
            exit(127);
        }
    }

    data->env = malloc(sizeof(char *) * 50);
    if (env)
    {
        for (; env[i]; i++)
        {
            data->env[i] = str_duplicate(env[i]);
        }
    }
    data->env[i] = NULL;
    env = data->env;
    data->alias_list = malloc(sizeof(char *) * 20);
    for (i = 0; i < 20; i++)
    {
        data->alias_list[i] = NULL;
    }
}

/**
 * sisifo - shows the prompt infinitely
 * @prompt: printed prompt
 * @data: pointer to the data
 */
void sisifo(char *prompt, data_of_program *data)
{
    int error_code = 0, string_len = 0;

    while (++(data->exec_counter))
    {
        _print(prompt);

        error_code = string_len = _getline(data);

        if (error_code == EOF)
        {
            free_all_data(data);
            exit(errno);
        }
        if (string_len >= 1)
        {
            expand_alias(data);
            expand_variables(data);
            tokenize(data);
            if (data->tokens[0])
            {
                error_code = execute(data);
                if (error_code != 0)
                    _print_error(error_code, data);
            }
            free_recurrent_data(data);
        }
    }
}
