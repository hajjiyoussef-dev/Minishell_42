# Minishell

Minishell is a simplified shell developed as part of the 42 Network curriculum. It replicates essential behaviors of a Unix shell (like `bash`), handling parsing, command execution, pipes, redirections, built-in commands, signal management, and more.

## 🧠 Project Summary

Over the span of a month, this project required building a shell from scratch in C, mastering process control, terminal behavior, memory management, and more. We recreated core shell functionalities while adhering to strict standards for memory leaks, signal handling, and correct Bash-like behavior.

---

## 🛠️ Features Implemented

### ✨ Core Features

- **Command Parsing**
  - Tokenization with handling of whitespace, quotes, escapes
  - Splitting input into structured command blocks
- **Execution Engine**
  - Handling of pipes (`|`) with correct input/output linking
  - Redirections: `<`, `>`, `>>`, `<<` (heredoc)
  - Builtin and external command execution
- **Built-in Commands**
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Environment Management**
  - Environment stored in a linked list (`t_copy`)
  - Support for `$VAR` expansion and special vars like `$?`

### 🛡️ Signal Handling

- Parent handles `SIGINT` (`Ctrl+C`) without exiting shell
- Child processes receive correct signal behavior
- Heredoc mode with custom signal blocking and interruption

### 🗓️ Redirection & Pipes

- Full support for multi-pipe commands (`ls | grep txt | wc`)
- Redirections before, after, and in-between pipes
- Temporary file handling for heredoc with correct clean-up

---

## 🔹 Bonus: Wildcard Expansion

We implemented **wildcard pattern matching**, enabling support for commands like:

```bash
echo *.c
```

### Implementation Details:

- Used `opendir()` and `readdir()` to read current directory entries
- Used pattern matching function (`match_string`) to match `*.c`, `*test*`, etc.
- Expanded matching files into arguments during parsing
- Sorted output for consistency
- Excluded hidden files (`.file`) unless pattern starts with dot

### Example:

```bash
minishell> echo *.c
lexer.c parser.c utils.c
```

---

## 🔧 Memory & FD Management

- All dynamic memory tracked via custom garbage collector (`gc_malloc`, `gc_free`)
- Signals handled safely during critical sections
- Verified with Valgrind:
  - No leaks
  - No FD leaks with `--track-fds=yes`

---

## 📁 Directory Structure

```
minishell/
│   ├── parsing/
│   ├── execution/
│   ├── builtins/
│   └── utils/
├── includes/
├── Makefile
└── minishell.c
```

---

## 📈 What I Learned

- Shell architecture and job control
- Bitwise operations (`st_mode & 0170000`) and file types with `stat()`
- System calls: `fork`, `execve`, `pipe`, `dup2`, `open`, `close`
- Directory scanning with `DIR *`, `struct dirent *`
- Writing a recursive, memory-safe parser with custom tokenizer
- Emulating Bash behavior closely with edge case handling

---

## 🌟 Final Notes

This project was an incredible journey through the internals of Unix systems. It sharpened our skills in low-level programming, process control, and debugging complex interactions in a multi-process environment. 

## CREATE BY
yhajji && harmi

