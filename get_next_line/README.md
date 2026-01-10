# Get Next Line Module

Read a line from a file descriptor, handling buffering and multiple file descriptors simultaneously.

## 📋 Overview

`get_next_line` is a function that reads one line at a time from a file descriptor, managing internal buffers efficiently. It's a fundamental I/O function that demonstrates advanced file handling, static variables, and memory management.

## 🎯 Function Signature

```c
char *get_next_line(int fd);
```

**Parameters**:
- `fd`: File descriptor to read from

**Returns**:
- Pointer to the line read (including `\n` if present)
- `NULL` when EOF reached or on error

**Behavior**:
```
File content: "Hello\nWorld\n"

Call 1: get_next_line(fd) → "Hello\n"
Call 2: get_next_line(fd) → "World\n"
Call 3: get_next_line(fd) → NULL (EOF)
```

## 🧠 Programming Concepts

### Static Variables

Static variables persist between function calls:

```c
char *get_next_line(int fd)
{
    static char *buffer;  // Retains value between calls
    
    // First call: buffer is NULL or previous leftover
    // Next calls: buffer contains leftover from last read
}
```

**Visual**:
```
File: "Hello\nWorld\nTest"
BUFFER_SIZE = 5

Call 1:
  Read: "Hello"
  Find '\n': Yes, at position 5
  Return: "Hello\n"
  Save: "" (nothing left)

Call 2:
  Read: "World"
  Find '\n': Yes
  Return: "World\n"
  Save: ""

Call 3:
  Read: "Test"
  Find '\n': No
  Return: "Test"
  Save: NULL (EOF)
```

### Buffered Reading

Instead of reading 1 byte at a time (slow), read chunks:

```c
#define BUFFER_SIZE 42  // Read 42 bytes at once

// Inefficient: 1000 system calls for 1000 bytes
for (i = 0; i < 1000; i++)
    read(fd, &c, 1);

// Efficient: ~24 system calls for 1000 bytes (with BUFFER_SIZE=42)
while (bytes_needed > 0)
    read(fd, buffer, BUFFER_SIZE);
```

**System call overhead**:
```
read(fd, buf, 1)     → ~1000 syscalls for 1KB file
read(fd, buf, 1024)  → ~1 syscall for 1KB file
```

### Multiple File Descriptors

Handle multiple files simultaneously using static arrays:

```c
#define MAX_FD 1024

char *get_next_line(int fd)
{
    static char *buffers[MAX_FD];  // One buffer per fd
    
    // Each fd maintains its own read position
    if (fd < 0 || fd >= MAX_FD)
        return (NULL);
    
    // Work with buffers[fd]...
}
```

**Visual**:
```
buffers[3] → "leftover from file1.txt\n..."
buffers[4] → "leftover from file2.txt\n..."
buffers[5] → "leftover from file3.txt\n..."

Each fd operates independently
```

### Line Delimiter Handling

```c
Input: "Hello\nWorld"
         ↑
    Delimiter found at position 5

Process:
1. Extract: "Hello\n"  → Return this
2. Save: "World"       → Keep for next call
```

**Edge cases**:
```
1. No newline at EOF: "Hello"     → Return "Hello" (no \n)
2. Empty line: "\n"                → Return "\n"
3. Multiple newlines: "\n\n\n"     → Return "\n" each time
4. Empty file: ""                  → Return NULL
```

### Memory Management Strategy

```c
Persistent storage:
┌─────────────────────────────────┐
│ Static buffer (between calls)   │
└─────────────────────────────────┘

Temporary storage:
┌─────────────────────────────────┐
│ Read buffer (freed each call)   │
└─────────────────────────────────┘

Return value:
┌─────────────────────────────────┐
│ Line string (caller must free)  │
└─────────────────────────────────┘
```

## 💡 Usage Examples

### Basic File Reading

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

### Reading with Line Numbers

```c
void print_file_with_numbers(char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;
    int line_num = 1;
    
    if (fd < 0)
    {
        perror("open");
        return;
    }
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%4d | %s", line_num, line);
        free(line);
        line_num++;
    }
    
    close(fd);
}

// Usage
print_file_with_numbers("source.c");
// Output:
//    1 | #include <stdio.h>
//    2 | 
//    3 | int main(void)
//    4 | {
//    5 |     printf("Hello\n");
//    6 |     return (0);
//    7 | }
```

### Reading from Standard Input

```c
#include <unistd.h>  // STDIN_FILENO

void interactive_input(void)
{
    char *line;
    
    printf("Enter text (Ctrl+D to end):\n");
    
    while ((line = get_next_line(STDIN_FILENO)) != NULL)
    {
        printf("You entered: %s", line);
        
        // Exit on "quit"
        if (strncmp(line, "quit", 4) == 0)
        {
            free(line);
            break;
        }
        
        free(line);
    }
}
```

### Processing CSV Files

```c
typedef struct s_person
{
    char *name;
    int age;
    char *city;
} t_person;

t_person *parse_csv_line(char *line)
{
    t_person *person = malloc(sizeof(t_person));
    
    person->name = strtok(line, ",");
    person->age = atoi(strtok(NULL, ","));
    person->city = strtok(NULL, "\n");
    
    return (person);
}

void read_csv(char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;
    
    // Skip header
    line = get_next_line(fd);
    free(line);
    
    // Read data lines
    while ((line = get_next_line(fd)) != NULL)
    {
        t_person *person = parse_csv_line(line);
        printf("Name: %s, Age: %d, City: %s\n",
               person->name, person->age, person->city);
        
        free(person);
        free(line);
    }
    
    close(fd);
}

// Usage with file "people.csv":
// name,age,city
// Alice,25,Paris
// Bob,30,London
```

### Reading Multiple Files

```c
void compare_files(char *file1, char *file2)
{
    int fd1 = open(file1, O_RDONLY);
    int fd2 = open(file2, O_RDONLY);
    char *line1, *line2;
    int line_num = 1;
    
    while (1)
    {
        line1 = get_next_line(fd1);
        line2 = get_next_line(fd2);
        
        if (!line1 && !line2)
            break;  // Both files ended
        
        if (!line1 || !line2 || strcmp(line1, line2) != 0)
        {
            printf("Difference at line %d:\n", line_num);
            printf("  File1: %s", line1 ? line1 : "(EOF)\n");
            printf("  File2: %s", line2 ? line2 : "(EOF)\n");
        }
        
        free(line1);
        free(line2);
        line_num++;
    }
    
    close(fd1);
    close(fd2);
}
```

### Configuration File Parser

```c
typedef struct s_config
{
    char *key;
    char *value;
    struct s_config *next;
} t_config;

t_config *parse_config(char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;
    t_config *config = NULL;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n')
        {
            free(line);
            continue;
        }
        
        // Parse "key=value"
        char *equals = strchr(line, '=');
        if (equals)
        {
            *equals = '\0';
            
            t_config *item = malloc(sizeof(t_config));
            item->key = strdup(line);
            item->value = strdup(equals + 1);
            item->next = config;
            config = item;
        }
        
        free(line);
    }
    
    close(fd);
    return (config);
}

// Usage with config.txt:
// # Database settings
// host=localhost
// port=5432
// db_name=myapp
```

### Log File Analyzer

```c
typedef struct s_log_stats
{
    int total_lines;
    int error_count;
    int warning_count;
} t_log_stats;

t_log_stats analyze_log(char *logfile)
{
    int fd = open(logfile, O_RDONLY);
    char *line;
    t_log_stats stats = {0, 0, 0};
    
    while ((line = get_next_line(fd)) != NULL)
    {
        stats.total_lines++;
        
        if (strstr(line, "[ERROR]"))
            stats.error_count++;
        else if (strstr(line, "[WARNING]"))
            stats.warning_count++;
        
        free(line);
    }
    
    close(fd);
    return (stats);
}

// Usage
t_log_stats stats = analyze_log("app.log");
printf("Total lines: %d\n", stats.total_lines);
printf("Errors: %d\n", stats.error_count);
printf("Warnings: %d\n", stats.warning_count);
```

### Simple grep Implementation

```c
void grep(char *pattern, char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;
    int line_num = 1;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        if (strstr(line, pattern))
            printf("%d:%s", line_num, line);
        
        free(line);
        line_num++;
    }
    
    close(fd);
}

// Usage
grep("TODO", "main.c");
// Output:
// 15:    // TODO: Implement error handling
// 42:    // TODO: Optimize this loop
```

## 🔍 Implementation Details

### Buffer Size Considerations

```c
// Small buffer: More read() calls, less memory
#define BUFFER_SIZE 1

// Large buffer: Fewer read() calls, more memory
#define BUFFER_SIZE 4096

// Typical choice: Balance between speed and memory
#define BUFFER_SIZE 42  // (42 School standard)
```

### Algorithm Outline

```c
char *get_next_line(int fd)
{
    static char *buffer;
    char *line;
    char *temp;
    int bytes_read;
    
    // 1. Read until '\n' found or EOF
    while (!strchr(buffer, '\n') && bytes_read > 0)
    {
        temp = malloc(BUFFER_SIZE + 1);
        bytes_read = read(fd, temp, BUFFER_SIZE);
        buffer = join_and_free(buffer, temp);
    }
    
    // 2. Extract line up to '\n'
    line = extract_line(buffer);
    
    // 3. Save remainder for next call
    buffer = save_remainder(buffer);
    
    return (line);
}
```

### Typical Helper Functions

```c
// Join two strings and free old buffer
char *ft_strjoin_free(char *s1, char *s2);

// Extract line up to '\n' (included)
char *extract_line(char *buffer);

// Get remainder after '\n'
char *get_remainder(char *buffer);

// Find '\n' in string
char *ft_strchr(char *s, int c);
```

## 📊 Performance

### Time Complexity
- **Per line**: O(n) where n = line length
- **Per file**: O(m) where m = total file size

### Space Complexity
- **Static buffer**: O(k) where k = remaining unprocessed data
- **Temporary**: O(BUFFER_SIZE) for read operations
- **Return value**: O(n) where n = line length

### System Calls

```
File: 1000 bytes, BUFFER_SIZE = 100

read() calls = ceil(1000 / 100) = 10 system calls

vs.

BUFFER_SIZE = 1
read() calls = 1000 system calls
```

## ⚠️ Important Considerations

### Memory Leaks

```c
// WRONG: Leak - line not freed
while ((line = get_next_line(fd)))
    process(line);  // Forgot to free!

// CORRECT: Free each line
while ((line = get_next_line(fd)))
{
    process(line);
    free(line);
}
```

### File Descriptor Validation

```c
// Always check fd
if (fd < 0 || fd >= MAX_FD)
    return (NULL);

// Check read errors
if (read(fd, buffer, BUFFER_SIZE) < 0)
{
    free(buffer);
    return (NULL);
}
```

### Buffer Size

```c
// Compile-time definition
gcc -D BUFFER_SIZE=42 get_next_line.c

// Or in code
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
```

### Static Variable Cleanup

```c
// Static buffer persists until program ends
// For proper cleanup on EOF:
if (!line && buffer)
{
    free(buffer);
    buffer = NULL;
}
```

## 🎓 Key Learnings

1. **Static variables**: Persistent state between function calls
2. **Buffered I/O**: Efficient reading strategy
3. **Multiple FDs**: Managing multiple open files
4. **Memory management**: Careful allocation and freeing
5. **Edge cases**: EOF, empty files, no newline at end
6. **System calls**: Understanding `read()` behavior

## 🔗 Related Concepts

- **File descriptors**: Unix I/O model
- **Buffering**: Performance optimization technique
- **String manipulation**: Building strings dynamically
- **State machines**: Tracking read position
- **Resource management**: RAII-style patterns

## 📚 Standard Library Equivalents

- `fgets()` - Similar but buffered automatically
- `getline()` - POSIX function (similar functionality)
- C++ `std::getline()` - Stream-based line reading

### Comparison

```c
// get_next_line
char *line = get_next_line(fd);
free(line);

// fgets (requires FILE*)
FILE *file = fdopen(fd, "r");
char buffer[1024];
fgets(buffer, sizeof(buffer), file);

// getline (POSIX)
char *line = NULL;
size_t len = 0;
getline(&line, &len, file);
free(line);
```

## 🚀 Advanced Usage

### Reading from Network Sockets

```c
#include <sys/socket.h>

void read_from_socket(int socket_fd)
{
    char *line;
    
    // Receive HTTP request line by line
    while ((line = get_next_line(socket_fd)) != NULL)
    {
        if (strcmp(line, "\r\n") == 0)
        {
            free(line);
            break;  // End of HTTP headers
        }
        
        printf("Header: %s", line);
        free(line);
    }
}
```

### Progress Reporting

```c
void copy_with_progress(char *src, char *dst)
{
    int fd_in = open(src, O_RDONLY);
    int fd_out = open(dst, O_WRONLY | O_CREAT, 0644);
    char *line;
    int lines = 0;
    
    while ((line = get_next_line(fd_in)) != NULL)
    {
        write(fd_out, line, strlen(line));
        free(line);
        
        lines++;
        if (lines % 100 == 0)
            printf("\rCopied %d lines...", lines);
    }
    
    printf("\nDone! Total: %d lines\n", lines);
    close(fd_in);
    close(fd_out);
}
```

---

[← Back to Main README](../../README.md)
