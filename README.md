# 🖥️ Command Line Interpreter Project

## 📘 Introduction

This project implements a relatively simple **Command Line Interpreter
(CLI)** --- a miniature version of the kind found in real operating
systems.
Although simplified, it supports many of the same fundamental concepts
and features.

The interpreter reads and executes commands one by one, either:
entered **interactively** by the user, or provided as a **batch file** stored in a text file.

It also supports **redirection** and **pipes**, just like in real
operating systems.

------------------------------------------------------------------------

## ⚙️ Functional Requirements

### 🧠 Basic Behavior

The command-line interpreter runs as an **interactive console
program**.
The user types commands, and the program prints output to the screen.

The interpreter works in a cycle:

1.  Prints a command prompt (default `$`, but it can be changed).

2.  Waits for the user to enter a command:

    ``` bash
    command [-opt] [argument]
    ```

3.  Executes the command and prints the result.

4.  Displays the prompt again for the next command.

Example:

``` bash
$ wc -w "Lorem ipsum dolor sit amet, consectetur adipiscing elit"
8
```

------------------------------------------------------------------------

### ✍️ Lexical Rules

-   Each command line can contain **up to 512 characters** (excluding
    newline).
-   **Uppercase and lowercase** letters are distinct.
-   Parts of the command are separated by **spaces or tabs**.
-   **Quoted text** (`" "`) is treated as a single argument, even if it
    contains spaces.
-   The symbols `|`, `<`, and `>` have **special meanings** (pipe and
    redirection), unless inside quotes.
-   If invalid characters or syntax appear, the interpreter prints an
    error message showing where the issue occurred.

------------------------------------------------------------------------

## 📥 Command Input and Output Streams

Most commands use an **input/output character stream**.
Input can come from several sources:

1.  **Keyboard (default)**

    ``` bash
    $ wc -w
    Lorem ipsum dolor sit amet
    # → 5
    ```

2.  **Quoted argument**

    ``` bash
    $ wc -w "Lorem ipsum dolor sit amet"
    # → 5
    ```

3.  **File input**

    ``` bash
    $ wc -w input.txt
    # → 5
    ```

4.  **Input redirection**

    ``` bash
    $ wc -w <input.txt
    # → 5
    ```

Output can be redirected as well:

-   **Default:** printed to the screen.

-   **To file:**

    ``` bash
    $ wc -w "Lorem ipsum" >output.txt
    ```

    -   `>` creates or overwrites the file\
    -   `>>` appends to the file

------------------------------------------------------------------------

## 🧩 Supported Commands

  ---------------------------------------------------------------------------
  Command                Format                  Description
  ---------------------- ----------------------- ----------------------------
  **echo**               `echo [argument]`       Prints input text unchanged

  **prompt**             `prompt "newPrompt"`    Changes the CLI prompt
                                                 symbol

  **time**               `time`                  Prints current system time

  **date**               `date`                  Prints current system date

  **touch**              `touch filename`        Creates an empty file
                                                 (errors if it exists)

  **truncate**           `truncate filename`     Clears file contents

  **rm**                 `rm filename`           Deletes a file

  **wc**                 `wc -opt [argument]`    Counts words (`-w`) or
                                                 characters (`-c`)

  **tr**                 `tr "what" "with"`      Replaces text (`what` →
                                                 `with`) or removes it

  **head**               `head -nN [argument]`   Prints the first N lines of
                                                 text

  **batch**              `batch [argument]`      Executes a series of
                                                 commands from input (batch
                                                 mode)
  ---------------------------------------------------------------------------

------------------------------------------------------------------------

## 🔗 Pipes

You can connect multiple commands using **pipes (`|`)**.
The output of one command becomes the input of the next.

Example:

``` bash
time | tr ":" "." | wc -c >time.txt
```

Explanation: - `time` prints the current time
- `tr` replaces `:` with `.`
- `wc` counts the characters and writes the result to `time.txt`

Commands connected by pipes cannot redefine the same input/output (e.g.,
via redirection or arguments).

------------------------------------------------------------------------

## 🧠 Summary

✅ Written in **C++**
✅ Supports **interactive and batch modes**
✅ Handles **redirection and piping**
✅ Includes essential **shell-like commands** (`echo`, `wc`, `tr`,
etc.)
✅ Easy to extend with new commands in the future

------------------------------------------------------------------------

### 🧑‍💻 Author

**Mihailo Mitrović**
✉️mihailo3332@gmail.com
