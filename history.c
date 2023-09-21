#include "shell.h"

/**
 * get_history_filepath - Get the path to the history file.
 * @info: Pointer to the parameter struct.
 *
 * Return: Allocated string containing the history file path,
 * or NULL on failure.
 */
char *get_history_filepath(info_t *info)
{
	char *home_dir, *f_path;

	home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return (NULL);

	f_path = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!file_path)
		return (NULL);

	file_path[0] = '\0';
	_strcpy(file_path, home_dir);
	_strcat(file_path, "/");
	_strcat(file_path, HIST_FILE);

	return (file_path);
}

/**
 * write_history_to_file - Write the command history to a file.
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history_to_file(info_t *info)
{
	ssize_t file_descriptor;
	char *file_path = get_history_filepath(info);
	list_t *h_node = NULL;

	if (!file_path)
		return (-1);

	file_descriptor = open(file_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_path);

	if (file_descriptor == -1)
		return (-1);

	for (node = info->history; h_node; h_node = h_node->next)
	{
		_putsfd(h_node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}

	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * read_history_from_file - Read command history from a file.
 * @info: Pointer to the parameter struct.
 *
 * Return: Number of lines read on success, 0 on failure.
 */
int read_history_from_file(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stat;
	char *buf = NULL, *file_path = get_history_filepath(info);

	if (!file_path)
		return (0);

	file_descriptor = open(file_path, O_RDONLY);
	free(file_path);

	if (file_descriptor == -1)
		return (0);

	if (!fstat(file_descriptor, &file_stat))
		file_size = file_stat.st_size;

	if (file_size < 2)
		return (0);

	buf = malloc(sizeof(char) * (file_size + 1));
	if (!buf)
		return (0);

	read_length = read(file_descriptor, buf, file_size);
	buf[file_size] = '\0';

	if (read_length <= 0)
		return (free(buf), 0);

	close(file_descriptor);

	for (i = 0; i < file_size; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, line_count++);
			last = i + 1;
		}
	}

	if (last != i)
		build_history_list(info, buf + last, line_count++);

	free(buf);
	info->histcount = line_count;

	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renum_history(info);
	return (info->histcount);
}

/**
 * add_to_history - Add a command to the history linked list.
 * @info: Pointer to the parameter struct.
 * @command: The command to add to the history.
 * @line_count: The line count in the history.
 *
 * Return: Always 0.
 */
int add_to_history(info_t *info, char *command, int line_count)
{
	list_t *history_node = NULL;

	if (info->history)
		history_node = info->history;

	add_node_end(&history_node, command, line_count);

	if (!info->history)
		info->history = history_node;

	return (0);
}

/**
 * renumber_history_list - Renumber the history linked list after changes.
 * @info: Pointer to the parameter struct.
 *
 * Return: The new history count.
 */
int renumber_history_list(info_t *info)
{
	list_t *history_node = info->history;
	int i = 0;

	while (history_node)
	{
		history_node->num = i++;
		history_node = history_node->next;
	}

	return (info->histcount = i);
}


