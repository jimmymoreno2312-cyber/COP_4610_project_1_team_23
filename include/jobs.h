#ifndef JOBS_H
#define JOBS_H

#include <stdbool.h>
#include <sys/types.h>

#define MAX_JOBS 10

/*
 * Registers a background job made of every pid in a pipeline and prints
 * "[job number] [pid of last command]". Job numbers start at 1 and are never reused.
 */
void jobs_add(const pid_t *pids, int num_pids, const char *cmdline);

/* Non-blocking check. Prints "[job number] + done [cmdline]" for finished jobs. */
void jobs_check(void);

/* Prints "[job number]+ [pid] [cmdline]" for each active job, or a message if none. */
void jobs_list(void);

/* Blocks until every background job has finished (used by exit). */
void jobs_wait_all(void);

#endif
