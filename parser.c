#include "shell.h"

/**
 * is_command - Determines if a file is an executable command.
 * @info: The info struct (not currently used).
 * @path: Path to the file to check.
 *
 * Return: 1 if it's an executable command, 0 otherwise.
 */
int is_command(info_t *info __attribute__((unused)), char *path)
{
	struct stat st;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - Duplicates characters from a string within a given range.
 * @pathstr: The source string.
 * @start: The starting index.
 * @stop: The stopping index.
 *
 * Return: Pointer to a new buffer containing the duplicated characters.
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
		{
			buf[k++] = pathstr[i];
		}
	}
	buf[k] = '\0';
	return (buf);
}

/**
 * find_command_path - Finds the full path of a command within the PATH string.
 * @info: The info struct (not currently used).
 * @pathstr: The PATH string to search.
 * @cmd: The command to find.
 *
 * Return: Full path of the command if found, or NULL if not found.
 */
char *find_command_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_command(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, curr_pos, i);
			if (!*path)
				strcat(path, cmd);
		else
			{
				strcat(path, "/");
				strcat(path, cmd);
			}
			if (is_command(info, path))
				return (path);

			if (!pathstr[i])
				break;

			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

