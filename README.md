# Project 1: Shell

A Unix shell written in C for COP4610 (Operating Systems). It supports environment
variable and tilde expansion, `$PATH` search, external command execution, I/O redirection,
piping, background jobs, and the built-ins `exit`, `cd`, and `jobs`.

## Group Members
- **Pedro De Lana**: pd23b@fsu.edu
- **Jimmy Moreno**: jam23ba@fsu.edu
- **Sarah Fieg**: sef21a@fsu.edu

## Division of Labor

### Part 1: Prompt
- **Responsibilities**: Print `USER@MACHINE:PWD>` before each command.
- **Assigned to**: Sarah, Pedro

### Part 2: Environment Variables
- **Responsibilities**: Expand tokens beginning with `$` to their values.
- **Assigned to**: Jimmy, Sarah

### Part 3: Tilde Expansion
- **Responsibilities**: Expand `~` and `~/...` to `$HOME`.
- **Assigned to**: Pedro, Jimmy

### Part 4: $PATH Search
- **Responsibilities**: Find executables by searching each directory in `$PATH`.
- **Assigned to**: Sarah, Jimmy

### Part 5: External Command Execution
- **Responsibilities**: Run external commands with `fork()` and `execv()`.
- **Assigned to**: Jimmy, Pedro

### Part 6: I/O Redirection
- **Responsibilities**: Support `<` and `>` (output files created with `-rw-------`).
- **Assigned to**: Jimmy, Sarah

### Part 7: Piping
- **Responsibilities**: Connect commands with `|`.
- **Assigned to**: Jimmy, Pedro

### Part 8: Background Processing
- **Responsibilities**: Run commands with `&`, track jobs, and report when they finish.
- **Assigned to**: Pedro, Jimmy

### Part 9: Internal Command Execution
- **Responsibilities**: Implement `exit`, `cd`, and `jobs`.
- **Assigned to**: Sarah, Pedro

### Extra Credit
- **Responsibilities**: Unlimited number of pipes; piping and I/O redirection combined;
  shell-ception (running the shell inside itself).
- **Assigned to**: Jimmy (all three), with Pedro testing shell-ception

### Integration & Testing
- **Responsibilities**: Combine the parts, test against the sample runs, fix issues found
  in testing, and keep the README up to date.
- **Assigned to**: Pedro, with Jimmy and Sarah

## File Listing
```
root/
├── bin/                # executable (bin/shell) is built here
├── obj/                # object files are built here
├── include/
│   ├── builtins.h
│   ├── command.h
│   ├── execute.h
│   ├── expand.h
│   ├── jobs.h
│   ├── lexer.h
│   ├── path_search.h
│   ├── prompt.h
│   └── redirect.h
├── src/
│   ├── builtins.c      # Part 9: exit, cd, jobs
│   ├── command.c       # parses tokens into a pipeline (pipes, <, >, &)
│   ├── execute.c       # Parts 5 & 7: fork/execv and pipelines
│   ├── expand.c        # Parts 2 & 3: $VAR and ~ expansion
│   ├── jobs.c          # Part 8: background job table
│   ├── lexer.c         # reads input and splits it into tokens
│   ├── main.c          # read / expand / parse / execute loop
│   ├── path_search.c   # Part 4: $PATH search
│   ├── prompt.c        # Part 1: prompt
│   └── redirect.c      # Part 6: opening redirection files
├── README.md
└── Makefile
```

## How to Compile & Execute

### Requirements
- **Compiler**: `gcc` (C99)
- **Environment**: linprog (any Linux system with `make` should also work)

### Compilation
```bash
make
```
This will build the executable in `bin/shell`, with object files in `obj/`.
`make clean` removes the build output.

### Execution
```bash
make run
```
This will run the shell. It can also be started directly with `./bin/shell`.

## Development Log
Each member records their contributions here.

### Pedro De Lana

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-28 | Worked with Jimmy on `exec_command()`, `close_pipes()`, and `run_child()` (Parts 5 & 7). |
| 2026-09-28 | Cleaned up source comments; restructured README to the course template. |
| 2026-09-28 | Implemented the background job table in `jobs.c` (Part 8). |
| 2026-09-28 | Hooked background jobs into `run_pipeline()`: `&`-free job names, flush before fork. |
| 2026-09-28 | Implemented tilde expansion (Part 3), `cd`, and `exit` history (Part 9). |
| 2026-09-28 | Matched prompt and job output formats to the sample runs. |
| 2026-09-28 | Tested all parts and extra credit; fixed issues found in testing; formatting. |

### Jimmy Moreno

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-27 | Set up the repository, Makefile, and modular project skeleton. |
| 2026-09-28 | Implemented environment variable expansion (Part 2). |
| 2026-09-28 | Implemented I/O redirection file handling (Part 6). |
| 2026-09-28 | Implemented run_pipeline: piping with up to two pipes (Part 7). |
| 2026-09-28 | Extra credit 1: unlimited pipes (dynamic arrays in `run_pipeline()` and `jobs.c`). |
| 2026-09-28 | Extra credit 2: piping combined with I/O redirection. |

### Sarah Fieg

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-27 | Completed `prompt.c` and `path_search.c` (Parts 1 & 4). |

## Meetings
Document in-person meetings, their purpose, and what was discussed.

| Date       | Attendees | Topics Discussed | Outcomes / Decisions |
|------------|-----------|------------------|----------------------|
| 2026-09-20 | Pedro, Jimmy, Sarah | Sunday 5 PM: project requirements and part assignments | Each part given a lead and a support member (see Division of Labor) |
| 2026-09-27 | Pedro, Jimmy, Sarah | Sunday 5 PM: progress on each part; setting up GitHub | Created the shared repository; rebalanced work so every part had support |

## Bugs
- None known. All base features were tested locally (macOS); final testing is on linprog.

## Extra Credit
- **Extra Credit 1: Unlimited number of pipes** (Jimmy): `run_pipeline()` in `src/execute.c`
  sizes its pipe, PID, and path arrays from the number of commands, so a pipeline can have any
  number of pipes, e.g. `cat in.txt | sort | uniq | sort -r | head -2 | wc -l`. The background
  job table in `src/jobs.c` also stores each job's PIDs in a dynamic array, so long pipelines
  work with `&` too.
- **Extra Credit 2: Piping and I/O redirection combined** (Jimmy): `<` gives its file to the
  first command and `>` sends the last command's output to its file, e.g.
  `sort < in.txt | uniq -c | sort -rn > out.txt`. `run_child()` in `src/execute.c` keeps the
  files open only in the first and last commands. The parser in `src/command.c` rejects `<`
  after the first command and `>` before the last.
- **Extra Credit 3: Shell-ception** (Jimmy, tested by Pedro): the shell can run itself, e.g. `./bin/shell` from
  inside `bin/shell`, repeatedly. The nested shell is started like any external command
  (the name contains `/`, so it is run directly with `fork()`/`execv()`), and the parent waits
  on it with `waitpid()`. Typing `exit` in the inner shell returns to the outer one.

## Considerations
- Output formats follow the posted sample runs: background start `[1] 12345`, completion
  `[1] + 12345 done sleep 3`, and `jobs` lines `[1] + 12345 running sleep 3`. Finished jobs
  are reported after the next command is entered, before it runs.
- Job listings show the command line without the trailing `&`.
- `exit` waits for background jobs, then prints the last three valid commands (oldest first),
  only the last one if there were fewer than three, or `No valid commands.`
- A "valid command" is one that started successfully: unknown commands, bad redirection
  files, and failed `cd` calls are not recorded.
- Any number of pipes is accepted (extra credit 1), and pipes can be combined with `<` and `>`
  (extra credit 2). In a pipeline, `<` must be on the first command and `>` on the last.
- An unset variable (e.g. `echo $NOPE`) expands to nothing and its token is dropped, as in bash.
- If `$MACHINE` is not set, the prompt falls back to `gethostname()`.
- Output files from `>` are always left with permissions `-rw-------`, even if they already
  existed.

### Use of AI
- **Pedro De Lana**: Used Claude Code as a learning aid to understand C and system calls
  (`fork`, `execv`, `dup2`, `waitpid`) more proficiently, and to partially assist in writing
  code (tilde expansion, `cd`, `exit` history, and the background job table). Worked together
  with Jimmy on `exec_command()`, `close_pipes()`, and `run_child()` in `execute.c`. It was
  also used to clean up source comments and format this README. All generated code was
  reviewed and understood before committing.
- **Jimmy Moreno**: Used Claude Code to generate the project skeleton (Makefile, lexer, parser,
  and module stubs), environment variable expansion, I/O redirection, `run_pipeline()`, and
  extra credits 1 and 2 (unlimited pipes; piping with I/O redirection). Worked together with
  Pedro on `exec_command()`, `close_pipes()`, and `run_child()` in `execute.c`. All generated
  code was reviewed and tested before committing.
- **Sarah Fieg**: Used ChatGPT to aid in understanding C and to help write the `$PATH` search
  in `path_search.c` (splitting `$PATH` on `:` and checking each directory with `access()`).
  All generated code was reviewed and understood before committing.
