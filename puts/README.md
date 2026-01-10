# Output Functions Module

Functions for writing data to file descriptors (stdout, stderr, or files).

## 📋 Overview

This module provides fundamental output functions that write various data types to file descriptors. These functions are building blocks for console applications, logging systems, and any program that needs to produce text output.

## 🎯 Functions

### `ft_putchar_fd`
```c
void ft_putchar_fd(char c, int fd);
```
**Description**: Writes a single character to the specified file descriptor.

**Parameters**:
- `c`: Character to write
- `fd`: File descriptor (0=stdin, 1=stdout, 2=stderr)

---

### `ft_putstr_fd`
```c
void ft_putstr_fd(char *s, int fd);
```
**Description**: Writes a string to the specified file descriptor.

**Parameters**:
- `s`: Null-terminated string to write
- `fd`: File descriptor

---

### `ft_putendl_fd`
```c
void ft_putendl_fd(char *s, int fd);
```
**Description**: Writes a string followed by a newline to the specified file descriptor.

**Parameters**:
- `s`: Null-terminated string to write
- `fd`: File descriptor

---

### `ft_putnbr_fd`
```c
void ft_putnbr_fd(int n, int fd);
```
**Description**: Writes an integer to the specified file descriptor.

**Parameters**:
- `n`: Integer to write
- `fd`: File descriptor

## 🧠 Programming Concepts

### File Descriptors
File descriptors are integers that represent open files or I/O streams:

```c
0 - STDIN_FILENO   // Standard Input
1 - STDOUT_FILENO  // Standard Output
2 - STDERR_FILENO  // Standard Error
```

### The `write` System Call
All these functions use the low-level `write()` system call:
```c
ssize_t write(int fd, const void *buf, size_t count);
```

**Why write() instead of printf()?**
- Direct system call - no formatting overhead
- Works with any file descriptor
- More control over output
- Required for 42 projects (printf not allowed in early projects)

### Recursive Number Printing
`ft_putnbr_fd` uses recursion to print numbers:
```c
void ft_putnbr_fd(int n, int fd)
{
    if (n == -2147483648)
        ft_putstr_fd("-2147483648", fd);
    else if (n < 0)
    {
        ft_putchar_fd('-', fd);
        ft_putnbr_fd(-n, fd);
    }
    else if (n >= 10)
    {
        ft_putnbr_fd(n / 10, fd);      // Print all but last digit
        ft_putchar_fd(n % 10 + '0', fd); // Print last digit
    }
    else
        ft_putchar_fd(n + '0', fd);
}
```

### Output Redirection
File descriptors enable output redirection:
```bash
# Redirect stdout to file
./program > output.txt

# Redirect stderr to file
./program 2> errors.txt

# Redirect both
./program > output.txt 2> errors.txt

# Redirect stderr to stdout
./program 2>&1
```

## 💡 Usage Examples

### Basic Output
```c
#include "puts.h"

int main(void)
{
    // Print to standard output
    ft_putstr_fd("Hello, World", 1);
    ft_putchar_fd('!', 1);
    ft_putchar_fd('\n', 1);
    
    // Simpler version with endline
    ft_putendl_fd("Hello, World!", 1);
    
    // Print numbers
    ft_putnbr_fd(42, 1);
    ft_putchar_fd('\n', 1);
    
    return (0);
}
```

### Error Handling
```c
// Separate normal output from errors
void process_file(char *filename)
{
    int fd = open(filename, O_RDONLY);
    
    if (fd < 0)
    {
        ft_putstr_fd("Error: Cannot open file '", 2);
        ft_putstr_fd(filename, 2);
        ft_putendl_fd("'", 2);
        return;
    }
    
    ft_putstr_fd("Successfully opened: ", 1);
    ft_putendl_fd(filename, 1);
    
    // ... process file ...
    close(fd);
}
```

### Logging System
```c
typedef enum e_log_level
{
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} t_log_level;

void log_message(t_log_level level, char *message)
{
    if (level == LOG_INFO)
    {
        ft_putstr_fd("[INFO] ", 1);
        ft_putendl_fd(message, 1);
    }
    else if (level == LOG_WARNING)
    {
        ft_putstr_fd("[WARNING] ", 2);
        ft_putendl_fd(message, 2);
    }
    else if (level == LOG_ERROR)
    {
        ft_putstr_fd("[ERROR] ", 2);
        ft_putendl_fd(message, 2);
    }
}

// Usage
log_message(LOG_INFO, "Application started");
log_message(LOG_ERROR, "Connection failed");
```

### Writing to Files
```c
#include <fcntl.h>

void write_to_file(char *filename, char *content)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd < 0)
    {
        ft_putendl_fd("Error: Cannot create file", 2);
        return;
    }
    
    ft_putendl_fd(content, fd);
    close(fd);
    
    ft_putstr_fd("Written to ", 1);
    ft_putendl_fd(filename, 1);
}

// Usage
write_to_file("output.txt", "Hello, File!");
```

### Formatting Complex Output
```c
void print_stats(char *name, int score, int rank)
{
    ft_putstr_fd("Player: ", 1);
    ft_putendl_fd(name, 1);
    
    ft_putstr_fd("Score: ", 1);
    ft_putnbr_fd(score, 1);
    ft_putchar_fd('\n', 1);
    
    ft_putstr_fd("Rank: #", 1);
    ft_putnbr_fd(rank, 1);
    ft_putchar_fd('\n', 1);
}

// Usage
print_stats("Alice", 9500, 1);
// Output:
// Player: Alice
// Score: 9500
// Rank: #1
```

### Progress Indicator
```c
void show_progress(int current, int total)
{
    ft_putstr_fd("\rProcessing: ", 1);
    ft_putnbr_fd(current, 1);
    ft_putchar_fd('/', 1);
    ft_putnbr_fd(total, 1);
    
    // Calculate percentage
    int percent = (current * 100) / total;
    ft_putstr_fd(" (", 1);
    ft_putnbr_fd(percent, 1);
    ft_putstr_fd("%)", 1);
}

// Usage in loop
for (int i = 1; i <= 100; i++)
{
    // ... do work ...
    show_progress(i, 100);
    usleep(50000);  // Simulate work
}
ft_putchar_fd('\n', 1);
```

## 🔍 Common Use Cases

### Command-Line Tools
- Printing help messages
- Showing command output
- Reporting errors

### Debugging
- Printing variable values
- Tracing program execution
- Logging debug information

### Data Export
- Writing results to files
- Creating reports
- Generating logs

### User Interaction
- Prompting for input
- Displaying menus
- Showing progress

## 🎓 Key Learnings

1. **File descriptors**: Understanding Unix I/O model
2. **System calls**: Direct interaction with kernel via `write()`
3. **Output streams**: Separating normal output from errors
4. **Recursion**: Elegant solution for number printing
5. **Buffering**: Understanding buffered vs unbuffered I/O
6. **Error handling**: Proper use of stderr for errors

## 📊 Performance

| Function | Time Complexity | Notes |
|----------|----------------|-------|
| `ft_putchar_fd` | O(1) | Single character write |
| `ft_putstr_fd` | O(n) | n = string length |
| `ft_putendl_fd` | O(n) | n = string length + newline |
| `ft_putnbr_fd` | O(log n) | n = number magnitude |

## ⚠️ Important Considerations

### Buffering
```c
// write() is unbuffered - output appears immediately
ft_putstr_fd("Hello", 1);  // Appears right away

// printf() is buffered - may not appear until flush
printf("Hello");  // Might not appear until \n or fflush()
```

### Error Checking
```c
// Basic functions don't check write() return value
// For production code, you might want to check:
ssize_t bytes_written = write(fd, "text", 4);
if (bytes_written < 0)
    perror("write failed");
```

### File Descriptor Validity
```c
// Always ensure file descriptor is valid
int fd = open("file.txt", O_WRONLY);
if (fd >= 0)
{
    ft_putendl_fd("Success", fd);
    close(fd);
}
else
    ft_putendl_fd("Error opening file", 2);
```

### INT_MIN Special Case
```c
// -2147483648 cannot be made positive
// Special handling required in ft_putnbr_fd
if (n == -2147483648)
    ft_putstr_fd("-2147483648", fd);
```

## 🔗 Related Functions

From other modules:
- `ft_itoa()` - Convert integer to string (allocates memory)
- `ft_strlen()` - Used internally to measure string length
- `ft_printf()` - More advanced formatted output

Standard library:
- `write()` - System call used internally
- `printf()` - Formatted output (more features)
- `puts()` - String output with newline

## 📚 Standard Library Equivalents

Similar functionality to:
- `putchar()` - but with file descriptor parameter
- `fputs()` - but simpler interface
- `fprintf()` - but without formatting

## 🔬 Advanced Usage

### Custom Output Stream
```c
typedef struct s_output
{
    int fd;
    char *prefix;
} t_output;

void print_prefixed(t_output *out, char *message)
{
    if (out->prefix)
        ft_putstr_fd(out->prefix, out->fd);
    ft_putendl_fd(message, out->fd);
}

// Usage
t_output logger = {1, "[LOG] "};
print_prefixed(&logger, "Application started");
// Output: [LOG] Application started
```

### Colored Output (ANSI Codes)
```c
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

void print_error(char *message)
{
    ft_putstr_fd(COLOR_RED, 2);
    ft_putstr_fd("ERROR: ", 2);
    ft_putstr_fd(message, 2);
    ft_putstr_fd(COLOR_RESET, 2);
    ft_putchar_fd('\n', 2);
}

void print_success(char *message)
{
    ft_putstr_fd(COLOR_GREEN, 1);
    ft_putstr_fd("SUCCESS: ", 1);
    ft_putstr_fd(message, 1);
    ft_putstr_fd(COLOR_RESET, 1);
    ft_putchar_fd('\n', 1);
}
```

---

[← Back to Main README](../../README.md)
