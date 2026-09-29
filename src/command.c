/*
 * command.c - turns a token list into a pipeline struct
 * (commands, pipes, "<" / ">" files, and a trailing "&").
 */
#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_operator(const char *tok)
{
    return strcmp(tok, "|") == 0 || strcmp(tok, "<") == 0 ||
           strcmp(tok, ">") == 0 || strcmp(tok, "&") == 0;
}

static pipeline *parse_error(pipeline *p, const char *message)
{
    fprintf(stderr, "syntax error: %s\n", message);
    free_pipeline(p);
    return NULL;
}

pipeline *parse_pipeline(const tokenlist *tokens, const char *cmdline)
{
    size_t num_tokens = tokens->size;
    pipeline *p = calloc(1, sizeof(pipeline));

    if (p == NULL)
        return NULL;
    p->cmdline = strdup(cmdline);

    if (num_tokens > 0 && strcmp(tokens->items[num_tokens - 1], "&") == 0) {
        p->background = true;
        num_tokens--;
    }

    p->num_cmds = 1;
    for (size_t i = 0; i < num_tokens; i++)
        if (strcmp(tokens->items[i], "|") == 0)
            p->num_cmds++;

    p->cmds = calloc(p->num_cmds, sizeof(simple_cmd));
    if (p->cmds == NULL)
        return parse_error(p, "out of memory");

    /* num_tokens + 1 is an upper bound on any single command's argv length. */
    for (int c = 0; c < p->num_cmds; c++) {
        p->cmds[c].argv = calloc(num_tokens + 1, sizeof(char *));
        if (p->cmds[c].argv == NULL)
            return parse_error(p, "out of memory");
    }

    int current = 0;
    for (size_t i = 0; i < num_tokens; i++) {
        const char *tok = tokens->items[i];

        if (strcmp(tok, "|") == 0) {
            if (p->cmds[current].argc == 0)
                return parse_error(p, "missing command before '|'");
            current++;
        } else if (strcmp(tok, "<") == 0 || strcmp(tok, ">") == 0) {
            if (i + 1 >= num_tokens || is_operator(tokens->items[i + 1]))
                return parse_error(p, "missing file name after redirection");
            /* In a pipeline, input feeds the first command and output leaves the last. */
            if (tok[0] == '<' && current != 0)
                return parse_error(p, "'<' is only allowed on the first command");
            if (tok[0] == '>' && current != p->num_cmds - 1)
                return parse_error(p, "'>' is only allowed on the last command");
            char **target = (tok[0] == '<') ? &p->input_file : &p->output_file;
            free(*target);
            *target = strdup(tokens->items[++i]);
        } else if (strcmp(tok, "&") == 0) {
            return parse_error(p, "'&' is only allowed at the end of a command");
        } else {
            simple_cmd *cmd = &p->cmds[current];
            cmd->argv[cmd->argc++] = strdup(tok);
        }
    }

    if (p->cmds[current].argc == 0)
        return parse_error(p, p->num_cmds > 1 ? "missing command after '|'"
                                              : "missing command");
    return p;
}

void free_pipeline(pipeline *p)
{
    if (p == NULL)
        return;
    if (p->cmds != NULL) {
        for (int c = 0; c < p->num_cmds; c++) {
            if (p->cmds[c].argv == NULL)
                continue;
            for (int a = 0; a < p->cmds[c].argc; a++)
                free(p->cmds[c].argv[a]);
            free(p->cmds[c].argv);
        }
        free(p->cmds);
    }
    free(p->input_file);
    free(p->output_file);
    free(p->cmdline);
    free(p);
}
