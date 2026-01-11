# get_next_line - File Descriptor Line Reader

> A function that reads and returns one line at a time from a file descriptor, mastering low-level I/O and state management.

## Project Goal

Create a function that returns a single line (ending with `\n`) from any file descriptor on each call, maintaining state between calls to handle partial reads. This project teaches **system-level programming**, **buffer management**, and **persistent memory with static variables**.


---

## What I Learned

### Low-Level File I/O
- Direct use of `read()` system call (not `fgets()` or higher-level functions)
- Understanding file descriptors beyond stdin (0), stdout (1), stderr (2)
- Working with `open()`, `close()`, and file permissions
- Binary-safe reading (handles any data, not just text)

### Static Variables for State Persistence
The key challenge: **maintaining leftover data between function calls**.

When you read from a file, the `read()` call might fetch more data than needed for one line. That extra data must be saved for the next call:

```
File content:    "Hello\nWorld\nFoo\n"
                  
Call 1: read(fd, buffer, BUFFER_SIZE)
        Buffer: "Hello\nWorld\nFoo\n"
        Extract: "Hello\n"
        Save in static: "World\nFoo\n"
        
Call 2: Already have "World\nFoo\n" in static
        Extract: "World\n"
        Save in static: "Foo\n"
        
Call 3: Already have "Foo\n" in static
        Extract: "Foo\n"
        Save in static: (empty)
        
Call 4: Need to read more...
        read() returns 0 (EOF)
        Return: NULL (no more lines)
```

### Buffer Management
- Configurable `BUFFER_SIZE` at compile time: `-D BUFFER_SIZE=42`
- Smaller buffers = more `read()` calls (but less memory)
- Larger buffers = fewer syscalls (but more memory)
- Must handle edge cases: `BUFFER_SIZE=1` and `BUFFER_SIZE=1000000`

### Memory Efficiency
- Avoid unnecessary allocations
- Free leftover data when done with a file descriptor
- Handle memory leaks when switching between files
- Careful with `strjoin` and `strdup` to prevent double frees

---

## Parameters & Return Value

### Parameters
- `fd`: File descriptor to read from (from `open()`, or 0 for stdin)

### Return Value
- **Success**: Pointer to a string containing the next line (including `\n` if present)
- **EOF**: NULL when end of file is reached
- **Error**: NULL on read errors or invalid fd

### Caller Responsibilities
The caller must `free()` the returned string:

---

## Technical Implementation

### Algorithm Overview

```
1. Check if static variable has leftover data
   ├─ If yes: use it
   └─ If no: initialize empty
   
2. Loop until we find '\n' or EOF:
   ├─ Allocate buffer[BUFFER_SIZE + 1]
   ├─ Call read(fd, buffer, BUFFER_SIZE)
   ├─ If read returns 0: EOF reached, break
   ├─ If read returns -1: error, return NULL
   ├─ Null-terminate buffer
   └─ Join buffer to leftover (strjoin)
   
3. Search for '\n' in leftover:
   ├─ If found:
   │  ├─ Extract line up to and including '\n'
   │  ├─ Save remainder back to static
   │  └─ Return line
   └─ If not found:
      ├─ If we have data but no '\n': last line without newline
      ├─ Return leftover
      └─ Clear static
      
4. If nothing left: return NULL
```

### Example Implementation Flow

**File**: `"Hello\nWorld"`  
**BUFFER_SIZE**: `5`

```
Call 1:
├─ leftover: (empty)
├─ read() → "Hello"
├─ leftover: "Hello"
├─ No '\n' found, read again
├─ read() → "\nWorl"
├─ leftover: "Hello\nWorl"
├─ '\n' found at index 5
├─ Extract: "Hello\n"
├─ Save: "Worl"
└─ Return: "Hello\n"

Call 2:
├─ leftover: "Worl"
├─ No '\n', read again
├─ read() → "d" (only 1 byte left)
├─ leftover: "World"
├─ No '\n', read again
├─ read() → 0 (EOF)
├─ Have data but no more to read
├─ Extract: "World"
├─ Clear leftover
└─ Return: "World"

Call 3:
├─ leftover: (empty)
├─ read() → 0 (EOF)
└─ Return: NULL
```

---

## Bonus: Multi-FD Support

The bonus part requires handling **multiple file descriptors simultaneously** using only one static variable.

Each fd must maintain its own leftover buffer independently.

### Solution: Static Array
```c
#define MAX_FD 1024

char *get_next_line(int fd)
{
    static char *leftover[MAX_FD];  // Array of leftovers
    
    // Use leftover[fd] for this specific file descriptor
    // ...
}
```

Now:
- `leftover[3]` stores data for fd 3
- `leftover[5]` stores data for fd 5
- No cross-contamination between files

### Edge Cases Handled
- **Invalid fd**: Check `fd < 0` or `fd >= MAX_FD`
- **Simultaneous reads**: Each fd is independent
- **Closing fd**: Leftover data freed on EOF or error
- **fd reuse**: When a fd is closed and reopened, old leftover is cleared

---

## Common Pitfalls Avoided

1. **Forgetting to null-terminate buffer**: `buffer[bytes_read] = '\0'`
2. **Not freeing leftover on error**: Memory leak on read failure
3. **Double free**: Freeing leftover twice when switching fds
4. **Static not cleared on EOF**: Leaving garbage in static variable
5. **Off-by-one in line extraction**: Including/excluding `\n` correctly
6. **Not handling BUFFER_SIZE=1**: Special case testing
7. **Assuming lines end with \n**: Last line might not have newline

---

## Key Takeaways

1. **Static variables are powerful but tricky**: Required careful memory management
2. **System calls are expensive**: Buffer size significantly impacts performance
3. **Edge cases dominate**: Spent 60% of time on EOF, empty files, no newline at end
4. **State machines are everywhere**: Managing leftover data was essentially a state machine
5. **Testing with extremes**: `BUFFER_SIZE=1` caught subtle bugs early

This project deepened my understanding of how file I/O works at the system level and taught me to manage persistent state in C without global variables.

**Validation**: Passed 42 evaluation with 125/100 (bonus included) ✅
