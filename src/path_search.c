/* path_search.c - Part 4: $PATH Search */
#include "path_search.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

char *search_path(const char *cmd)
{
    if (strchr(cmd, '/') != NULL)
        return strdup(cmd);

    char *path = getenv("PATH");
    if (path == NULL)
        return NULL;

    // Work on a copy because strtok modifies its input
    char *copy = strdup(path);
    if (copy == NULL)
        return NULL;

    char full[1024];
    char *dir = strtok(copy, ":");

    // Build "dir/cmd" for each $PATH directory and return the first executable one
    while (dir != NULL)
    {
        snprintf(full, sizeof full, "%s/%s", dir, cmd);

        if (access(full, X_OK) == 0)
        {
            free(copy);
            return strdup(full);
        }

        dir = strtok(NULL, ":");
    }

    free(copy);
    return NULL;    // not found; the caller prints "command not found"
}
