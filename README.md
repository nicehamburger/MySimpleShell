# Basic C Shell

## Overview

This is a simple Unix shell implemented in C, based on [Brennan's tutorial](https://brennan.io/2015/01/16/write-a-shell-in-c/). 
It provides a basic interactive command-line interface that can handle built-in commands like `cd`, `help`, and `exit`, as well as external commands using process creation.

## Table of Contents

- [Project Structure](#code-structure)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)

## Project Structure
```
MySimpleShell/
├── docs/
│   └── shell_explanation.pdf         # Main shell code explanation
├── src/
│   └── shell.c                       # Main shell code implementation
├── Makefile                          # Makefile for building the project
├── README.md                         # This file
```

## Features

- Execute built-in commands (`cd`, `help`, `exit`)
- Launch external programs using `fork()` and `execvp()`
- Supports basic command parsing and argument handling
- Error handling for command execution and memory allocation

## Installation

### Prerequisites

- C compiler (e.g., `gcc`)
- Unix-based OS (Linux, macOS, or WSL on Windows)

### Clone the Repository

```bash
git clone https://github.com/nicehamburger/MySimpleShell
cd MySimpleShell
```

### Build the project using make
```bash
make
```

## Usage
```bash
./lsh
```
You will be presented with a prompt (> ) where you can enter commands.

### Commands
Change the current directory
```
cd [directory]
```
Display the help menu, listing available commands
```
help
```
Exit the shell
```
exit
```
Any other command will be treated as an external command (if it exists).<br>
