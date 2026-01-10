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


## Implementation Details

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

---

[← Back to Main README](../../README.md)
