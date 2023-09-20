#include "shell.h"

/*
 * main - entry point
 * Description: a program that executes a command and
 * tokenizes a arguments
 */
void implement_command(const char *command)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		eby_print("Error forking process.\n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		char *args[127];
		int arg_count = 0;

		char *token = strtok((char *)command, " ");
		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		execvp(args[0], args);

		eby_print("Erorr executing command.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

