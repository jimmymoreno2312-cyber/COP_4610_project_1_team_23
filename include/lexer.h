#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

/* A dynamically sized list of whitespace-separated tokens. */
typedef struct {
    char **items;
    size_t size;
} tokenlist;

/* Reads one line from stdin (newline stripped). Returns NULL on EOF. Caller frees. */
char *get_input(void);

/* Splits input on spaces/tabs. Caller frees with free_tokens(). */
tokenlist *get_tokens(const char *input);

void free_tokens(tokenlist *tokens);

#endif
