/* builtins.c - Part 9: Internal Command Execution (exit, cd, jobs) */
#include "builtins.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "jobs.h"

#define HISTORY_SIZE 3
#define MAX_CMD_LEN 200

/* The last three valid command lines, oldest first. */
static char history[HISTORY_SIZE][MAX_CMD_LEN];
static int history_count = 0;

static int builtin_cd(const simple_cmd *cmd)
{
    if (cmd->argc > 2) {
        fprintf(stderr, "cd: too many arguments\n");
        return -1;
    }

    const char *target = (cmd->argc == 2) ? cmd->argv[1] : getenv("HOME");
    if (target == NULL) {
        fprintf(stderr, "cd: HOME not set\n");
        return -1;
    }

    struct stat info;
    if (stat(target, &info) == -1) {
        fprintf(stderr, "cd: %s: %s\n", target, strerror(errno));
        return -1;
    }
    if (!S_ISDIR(info.st_mode)) {
        fprintf(stderr, "cd: %s: not a directory\n", target);
        return -1;
    }
    if (chdir(target) == -1) {
        fprintf(stderr, "cd: %s: %s\n", target, strerror(errno));
        return -1;
    }

    /* Keep $PWD in sync with the real working directory. */
    char cwd[4096];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        setenv("PWD", cwd, 1);
    return 0;
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
    /* Once full, drop the oldest entry to make room at the end. */
    if (history_count == HISTORY_SIZE) {
        memmove(history[0], history[1], sizeof(history[0]) * (HISTORY_SIZE - 1));
        history_count--;
    }
    snprintf(history[history_count++], MAX_CMD_LEN, "%s", cmdline);
}

void builtin_exit(void)
{
    jobs_wait_all();

    if (history_count == 0) {
        printf("No valid commands.\n");
    } else if (history_count < HISTORY_SIZE) {
        printf("Last valid command:\n[1]: %s\n", history[history_count - 1]);
    } else {
        printf("Last (%d) valid commands:\n", HISTORY_SIZE);
        for (int i = 0; i < HISTORY_SIZE; i++)
            printf("[%d]: %s\n", i + 1, history[i]);
    }
    exit(EXIT_SUCCESS);
}
