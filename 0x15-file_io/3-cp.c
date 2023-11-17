#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024

/**
 * Copies the content of a file to another file.
 * Usage: cp file_from file_to
 * If the number of argument is not the correct one, exit with code 97 and print Usage: cp file_from file_to, followed by a new line, on the POSIX standard error
 * If file_to already exists, truncate it
 * If file_from does not exist, or if you can not read it, exit with code 98 and print Error: Can't read from file NAME_OF_THE_FILE, followed by a new line, on the POSIX standard error
 * where NAME_OF_THE_FILE is the first argument passed to your program
 * If you can not create or if write to file_to fails, exit with code 99 and print Error: Can't write to NAME_OF_THE_FILE, followed by a new line, on the POSIX standard error
 * where NAME_OF_THE_FILE is the second argument passed to your program
 * If you can not close a file descriptor , exit with code 100 and print Error: Can't close fd FD_VALUE, followed by a new line, on the POSIX standard error
 * where FD_VALUE is the value of the file descriptor
 * Permissions of the created file: rw-rw-r--. If the file already exists, do not change the permissions
 * You must read 1,024 bytes at a time from the file_from to make less system calls. Use a buffer
 * You are allowed to use dprintf
 */
int main(int argc, char *argv[])
{
    int fd_from, fd_to, ret;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // Check the number of arguments
    if (argc != 3)
    {
        dprintf(STDERR_FILENO, "Usage: %s file_from file_to\n", argv[0]);
        exit(97);
    }

    // Open the source file
    fd_from = open(argv[1], O_RDONLY);
    if (fd_from == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
        exit(98);
    }

    // Open the destination file
    fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_to == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
        exit(99);
    }

    // Copy the content of the source file to the destination file
    while ((bytes_read = read(fd_from, buffer, BUFFER_SIZE)) > 0)
    {
        bytes_written = write(fd_to, buffer, bytes_read);
        if (bytes_written != bytes_read)
        {
            dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
            exit(99);
        }
    }

    // Check for errors during the copy process
    if (bytes_read == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
        exit(98);
    }

    // Close the files
    ret = close(fd_from);
    if (ret == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
        exit(100);
    }

    ret = close(fd_to);
    if (ret == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
        exit(100);
    }

    return 0;
}
