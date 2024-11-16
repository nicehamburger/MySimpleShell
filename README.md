# My Simple Shell

## Overview

This is a simple Unix shell implemented in C, based on [Brennan's tutorial](https://brennan.io/2015/01/16/write-a-shell-in-c/). It provides a basic interactive command-line interface that can handle built-in commands like `cd`, `help`, and `exit`, as well as external commands using process creation.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Code Structure](#code-structure)
- [Usage](#usage)

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

### Build with make
```bash
make
```

## Code Structure

MySimpleShell/
├── src/
│   └── shell.c                       # Main shell code implementation
├── docs/
│   └── shell_explanation.pdf         # Main shell code implementation
├── Makefile                          # Makefile for building the project
├── README.md                         # This file

## Usage
```bash
./lsh
```
