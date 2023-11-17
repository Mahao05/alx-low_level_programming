#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 1024
#define USAGE "Usage: cp file_from file_to\n"
#define READ_ERR "Error: Can't read from file %s\n"
#define WRITE_ERR "Error: Can't write to %s\n"
#define CLOSE_ERR "Error: Can't close fd %d\n"

/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: Arguments vector
 * @return: 0 on success, 97, 98, 99 or 100 on error
 */
int main(int argc, char **argv)
{
	int fd_from, fd_to, n, m;
	char buffer[BUFSIZE];
	mode_t mode;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, USAGE);
		exit(97);
	}
	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, READ_ERR, argv[1]);
		exit(98);
	}
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, WRITE_ERR, argv[2]);
		exit(99);
	}
	while ((n = read(fd_from, buffer, BUFSIZE)) > 0)
	{
		m = write(fd_to, buffer, n);
		if (m != n)
		{
			dprintf(STDERR_FILENO, WRITE_ERR, argv[2]);
			exit(99);
		}
	}
	if (n == -1)
	{
		dprintf(STDERR_FILENO, READ_ERR, argv[1]);
		exit(98);
	}
	if (close(fd_from) == -1)
	{
		dprintf(STDERR_FILENO, CLOSE_ERR, fd_from);
		exit(100);
	}
	if (close(fd_to) == -1)
	{
		dprintf(STDERR_FILENO, CLOSE_ERR, fd_to);
		exit(100);
	}
	return (0);
}
