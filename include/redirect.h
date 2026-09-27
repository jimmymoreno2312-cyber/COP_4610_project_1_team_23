#ifndef REDIRECT_H
#define REDIRECT_H

/*
 * Opens a file for "<". It must exist and be a regular file.
 * Returns the fd, or -1 after printing an error.
 */
int open_input_file(const char *path);

/*
 * Opens a file for ">": created or truncated with permissions -rw------- (0600).
 * Returns the fd, or -1 after printing an error.
 */
int open_output_file(const char *path);

#endif
