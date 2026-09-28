/*
 * path_search.c - Part 4: $PATH Search
 * Owner: Sarah (support: Jimmy)
 */
#include "path_search.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

char *search_path(const char *cmd)
{
    if (strchr(cmd, '/') != NULL)
        return strdup(cmd);

     // TODO(Sarah): search $PATH.
      char *path = getenv("PATH"); 
        if(path == NULL)
            return NULL; 

     //strdup(getenv("PATH")) and split the copy on ':'
        char *copy = strdup(path);
        if(copy == NULL)
            return NULL; 

        char full[1024]; 
    //(strtok modifies its input).
        char *dir = strtok(copy, ":"); 

    // For each dir, build "dir/cmd" and check it with access(path, X_OK).
    while( dir != NULL)
    {
        snprintf(full, sizeof full, "%s/%s", dir, cmd); 

        //check execute 
        if(access(full, X_OK) == 0)
        {
            free(copy);
            // Return the first match (malloc'd), or NULL so the caller prints
            return strdup(full); 
        }
        
        dir = strtok(NULL, ":"); 
    }

    free(copy); 
    return NULL;    // "command not found".
}
