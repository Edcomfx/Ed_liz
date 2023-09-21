#include "shell.h"

/**
 * _myenv - Prints the current environment.
 * @info: Pointer to a structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
	print_environment(info->env);
	return (0);
}

/**
 * _getenv - Gets the value of an environment variable.
 * @info: Pointer to a structure containing potential arguments.
 * @name: The name of the environment variable to retrieve.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *k;

	while (node)
	{
		k = starts_with(node->str, name);
		if (k && *k)
			return (k);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initializes a new environment variable
 * or modifies an existing one.
 * @info: Pointer to a structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("incorrect number of arguments\n");
		return (1);
	}
	if (set_environment_variable(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Removes an environment variable.
 * @info: Pointer to a structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("too few arguments.\n");
		return (1);
	}
	for (i = 1; i < info->argc; i++)
		unset_environment_variable(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populates the environment linked list.
 * @info: Pointer to a structure containing potential arguments.
 *
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

