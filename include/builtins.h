#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdbool.h>

#include "command.h"

/* True if the pipeline is a single built-in command (exit, cd, jobs). */
bool is_builtin(const pipeline *p);

/* Runs a built-in. Returns 0 on success, -1 on error. */
int run_builtin(const pipeline *p);

/* Records a valid command line for exit's "last three commands" output. */
void history_add(const char *cmdline);

/* Waits for background jobs, prints the command history, and exits the shell. */
void builtin_exit(void);

#endif
