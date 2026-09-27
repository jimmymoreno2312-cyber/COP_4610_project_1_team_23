/*
 * redirect.c - Part 6: I/O Redirection
 * Owner: Jimmy (support: Sarah)
 */
#include "redirect.h"

#include <stdio.h>

int open_input_file(const char *path)
{
    /*
     * TODO(Jimmy):
     *  - stat() the path: error if it doesn't exist or !S_ISREG.
     *  - open(path, O_RDONLY) so the input file is never modified.
     */
    fprintf(stderr, "%s: input redirection not implemented yet\n", path);
    return -1;
}

int open_output_file(const char *path)
{
    /*
     * TODO(Jimmy): open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR).
     *  - An existing file is overwritten, not appended.
     */
    fprintf(stderr, "%s: output redirection not implemented yet\n", path);
    return -1;
}
