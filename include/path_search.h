#ifndef PATH_SEARCH_H
#define PATH_SEARCH_H

/*
 * Resolves a command name to an executable path.
 * Names containing '/' are used as-is; otherwise each $PATH directory is searched.
 * Returns a newly allocated path, or NULL if the command was not found.
 */
char *search_path(const char *cmd);

#endif
