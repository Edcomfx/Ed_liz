#include "shell.h"

/**
 * _myexit - Exits the shell
 * @info: Pointer to a structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int _myexit(info_t *info)
{
	int exit_code;

	if (info->argv[1]) /* Check if there is an exit argument */
	{
		exit_code = _erratoi(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			print_error(info, "illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Changes the current directory of the process
 * @info: Pointer to a structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _mycd(info_t *info)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure message here<<\n");
	if (!info->argv[1])
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
			chdir_result = /* TODO: Define appropriate value here */
				chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
		else
			chdir_result = chdir(target_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_result = /* TODO: Define appropriate value here */
			chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);
	if (chdir_result == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Provides help information
 * @info: Pointer to a structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
	char **args;

	args = info->argv;
	_puts("Help function called. Function not yet implemented.\n");
	if (0)
		_puts(*args); /* Temporary unused argument workaround */
	return (0);
}


