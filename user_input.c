#include "shell.h"

/*
 * main - entry point
 * user_input - a function that reads user input,
 * handles the EOF condition,
 * Removes new line.
 */
void user_input(char *command, size_t size)
{
	if (fgets(command, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			eby_print("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			eby_print("Error while reading input.\n");
			exit(EXIT_FAILURE);
		}
	}
	command[strcspn(command, "\n")] = '\0';
}
