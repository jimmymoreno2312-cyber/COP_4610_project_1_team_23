/*
 * execute.c - Part 5: External Command Execution (owner: Pedro, support: Jimmy)
 *             Part 7: Piping                      (owner: Jimmy, support: Pedro)
 *             Extra credit: unlimited pipes, piping + I/O redirection (Jimmy, Sarah)
 */
#include "execute.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "jobs.h"
#include "path_search.h"
#include "redirect.h"

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
