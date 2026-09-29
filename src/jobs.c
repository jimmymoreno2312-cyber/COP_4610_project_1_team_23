/* jobs.c - Part 8: Background Processing */
#include "jobs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/* One background job: every pid in its pipeline plus the original command line. */
struct job {
    int num;
    pid_t *pids;  /* one per command, so pipelines of any length fit */
    int num_pids;
    char *cmdline;
    bool active;
};

static struct job table[MAX_JOBS];
/* Job numbers start at 1 and are never reused. */
static int next_job_num = 1;

void jobs_add(const pid_t *pids, int num_pids, const char *cmdline)
{
    int space = -1;
    for (int i = 0; i < MAX_JOBS; i++) {
        if (!table[i].active) {  /* find an empty slot */
            space = i;
            break;
        }
    }
    if (space == -1)
        return;

    table[space].pids = malloc(num_pids * sizeof(pid_t));
    if (table[space].pids == NULL)
        return;

    table[space].num = next_job_num;
    table[space].num_pids = num_pids;
    table[space].cmdline = strdup(cmdline);
    table[space].active = true;
    for (int i = 0; i < num_pids; i++)
        table[space].pids[i] = pids[i];

    /* The job is reported by the pid of its last command. */
    printf("[%d] %d\n", next_job_num, pids[num_pids - 1]);
    next_job_num++;
}

void jobs_check(void)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (!table[i].active)
            continue;

        /* A job is done only when every process in its pipeline has exited. */
        bool fin = true;
        for (int p = 0; p < table[i].num_pids; p++) {
            int status;
            if (waitpid(table[i].pids[p], &status, WNOHANG) == 0)
                fin = false;
        }

        if (fin) {
            int last = table[i].num_pids - 1;
            printf("[%d] + %d done %s\n", table[i].num, table[i].pids[last], table[i].cmdline);
            free(table[i].cmdline);
            free(table[i].pids);
            table[i].active = false;
        }
    }
}

void jobs_list(void)
{
    bool found = false;
    for (int i = 0; i < MAX_JOBS; i++) {
        if (table[i].active) {
            int last = table[i].num_pids - 1;
            printf("[%d] + %d running %s\n", table[i].num, table[i].pids[last],
                   table[i].cmdline);
            found = true;
        }
    }
    if (!found)
        printf("no active background jobs\n");
}

void jobs_wait_all(void)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (!table[i].active)
            continue;
        for (int j = 0; j < table[i].num_pids; j++) {  /* wait until every pid finishes */
            int status;
            waitpid(table[i].pids[j], &status, 0);
        }
        free(table[i].cmdline);
        free(table[i].pids);
        table[i].active = false;
    }
}
