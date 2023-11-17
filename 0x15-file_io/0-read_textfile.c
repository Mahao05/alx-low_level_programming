#include "main.h"
#include <stdlib.h>

/**
 * read_textfile- Read text file print to STDOUT.
 * @filename: text file being read
 * @letters: number of letters to be read
 * Return: w- actual number of bytes read and printed
 *        0 when function fails or filename is NULL.
 */

ssize_t read_textfile(const char *filename, size_t letters) {
    if (filename == NULL) {
        return 0;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    char *buffer = (char *) malloc(letters + 1);
    if (buffer == NULL) {
        fclose(file);
        return 0;
    }

    ssize_t bytes_read = fread(buffer, sizeof(char), letters, file);
    if (bytes_read == -1) {
        fclose(file);
        free(buffer);
        return 0;
    }

    buffer[bytes_read] = '\0';
    printf("%s", buffer);

    free(buffer);
    fclose(file);

    return bytes_read;
}
