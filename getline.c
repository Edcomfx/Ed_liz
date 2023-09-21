#include "shell.h"

/**
 * input_buf - Read and buffer chained commands.
 * @info: Pointer to the parameter struct.
 * @buf: Address of the buffer.
 * @len: Address of the length variable.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t read_bytes = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/* bfree((void **)info->cmd_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		read_bytes = getline(buf, &len_p, stdin);
#else
		read_bytes = _getline(info, buf, &len_p);
#endif
		if (read_bytes > 0)
		{
			if ((*buf)[read_bytes - 1] == '\n')
			{
				(*buf)[read_bytes - 1] = '\0'; /* remove trailing newline */
				read_bytes--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = read_bytes;
				info->cmd_buf = buf;
			}
		}
	}
	return (read_bytes);
}

/**
 * get_input - Get a line without the newline character.
 * @info: Pointer to the parameter struct.
 *
 * Return: The number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, k, len;
	ssize_t read_bytes = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	read_bytes = input_buf(info, &buf, &len);
	if (read_bytes == -1) /* EOF */
		return (-1);
	if (len)    /* there are commands left in the chain buffer */
	{
		k = i; /* initialize a new iterator to the current buf position */
		p = buf + i; /* Get a pointer for return */

		check_chain(info, buf, &k, i, len);
		while (k < len) /* Iterate to semicolon or end */
		{
			if (is_chain(info, buf, k))
				break;
			k++;
		}

		i = k + 1; /* Increment past nulled ';'' */
		if (i >= len) /* Reached the end of the buffer? */
		{
			i = len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Pass back a pointer to the current command position */
		return (_strlen(p)); /* Return the length of the current command */
	}

	*buf_p = buf; /* Otherwise, not a chain; pass back buffer from _getline() */
	return (read_bytes); /* Return the length of the buffer from _getline() */
}

/**
 * read_buf - Read data into a buffer.
 * @info: Pointer to the parameter struct.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: Number of bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t read_bytes = 0;

	if (*i)
		return (0);
	read_bytes = read(info->readfd, buf, READ_BUF_SIZE);
	if (read_bytes >= 0)
		*i = read_bytes;
	return (read_bytes);
}

/**
 * _getline - Read the next line of input from STDIN.
 * @info: Pointer to the parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: The number of bytes read.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t read_bytes = 0, total_bytes = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		total_bytes = *length;
	if (i == len)
		i = len = 0;

	read_bytes = read_buf(info, buf, &len);
	if (read_bytes == -1 || (read_bytes == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, total_bytes, total_bytes ? total_bytes + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (total_bytes)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	total_bytes += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = total_bytes;
	*ptr = p;
	return (total_bytes);
}

/**
 * sigintHandler - Block Ctrl-C signal.
 * @sig_num: The signal number.
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}


