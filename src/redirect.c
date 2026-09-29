/*
 * redirect.c - Part 6: I/O Redirection
 * Owner: Jimmy (support: Sarah)
 */
#include "redirect.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* -rw------- */
#define OUTPUT_FILE_MODE (S_IRUSR | S_IWUSR)

int open_input_file(const char *path)
{
    struct stat info;

    if (stat(path, &info) == -1) {
        fprintf(stderr, "%s: %s\n", path, strerror(errno));
        return -1;
    }
    if (!S_ISREG(info.st_mode)) {
        fprintf(stderr, "%s: not a regular file\n", path);
        return -1;
    }

    /* Read-only so the input file is never modified. */
    int fd = open(path, O_RDONLY);
    if (fd == -1)
        fprintf(stderr, "%s: %s\n", path, strerror(errno));
    return fd;
}

int open_output_file(const char *path)
{
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, OUTPUT_FILE_MODE);

    if (fd == -1) {
        fprintf(stderr, "%s: %s\n", path, strerror(errno));
        return -1;
    }

    /* O_TRUNC keeps an existing file's mode, so reset it to -rw------- explicitly. */
    if (fchmod(fd, OUTPUT_FILE_MODE) == -1) {
        fprintf(stderr, "%s: %s\n", path, strerror(errno));
        close(fd);
        return -1;
    }
    return fd;
}

int apply_redirection(int in_fd, int out_fd)
{
    if (in_fd != -1) {
        if (dup2(in_fd, STDIN_FILENO) == -1) {
            perror("dup2");
            return -1;
        }
        close(in_fd);
    }
    if (out_fd != -1) {
        if (dup2(out_fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            return -1;
        }
        close(out_fd);
    }
    return 0;
}
