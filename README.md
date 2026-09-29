# Project 1: Shell

A Unix shell written in C for COP4610 (Operating Systems). It supports environment
variable and tilde expansion, `$PATH` search, external command execution, I/O redirection,
piping, background jobs, and the built-ins `exit`, `cd`, and `jobs`.

## Group Members
- **Pedro De Lana**: [school email]
- **Jimmy Moreno**: [school email]
- **Sarah Fieg**: [school email]

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
- **Assigned to**: Pedro, Jimmy

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
- **Assigned to**: Jimmy (unlimited pipes), Jimmy and Sarah (piping + redirection),
  Pedro (shell-ception)

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
| 2026-09-28 | Added pipe helpers `close_pipes()` and `run_child()` to `execute.c` (Parts 5 & 7). |
| 2026-09-28 | Implemented `exec_command()` with `execv()` (Part 5). |
| 2026-09-28 | Cleaned up source comments; restructured README to the course template. |

### Jimmy Moreno

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-27 | Set up the repository, Makefile, and modular project skeleton. |
| 2026-09-28 | Implemented environment variable expansion (Part 2). |
| 2026-09-28 | Implemented I/O redirection file handling (Part 6). |
| 2026-09-28 | Implemented run_pipeline: piping with up to two pipes (Part 7). |

### Sarah Fieg

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-27 | Completed `prompt.c` and `path_search.c` (Parts 1 & 4). |

## Meetings
Document in-person meetings, their purpose, and what was discussed.

| Date       | Attendees | Topics Discussed | Outcomes / Decisions |
|------------|-----------|------------------|----------------------|
| YYYY-MM-DD | [Names]   | [Agenda items]   | [Actions/Next steps] |

## Bugs
- None known yet.

Unfinished portions (as of 2026-09-28):
- `run_pipeline()` (Parts 5 & 7): prints "external commands not implemented yet".
- `expand_tilde()` (Part 3): returns the token unchanged.
- `cd`, command history, and `exit`'s last-three-commands output (Part 9).
- Background job table in `jobs.c` (Part 8).

## Extra Credit
- **Extra Credit 1:**: Unlimited number of pipes (not finished yet)
- **Extra Credit 2:**: Piping and I/O redirection combined (not finished yet)
- **Extra Credit 3:**: Shell-ception (not finished yet)

## Considerations
- An unset variable (e.g. `echo $NOPE`) expands to nothing and its token is dropped, as in bash.
- If `$MACHINE` is not set, the prompt falls back to `gethostname()`.
- Output files from `>` are always left with permissions `-rw-------`, even if they already
  existed.

### Use of AI
- **Pedro De Lana**: Used Claude Code to add `exec_command()` and the pipe helpers to
  `execute.c`, clean up source comments, and format this README. All generated code was
  reviewed and understood before committing.
