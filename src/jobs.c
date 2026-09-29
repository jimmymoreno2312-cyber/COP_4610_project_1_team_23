/* jobs.c - Part 8: Background Processing */
#include "jobs.h"

#include <stdio.h>

void jobs_add(const pid_t *pids, int num_pids, const char *cmdline)
{
    (void)pids;
    (void)num_pids;
    (void)cmdline;
}

void jobs_check(void)
{
}

void jobs_list(void)
{
    printf("no active background jobs\n");
}

void jobs_wait_all(void)
{
}
