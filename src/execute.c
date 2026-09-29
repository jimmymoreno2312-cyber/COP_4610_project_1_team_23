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
    int n = p->num_cmds;
    char *paths[MAX_PIPE_CMDS] = {NULL};
    pid_t pids[MAX_PIPE_CMDS];
    int pipes[MAX_PIPES][2];
    int num_pipes = 0;
    int num_forked = 0;
    int in_fd = -1;
    int out_fd = -1;
    int result = -1;

    if (n > MAX_PIPE_CMDS) {
        fprintf(stderr, "error: at most %d pipes are supported\n", MAX_PIPES);
        return -1;
    }
    if (n > 1 && (p->input_file != NULL || p->output_file != NULL)) {
        fprintf(stderr, "error: piping and I/O redirection together is not supported\n");
        return -1;
    }

    /* Resolve every command before forking so a typo doesn't start half a pipeline. */
    for (int i = 0; i < n; i++) {
        paths[i] = search_path(p->cmds[i].argv[0]);
        if (paths[i] == NULL) {
            fprintf(stderr, "%s: command not found\n", p->cmds[i].argv[0]);
            goto cleanup;
        }
    }

    if (p->input_file != NULL && (in_fd = open_input_file(p->input_file)) == -1)
        goto cleanup;
    if (p->output_file != NULL && (out_fd = open_output_file(p->output_file)) == -1)
        goto cleanup;

    for (; num_pipes < n - 1; num_pipes++) {
        if (pipe(pipes[num_pipes]) == -1) {
            perror("pipe");
            goto cleanup;
        }
    }

    for (; num_forked < n; num_forked++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            break;
        }
        if (pid == 0)
            run_child(num_forked, n, pipes, in_fd, out_fd, paths[num_forked],
                      &p->cmds[num_forked]);
        pids[num_forked] = pid;
    }

    /* The parent must close its pipe ends, or readers never see end-of-file. */
    close_pipes(pipes, num_pipes);
    num_pipes = 0;

    if (p->background && num_forked == n) {
        jobs_add(pids, num_forked, p->cmdline);
    } else {
        for (int i = 0; i < num_forked; i++)
            waitpid(pids[i], NULL, 0);
    }
    if (num_forked == n)
        result = 0;

cleanup:
    close_pipes(pipes, num_pipes);
    if (in_fd != -1)
        close(in_fd);
    if (out_fd != -1)
        close(out_fd);
    for (int i = 0; i < n; i++)
        free(paths[i]);
    return result;
}

void exec_command(const char *path, const simple_cmd *cmd)
{
    /* argv[0] stays as the name the user typed; path is the resolved executable. */
    execv(path, cmd->argv);

    /* execv only returns on failure. _exit skips the parent's stdio buffers. */
    fprintf(stderr, "%s: %s\n", cmd->argv[0], strerror(errno));
    _exit(EXIT_FAILURE);
}
