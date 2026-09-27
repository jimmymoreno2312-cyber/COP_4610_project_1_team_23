# Project 1: Shell

A Unix shell written in C for COP4610 (Operating Systems). It supports environment
variable and tilde expansion, `$PATH` search, external command execution, I/O redirection,
piping, background jobs, and the built-ins `exit`, `cd`, and `jobs`.

## Group Members

- **Pedro De Lana**
- **Jimmy Moreno**
- **Sarah Fieg**

## Division of Labor

<!-- The rubric grades the division "after" the work: update this to reflect who actually
     did what, not just the original plan. -->

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
- **Unlimited number of pipes**: Jimmy
- **Piping and I/O redirection combined**: Jimmy, Sarah
- **Shell-ception**: Pedro

## File Listing

```
.
├── Makefile
├── README.md
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
└── src/
    ├── builtins.c      # Part 9: exit, cd, jobs
    ├── command.c       # parses tokens into a pipeline (pipes, <, >, &)
    ├── execute.c       # Parts 5 & 7: fork/execv and pipelines
    ├── expand.c        # Parts 2 & 3: $VAR and ~ expansion
    ├── jobs.c          # Part 8: background job table
    ├── lexer.c         # reads input and splits it into tokens
    ├── main.c          # read / expand / parse / execute loop
    ├── path_search.c   # Part 4: $PATH search
    ├── prompt.c        # Part 1: prompt
    └── redirect.c      # Part 6: opening redirection files
```

## How to Compile & Execute

### Requirements
- **Compiler**: `gcc`
- **Environment**: linprog (any Linux system with `make` should also work)

### Compilation
```bash
make
```
This builds the executable at `bin/shell`. Use `make clean` to remove build output.

### Execution
```bash
./bin/shell
```
or `make run`.

## Extra Credit

<!-- Extra credit only counts if it is documented here. Describe each one you finish. -->

- **Unlimited pipes**: TODO
- **Piping + I/O redirection**: TODO
- **Shell-ception**: TODO

## Development Log

Each member records their contributions here.

### Pedro De Lana

| Date       | Work Completed / Notes |
|------------|------------------------|
| YYYY-MM-DD | |

### Jimmy Moreno

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-27 | Set up the repository, Makefile, and modular project skeleton. |

### Sarah Fieg

| Date       | Work Completed / Notes |
|------------|------------------------|
| YYYY-MM-DD | |

## Meetings

| Date       | Attendees | Topics Discussed | Outcomes / Decisions |
|------------|-----------|------------------|----------------------|
| YYYY-MM-DD | | | |

## Bugs

- None known yet.
