# 42 Minishell

***by [pda-silv](https://github.com/PBento96) and [joseferr](https://github.com/Drkpulse)***

![Minishell 42](https://github.com/mcombeau/mcombeau/blob/main/42_badges/minishelle.png)

![42](https://img.shields.io/badge/-42-black?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

![GitHub contributors](https://img.shields.io/github/contributors/PBento96/minishell)
![GitHub commit activity](https://img.shields.io/github/commit-activity/t/PBento96/minishell)
![GitHub last commit](https://img.shields.io/github/last-commit/PBento96/minishell)

![GitHub repo size](https://img.shields.io/github/repo-size/PBento96/minishell)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/PBento96/minishell)
![GitHub top language](https://img.shields.io/github/languages/top/PBento96/minishell)

![GitHub Issues or Pull Requests](https://img.shields.io/github/issues-pr-raw/PBento96/minishell)
![GitHub Issues or Pull Requests](https://img.shields.io/github/issues-pr-closed-raw/PBento96/minishell)

![GitHub Issues or Pull Requests](https://img.shields.io/github/issues-raw/PBento96/minishell)
![GitHub Issues or Pull Requests](https://img.shields.io/github/issues-closed-raw/PBento96/minishell)

## About the project

> The existence of shells is linked to the very existence of IT.
>
> At the time, all developers agreed that communicating with a computer using aligned 1/0 switches was seriously irritating.
>
> It was only logical that they came up with the idea of creating a software to communicate with a computer using interactive lines of commands in a language somewhat close to the human language.
>
> Thanks to Minishell, you’ll be able to travel through time and come back to problems people faced when Windows didn’t exist.
>
> -Minishell [Subject](./docs/en.subject.pdf) Introduction

### Project Requirements

This project must:

- Display a **prompt** when waiting for a new command
- Have a working **history**
- Search and launch the right executable (based on the **PATH** variable or using a relative or an absolute path)
- Use at most **one global variable** to indicate a received signal (Must not access main data structures and can only be used to store the SIGNUM)
- Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon)
- Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence
- Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign)
- Implement **redirections**:
  - < should redirect input
  - \> should redirect output
  - << should be given a delimiter, then read the input until a line containing the delimiter is seen (doesn’t have to update the history)
  - \>\> should redirect output in append mode
- Implement **pipes** (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe
- Handle **environment variables** ($ followed by a sequence of characters) which should expand to their values
- Handle $? which should expand to the exit status of the most recently executed foreground pipeline
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash
- In interactive mode:
  - ctrl-C displays a new prompt on a new line
  - ctrl-D exits the shell
  - ctrl-\ does nothing
- Implement the following **builtins**:
  - echo with option -n
  - cd with only a relative or absolute path
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options
- The program must not leak (leaks from the readline function are allowed)

Optionally implement:

- && and || with parenthesis for priorities
- Wildcards * should work for the current working directory
