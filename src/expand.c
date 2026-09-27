/*
 * expand.c - Part 2: Environment Variables (owner: Jimmy, support: Sarah)
 *            Part 3: Tilde Expansion       (owner: Pedro, support: Jimmy)
 */
#include "expand.h"

#include <stdlib.h>
#include <string.h>

void expand_tokens(tokenlist *tokens)
{
    for (size_t i = 0; i < tokens->size; i++) {
        const char *tok = tokens->items[i];
        char *expanded;

        if (tok[0] == '$' && tok[1] != '\0')
            expanded = expand_env_var(tok);
        else if (tok[0] == '~' && (tok[1] == '\0' || tok[1] == '/'))
            expanded = expand_tilde(tok);
        else
            continue;

        if (expanded != NULL) {
            free(tokens->items[i]);
            tokens->items[i] = expanded;
        }
    }
}

char *expand_env_var(const char *token)
{
    /*
     * TODO(Jimmy): return strdup(getenv(token + 1)).
     *  - Only whole tokens need expanding (e.g. "$USER", not "abc$USER").
     *  - Decide what an unset variable becomes (bash uses an empty string).
     */
    return strdup(token);
}

char *expand_tilde(const char *token)
{
    /*
     * TODO(Pedro): replace the leading "~" with getenv("HOME").
     *  "~" -> "/home/you", "~/dir1" -> "/home/you/dir1".
     */
    return strdup(token);
}
