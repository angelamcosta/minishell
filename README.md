# Minishell 🐚

<div align=center>

  ![badge](https://raw.githubusercontent.com/angelamcosta/angelamcosta/main/42_badges/minishelle.png)

  [![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)  [![forthebadge](https://forthebadge.com/images/badges/built-by-codebabes.svg)](https://forthebadge.com)
</div>

<div align=center>
  <img alt="GitHub Language Count" src="https://img.shields.io/github/languages/count/angelamcosta/minishell" /> <img alt="GitHub Top Language" src="https://img.shields.io/github/languages/top/angelamcosta/minishell" /> <img alt="GitHub Contributors" src="https://img.shields.io/github/contributors/angelamcosta/minishell" /> <img alt="GitHub Last Commit" src="https://img.shields.io/github/last-commit/angelamcosta/minishell" /> <img alt="Github License" src="https://img.shields.io/github/license/angelamcosta/minishell" />
</div>

Minishell is a shell program written in C that provides a simplified command-line interface for executing commands and managing processes. It aims to replicate basic functionalities of a Unix shell, such as command execution, I/O redirection, piping, and handling of environment variables.

## 📜 Instructions

- Language: C
- Norm: The project must adhere to the Norm, a set of rules and coding conventions.
- Dependencies: The project can use external libraries such as `readline` for line editing capabilities.
- Memory Management: Proper memory allocation and deallocation should be ensured to prevent memory leaks.
- Makefile: A Makefile should be included, providing rules to compile the project with required flags and dependencies.
- Separate Compilation: The Makefile should not relink, and the project should be organized into multiple files if necessary.
- Bonus: Additional features or functions can be implemented as bonuses, but they will be evaluated separately.

## ⚙️ Features

- Prompt: Minishell displays a prompt to indicate it is ready to accept commands.
- History: The shell maintains a history of previously executed commands.
- Command Execution: Minishell searches for and launches the appropriate executable based on the `PATH` variable or using a relative/absolute path.
- Quoting: Minishell handles single quotes (`'`) and double quotes (`"`) to prevent interpretation of metacharacters within the quoted sequence.
- Redirection: The shell supports input (`<`) and output (`>`) redirection, as well as appending output (`>>`) to a file. It also supports here documents (`<<`) with a delimiter.
- Pipes: Minishell implements pipes (`|`) for connecting the output of one command to the input of another.
- Environment Variables: The shell expands environment variables (e.g., `$VAR`) to their corresponding values.
- Special Variables: Minishell expands `$?` to the exit status of the most recently executed foreground pipeline.
- Signal Handling: The shell handles signals such as `ctrl-C`, `ctrl-D`, and `ctrl-\` as expected.
- Built-in Commands: Minishell provides several built-in commands:
  - `echo -n`: Prints arguments to the standard output without a trailing newline.
  - `cd`: Changes the current working directory to the specified path.
  - `pwd`: Prints the current working directory.
  - `export`: Sets or exports environment variables.
  - `unset`: Unsets environment variables.
  - `env`: Prints the environment variables.
  - `exit`: Exits the shell.

## 📂 Project Structure

The Minishell repository consists of the following files:

- `Makefile`: Makefile for compiling the project.
- `*.h`: Header files containing function prototypes and necessary definitions.
- `*.c`: Source code files containing the implementation of various features and built-in commands.

## 🚀 Usage

To compile the Minishell project, run the following command:

```
make
```

This will generate an executable named `minishell`.

To launch the shell, run the following command:

```
./minishell
```

Once the shell is running, you can enter commands and utilize the supported features.
