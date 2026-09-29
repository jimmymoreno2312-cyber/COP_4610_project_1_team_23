/*
 * execute.c - Part 5: External Command Execution (owner: Pedro, support: Jimmy)
 *             Part 7: Piping                      (owner: Jimmy, support: Pedro)
 *             Extra credit: unlimited pipes, piping + I/O redirection (Jimmy, Sarah)
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
    /*
     * TODO(Jimmy + Pedro): general N-command pipeline (N == 1 means no pipes).
     *  1. Resolve every argv[0] with search_path() BEFORE forking. If one is NULL,
     *     print "<cmd>: command not found" and return -1.
     *  2. Open p->input_file / p->output_file with open_input_file() /
     *     open_output_file(). On failure return -1.
     *  3. For i in 0..N-1: pipe() if i < N-1, then fork(). In the child:
     *       - stdin  = input file (i == 0) or previous pipe's read end
     *       - stdout = output file (i == N-1) or this pipe's write end
     *       - apply_redirection(in_fd, out_fd) does the dup2() for files; use dup2()
     *         for pipe ends, close every other pipe/file fd, then exec_command().
     *     The parent closes the pipe ends it no longer needs.
     *  4. The parent closes the redirect fds, then either:
     *       - foreground: waitpid() on every child
     *       - background: jobs_add(pids, N, p->cmdline)
     */
    (void)p;
    fprintf(stderr, "external commands not implemented yet\n");
    return -1;
}

void exec_command(const char *path, const simple_cmd *cmd)
{
    /*
     * TODO(Pedro): execv(path, cmd->argv). If it returns, print the error
     * with perror() and _exit(EXIT_FAILURE). Only execv() is allowed.
     */
    (void)path;
    (void)cmd;
    _exit(EXIT_FAILURE);
}
