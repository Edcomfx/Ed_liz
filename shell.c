#include "shell.h"
#include <stdbool.h>

/*
 * main - entry point
 * this is my source code file.
 */
int main(void)
{
	char command[127];
	while (true)
	{
		customized_prompt();
		user_input(command, sizeof(command));
		execute_command(command);
	}
	return 0;
}
