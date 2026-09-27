/*
 * prompt.c - Part 1: Prompt
 * Owner: Sarah (support: Pedro)
 */
#include "prompt.h"

#include <stdio.h>

void print_prompt(void)
{
    /*
     * TODO(Sarah): print "USER@MACHINE:PWD> " using getenv("USER"),
     * getenv("MACHINE") and getenv("PWD").
     *  - $MACHINE may not be set everywhere; fall back to gethostname().
     *  - Use getcwd() (or keep $PWD updated in cd) so the prompt is right after cd.
     */
    printf("> ");
    fflush(stdout);
}
