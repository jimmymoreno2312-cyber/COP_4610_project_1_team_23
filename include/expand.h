#ifndef EXPAND_H
#define EXPAND_H

#include "lexer.h"

/* Applies environment-variable and tilde expansion to every token, in place. */
void expand_tokens(tokenlist *tokens);

/* "$NAME" -> value of NAME. Returns a newly allocated string. */
char *expand_env_var(const char *token);

/* "~" or "~/path" -> "$HOME" or "$HOME/path". Returns a newly allocated string. */
char *expand_tilde(const char *token);

#endif
