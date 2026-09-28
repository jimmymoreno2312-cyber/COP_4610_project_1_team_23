/*
 * main.c - the shell's read / expand / parse / execute loop.
 */
#include <stdlib.h>

#include "builtins.h"
#include "command.h"
#include "execute.h"
#include "expand.h"
#include "jobs.h"
#include "lexer.h"
#include "prompt.h"

int main(void)
{
    while (1) {
        jobs_check();
        print_prompt();

        char *input = get_input();
        if (input == NULL)  /* EOF (Ctrl-D) behaves like exit */
            builtin_exit();

        tokenlist *tokens = get_tokens(input);
        if (tokens != NULL && tokens->size > 0) {
            expand_tokens(tokens);

            /* A line of only unset variables expands to nothing. */
            pipeline *p = tokens->size > 0 ? parse_pipeline(tokens, input) : NULL;
            if (p != NULL) {
                int status = is_builtin(p) ? run_builtin(p) : run_pipeline(p);
                if (status == 0)
                    history_add(input);
                free_pipeline(p);
            }
        }

        free_tokens(tokens);
        free(input);
    }
}
