/*
 * jobs.c - Part 8: Background Processing
 * Owner: Pedro (support: Jimmy)
 */
#include "jobs.h"

#include <stdio.h>

/*
 * TODO(Pedro): keep a static table of up to MAX_JOBS active jobs, e.g.
 *   struct job { int number; pid_t pids[...]; int num_pids; char *cmdline; bool active; };
 * plus a static next_job_number starting at 1.
 */

void jobs_add(const pid_t *pids, int num_pids, const char *cmdline)
{
    /* TODO(Pedro): store the job and print "[number] [pids[num_pids - 1]]". */
    (void)pids;
    (void)num_pids;
    (void)cmdline;
}

void jobs_check(void)
{
    /*
     * TODO(Pedro): waitpid(pid, &status, WNOHANG) on each job's pids.
     * When all of a job's pids have finished, print "[number] + done cmdline"
     * and free its slot.
     */
}

void jobs_list(void)
{
    /* TODO(Pedro/Sarah): "[number]+ [pid] [cmdline]" per active job, or "no active jobs". */
    printf("no active background jobs\n");
}

void jobs_wait_all(void)
{
    /* TODO(Pedro): blocking waitpid() on every remaining pid. */
}
