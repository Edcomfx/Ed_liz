#include "shell.h"

/*
 * main - entry point
 * Description - a function that executes a prompt
 * using the fork, wait and execlp functions.
 */
void execute_command(const char *command)
{
	pid_t child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		execlp(command, command, (char *)NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}
