#include "shell.h"

/*
 * main - entry point.
 * _print - a program that creates my own print function.
 */
void eby_print(const char *errand)
{
	write(STDOUT_FILENO, errand, strlen(errand));
}
