# Mini Shell in C

A simple Unix shell written in C as part of my systems programming journey.

This project is being built from scratch while learning C through *The C Programming Language* (Kernighan & Ritchie). The goal is not just to make a working shell, but to understand how operating systems execute programs, manage processes, and interact with the filesystem.

---

## Features

### Built-in Commands
- `echo`
- `type`
- `exit`

### External Commands
- Search executables using the `PATH` environment variable
- Execute programs using `fork()` and `execv()`
- Wait for child processes using `waitpid()`

---

## Concepts Learned

This project helped me understand:

- String tokenization using `strtok()`
- Parsing command-line arguments (`argv`)
- Environment variables (`getenv`)
- Searching the `PATH`
- Executable permissions using `access()`
- Process creation using `fork()`
- Program execution using `execv()`
- Parent-child synchronization using `waitpid()`

---

## Technologies

- C
- GCC
- Linux / WSL
- POSIX System Calls

---

## Building

Compile the project:

```bash
gcc main.c -o shell
```

Run:

```bash
./shell
```

---

## Current Status

- [x] Command parsing
- [x] Built-in commands
- [x] PATH lookup
- [x] External command execution
- [x] Process creation (`fork`)
- [x] Program execution (`execv`)
- [x] Parent waits for child

---

## Roadmap

- [ ] Input/Output Redirection (`>`, `<`)
- [ ] Pipes (`|`)
- [ ] Background Processes (`&`)
- [ ] Command History
- [ ] Signal Handling
- [ ] Environment Variable Expansion
- [ ] Job Control

---

## Why I'm Building This

I'm currently learning systems programming and low-level software development.

This shell is one of several projects I'm building to understand how Unix systems work internally before moving on to larger projects like:

- HTTP Server in C
- Memory Allocator
- Mini Operating System
- Networking Projects
- Embedded Systems Development

---

## References

- *The C Programming Language* — Brian W. Kernighan & Dennis M. Ritchie
- POSIX Manual Pages
- CodeCrafters Shell Challenge

---

**Author:** Akshat Singh
