*This project has been created as part of the 42 curriculum by pnovato-, mlessa-s.*

# minishell

## Description

**minishell** is a comprehensive project developed as a minimalistic shell interpreter, designed to replicate the core functionalities of popular command-line interfaces like Bash. The primary goal of this project is to deepen the understanding of process management, inter-process communication, and system calls in a Unix-like environment.

The interpreter supports a wide array of features essential for a functional shell, including:
*   **Basic Command Execution**: Running external programs and built-in commands.
*   **Environment Variable Handling**: Accessing and modifying environment variables.
*   **Command Chaining**: Executing multiple commands sequentially.
*   **Redirections**: Input (`<`) and output (`>`, `>>`) file redirection.
*   **Pipes**: Inter-process communication using the pipe operator (`|`).
*   **Subshells**: Executing commands in a separate shell environment (if implemented).
*   **Here Documents**: Handling multi-line input redirection (`<<`).

This project serves as a foundational exercise in system programming, requiring meticulous parsing, execution flow control, and error handling.

## Instructions

To compile and run the **minishell** project, follow the steps below in a Unix-like environment (e.g., Linux or macOS).

### Prerequisites

*   A C compiler (e.g., `gcc` or `clang`).
*   The `make` utility.

### Compilation

1.  **Clone the repository:**
    ```bash
    git clone [YOUR_REPOSITORY_URL]
    cd minishell
    ```

2.  **Compile the source code:**
    The project uses a standard `Makefile`. Run the `make` command to compile the executable.
    ```bash
    make
    ```
    This will generate the executable file, typically named `minishell`, in the root directory.

### Execution

1.  **Run the shell:**
    Execute the compiled program:
    ```bash
    ./minishell
    ```

2.  **Interact with the shell:**
    The shell will display a prompt (e.g., `minishell> `) and wait for user input. You can now execute commands, use pipes, and test redirections.

3.  **Exit the shell:**
    Type `exit` or press `Ctrl-D` to terminate the minishell process.

### Cleaning Up

To remove the compiled object files and the executable, use the `fclean` target:
```bash
make fclean
```

## Resources

This section lists classic references related to the topic, as well as a description of how AI was used in the project.

### Classic References

*   **The Linux Programming Interface (TLPI)**: A comprehensive guide to the Linux system programming API, particularly useful for understanding system calls like `fork()`, `execve()`, `pipe()`, and file descriptors.
*   **GNU Bash Manual**: The official documentation for the Bash shell, which serves as the primary reference for expected shell behavior, parsing rules, and built-in commands.
*   **man pages**: The primary source for documentation on system calls and library functions used in C programming (e.g., `man 2 fork`, `man 3 malloc`).

