#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>

#include "lexer.h"

/* One program invocation: argv[0] is the command name, argv is NULL-terminated. */
typedef struct {
    char **argv;
    int argc;
} simple_cmd;

/*
 * A full command line: cmds[0] | cmds[1] | ... | cmds[num_cmds - 1].
 * A command with no pipes is just num_cmds == 1.
 * input_file feeds cmds[0]; output_file receives the last command's stdout.
 */
typedef struct {
    simple_cmd *cmds;
    int num_cmds;
    char *input_file;   /* from "<", or NULL */
    char *output_file;  /* from ">", or NULL */
    bool background;    /* trailing "&" */
    char *cmdline;      /* original text, used by jobs and exit history */
} pipeline;

/* Builds a pipeline from expanded tokens. Prints an error and returns NULL on bad syntax. */
pipeline *parse_pipeline(const tokenlist *tokens, const char *cmdline);

void free_pipeline(pipeline *p);

#endif
