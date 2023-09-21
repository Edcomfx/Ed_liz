#include "shell.h"

/**
 * _myhistory - Displays the command history with line numbers.
 * @info: Pointer to a structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myhistory(info_t *info)
{
	print_command_history(info->history);
	return (0);
}

/**
 * unset_alias - Removes an alias from the alias list.
 * @info: Pointer to a structure containing potential arguments.
 * @alias_str: The alias string to unset.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *alias_str)
{
	char *j, k;
	int ret;

	j = _strchr(alias_str, '=');
	if (!j)
		return (1);
	k = *j;
	*j = 0;
	ret = delete_alias(&(info->alias),
			find_alias(info->alias, alias_str));
	*j = k;
	return (ret);
}

/**
 * set_alias - Sets an alias by adding it to the alias list.
 * @info: Pointer to a structure containing potential arguments.
 * @alias_str: The alias string to set.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *alias_str)
{
	char *k;

	k = _strchr(alias_str, '=');
	if (!k)
		return (1);
	if (!*++k)
		return (unset_alias(info, alias_str));

	unset_alias(info, alias_str);
	return (add_alias_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @alias_node: Pointer to an alias node to print.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *alias_node)
{
	char *k = NULL, *a = NULL;

	if (alias_node)
	{
		k = _strchr(alias_node->str, '=');
		for (a = alias_node->str; a <= k; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(k + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics the behavior of the alias built-in command.
 * @info: Pointer to a structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *k = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			print_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		k = _strchr(info->argv[i], '=')
			if (k)
				set_alias(info, info->argv[i]);
			else
				print_alias(find_alias(info->alias, info->argv[i]));
	}

	return (0);
}


