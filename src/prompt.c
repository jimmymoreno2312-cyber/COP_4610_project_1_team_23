/* prompt.c - Part 1: Prompt */
#include "prompt.h"

#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>

void print_prompt(void)
{
     const char *user =getenv("USER"); 
     const char *machine =getenv("MACHINE"); 
     char host[256] = "unknown"; 
     char cwd[4096]; 

     //User fallback 
     if(!user)
        user = "unknown"; 
     //Machine fallback to gethostname()
     if(!machine) 
     {
        gethostname(host, sizeof host - 1); 
        machine = host; 
     }  
     
     // getcwd() instead of $PWD so the prompt is right after cd
        if(!getcwd(cwd, sizeof cwd))
        {
            snprintf(cwd, sizeof cwd, "?"); 
        }

    printf("%s@%s:%s> ", user, machine, cwd);
    fflush(stdout);
}
