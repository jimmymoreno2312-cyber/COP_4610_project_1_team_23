/*
 * expand.c - Part 2: Environment Variables (owner: Jimmy, support: Sarah)
 *            Part 3: Tilde Expansion       (owner: Pedro, support: Jimmy)
 */
#include "expand.h"

#include <stdlib.h>
#include <string.h>

void expand_tokens(tokenlist *tokens)
{
    size_t kept = 0;

    for (size_t i = 0; i < tokens->size; i++) {
        char *tok = tokens->items[i];

        if (tok[0] == '$' && tok[1] != '\0') {
            char *value = expand_env_var(tok);
            free(tok);
            if (value == NULL)  /* unset variable: drop the token, like bash */
                continue;
            tok = value;
        } else if (tok[0] == '~' && (tok[1] == '\0' || tok[1] == '/')) {
            char *expanded = expand_tilde(tok);
            if (expanded != NULL) {
                free(tok);
                tok = expanded;
            }
        }

        tokens->items[kept++] = tok;
    }
    tokens->size = kept;
}

char *expand_env_var(const char *token)
{
    const char *value = getenv(token + 1);  /* skip the leading '$' */

    return value != NULL ? strdup(value) : NULL;
}

char *expand_tilde(const char *token)
{
    /*
     * TODO(Pedro): replace the leading "~" with getenv("HOME").
     *  "~" -> "/home/you", "~/dir1" -> "/home/you/dir1".
     */
    return strdup(token);
}
