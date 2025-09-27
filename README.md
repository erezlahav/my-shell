# my_shell

[![Language: C](https://img.shields.io/badge/language-C-blue.svg)](https://www.gnu.org/software/gcc/)  
[![License](https://img.shields.io/badge/license-Educational-lightgrey.svg)](LICENSE)

**my_shell** is a custom command-line shell written in C, supporting **internal and external commands**, **pipes**, and **I/O redirection**, while showcasing low-level process and memory management.

---

# Features

- **Internal Commands:** `cd`, `ls`, `pwd`, `whoami`, `exit`  
- **External Commands:** Executes any binary in `PATH`  
- **Pipes (`|`)**: Combine multiple commands  
- **I/O Redirection:**  
  - Output: `>`  
  - Input: `<`  
- **Memory Management:** Dynamic allocation and proper freeing of arguments  
- **Process Management:** Forking with `execve()` and waiting with `waitpid()`

---

## Folder Structure

```text
my_shell/
├── src/
│   ├── main.c
│   ├── parser.c
│   ├── utils.c
│   ├── pipe.c
│   ├── redirection.c
│   └── commands.c
├── headers/
│   ├── parser.h
│   ├── utils.h
│   ├── pipe.h
│   ├── redirection.h
│   └── commands.h
├── makefile
└── README.md
