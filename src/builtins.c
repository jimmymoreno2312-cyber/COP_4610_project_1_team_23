/* builtins.c - Part 9: Internal Command Execution (exit, cd, jobs) */
#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jobs.h"

static int builtin_cd(const simple_cmd *cmd)
{
    (void)cmd;
    fprintf(stderr, "cd: not implemented yet\n");
    return -1;
}

bool is_builtin(const pipeline *p)
{
    if (p->num_cmds != 1)
        return false;
    const char *name = p->cmds[0].argv[0];
    return strcmp(name, "exit") == 0 || strcmp(name, "cd") == 0 ||
           strcmp(name, "jobs") == 0;
}

int run_builtin(const pipeline *p)
{
    const simple_cmd *cmd = &p->cmds[0];
    const char *name = cmd->argv[0];

    if (strcmp(name, "exit") == 0)
        builtin_exit();
    if (strcmp(name, "cd") == 0)
        return builtin_cd(cmd);

    jobs_list();
    return 0;
}

void history_add(const char *cmdline)
{
    (void)cmdline;
}

void builtin_exit(void)
{
    jobs_wait_all();
    exit(EXIT_SUCCESS);
}
