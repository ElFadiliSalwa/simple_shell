/**
  * main - handles the path
  *
  * Return: int
  */
int main(void)
{
  char *prompt = "#cisfun$ ";
  char *line;
  size_t bufsize = 0;
  ssize_t characters;
  while (1)
  {
    printf("%s", prompt);
    characters = getline(&line, &bufsize, stdin);
    if (characters == -1)
    {
      printf("\n");
      break;
    }
    line[strcspn(line, "\n")] = '\0';
    char *command = strtok(line, " ");
    char *arg = strtok(NULL, " ");
    if (command != NULL)
    {
      pid_t pid = fork();
      if (pid == -1)
        perror("fork");
      else if (pid == 0)
      {
        if (execvp(command, (char *const[]){command, arg, NULL}) == -1)
        {
          perror(command);
          exit(EXIT_FAILURE);
        }
      }
      else
        wait(NULL);
    }
  }
  free(line);
  return EXIT_SUCCESS;
}
