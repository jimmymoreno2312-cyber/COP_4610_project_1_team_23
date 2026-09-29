/*
 * execute.c - Part 5: External Command Execution
 *             Part 7: Piping
 */
#include "execute.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "jobs.h"
#include "path_search.h"
#include "redirect.h"

/* The base assignment allows at most two pipes, i.e. three commands. */
#define MAX_PIPES 2
#define MAX_PIPE_CMDS (MAX_PIPES + 1)

static void close_pipes(int pipes[][2], int num_pipes)
{
    for (int i = 0; i < num_pipes; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
}

/*
 * Child side: wires command i of n to its neighbours' pipes and to any redirection
 * files, closes every descriptor it no longer needs, then execs. Never returns.
 */
static void run_child(int i, int n, int pipes[][2], int in_fd, int out_fd,
                      const char *path, const simple_cmd *cmd)
{
    if (i > 0 && dup2(pipes[i - 1][0], STDIN_FILENO) == -1) {
        perror("dup2");
        _exit(EXIT_FAILURE);
    }
    if (i < n - 1 && dup2(pipes[i][1], STDOUT_FILENO) == -1) {
        perror("dup2");
        _exit(EXIT_FAILURE);
    }
    close_pipes(pipes, n - 1);

    /* Redirection files are only opened for single commands (n == 1). */
    if (apply_redirection(in_fd, out_fd) == -1)
        _exit(EXIT_FAILURE);

    exec_command(path, cmd);
}

int run_pipeline(pipeline *p)
{
    (void)p;
    fprintf(stderr, "external commands not implemented yet\n");
    return -1;
}

void exec_command(const char *path, const simple_cmd *cmd)
{
    /* argv[0] stays as the name the user typed; path is the resolved executable. */
    execv(path, cmd->argv);

    /* execv only returns on failure. _exit skips the parent's stdio buffers. */
    fprintf(stderr, "%s: %s\n", cmd->argv[0], strerror(errno));
    _exit(EXIT_FAILURE);
}
