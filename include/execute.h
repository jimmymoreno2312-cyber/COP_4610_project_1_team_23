#ifndef EXECUTE_H
#define EXECUTE_H

#include "command.h"

/*
 * Runs an external pipeline (one or more commands) with its redirections.
 * Foreground: waits for every child. Background: registers a job and returns.
 * Returns 0 if the command was valid and started, -1 otherwise.
 */
int run_pipeline(pipeline *p);

/* Child side only: execv(path, cmd->argv). Never returns. */
void exec_command(const char *path, const simple_cmd *cmd);

#endif
