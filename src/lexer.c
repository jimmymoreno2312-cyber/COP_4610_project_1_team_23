/* lexer.c - reads input and splits it into tokens. */
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_CHUNK 128

char *get_input(void)
{
    size_t capacity = INPUT_CHUNK;
    size_t length = 0;
    char *buffer = malloc(capacity);
    char chunk[INPUT_CHUNK];

    if (buffer == NULL)
        return NULL;
    buffer[0] = '\0';

    /* Keep reading chunks until we see the newline, so long lines aren't truncated. */
    while (fgets(chunk, sizeof(chunk), stdin) != NULL) {
        size_t chunk_len = strlen(chunk);

        if (length + chunk_len + 1 > capacity) {
            capacity = (length + chunk_len + 1) * 2;
            char *grown = realloc(buffer, capacity);
            if (grown == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = grown;
        }
        memcpy(buffer + length, chunk, chunk_len + 1);
        length += chunk_len;

        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
            return buffer;
        }
    }

    /* EOF: return a final unterminated line if there was one. */
    if (length > 0)
        return buffer;
    free(buffer);
    return NULL;
}

static void add_token(tokenlist *tokens, const char *item)
{
    char **grown = realloc(tokens->items, (tokens->size + 1) * sizeof(char *));
    if (grown == NULL)
        return;
    tokens->items = grown;
    tokens->items[tokens->size] = strdup(item);
    tokens->size++;
}

tokenlist *get_tokens(const char *input)
{
    tokenlist *tokens = calloc(1, sizeof(tokenlist));
    char *copy = strdup(input);

    if (tokens == NULL || copy == NULL) {
        free(tokens);
        free(copy);
        return NULL;
    }

    for (char *tok = strtok(copy, " \t"); tok != NULL; tok = strtok(NULL, " \t"))
        add_token(tokens, tok);

    free(copy);
    return tokens;
}

void free_tokens(tokenlist *tokens)
{
    if (tokens == NULL)
        return;
    for (size_t i = 0; i < tokens->size; i++)
        free(tokens->items[i]);
    free(tokens->items);
    free(tokens);
}
