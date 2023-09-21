#include "shell.h"

/**
 * is_interactive_mode - Checks if the shell is in interactive mode.
 * @info: Pointer to the shell information struct.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int is_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiters - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delimiters: The delimiter characters.
 *
 * Return: 1 if it's a delimiter, 0 otherwise.
 */
int is_delimiters(char c, char *delimiters)
{
	while (*delimiters)
	{
		if (*delimiters++ == c)
			return (1);
	}
	return (0);
}

/**
 * _isalpha - Checks if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c  <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * string_to_integer - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: 0 if no numbers in the string, the converted number otherwise.
 */
int string_to_integer(char *str)
{
	int j, sign = 1, flag = 0, result = 0;

	for (j = 0; str[j] != '\0' && flag != 2; j++)
	{
		if (str[j] == '-')
			sign *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -result;

	return (result);
}



