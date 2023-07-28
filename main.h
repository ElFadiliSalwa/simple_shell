#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

void display_prompt();
char *read_input();
void execute_command(char *command);

#endif
