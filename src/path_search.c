/*
 * path_search.c - Part 4: $PATH Search
 * Owner: Sarah (support: Jimmy)
 */
#include "path_search.h"

#include <stdlib.h>
#include <string.h>

char *search_path(const char *cmd)
{
    if (strchr(cmd, '/') != NULL)
        return strdup(cmd);

    /*
     * TODO(Sarah): search $PATH.
     *  - strdup(getenv("PATH")) and split the copy on ':' (strtok modifies its input).
     *  - For each dir, build "dir/cmd" and check it with access(path, X_OK).
     *  - Return the first match (malloc'd), or NULL so the caller prints
     *    "command not found".
     */
    return NULL;
}
