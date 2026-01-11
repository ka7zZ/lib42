# lib42 – A Personal C Foundation Library

> Built during the 42 curriculum by **aghergut** (42 Madrid)

## Overview

lib42 is my personal C library that started as a reimplementation of standard C functions (**libft**) and grew to include **ft_printf** and **get_next_line**, all integrated into a single static library.

The goal wasn't just to reproduce existing functions — it was to understand:
- **How C works at a low level**
- **How to design reusable code**
- **How to grow a project without breaking its structure**

This repository reflects my progression from basic memory manipulation to complex architectural decisions involving state, extensibility, and I/O management.

---

## What This Project Taught Me

Working on lib42 helped me develop:

### **Low-level reasoning**
Understanding memory, pointers, buffers, and system calls instead of relying on abstractions.

### **Architectural thinking**
Designing functions that can evolve (especially in ft_printf) and managing shared logic inside a single library.

### **Discipline & debugging**
Writing defensive code, handling edge cases, and learning to debug segmentation faults, leaks, and undefined behavior.

### **Code ownership**
Every line was written, tested, and fixed by me. I now understand *why* things work, not just *that* they work

---

## Project Structure

```
lib42/
├── libft.h              # Main header file
├── Makefile             # Compilation rules
│
├── changechar/          # Character case conversion (toupper, tolower)
├── checkchar/           # Character validation (isalpha, isdigit, etc.)
├── strtoint/            # String ↔ Integer conversion (atoi, itoa)
├── strings/             # String manipulation (20+ functions)
├── memory/              # Memory operations (memcpy, memset, etc.)
├── puts/                # Output functions (putchar_fd, putstr_fd, etc.)
├── lists/               # Linked list operations (9 functions)
├── maps/                # Working with 2D arrays
│
├── ft_printf/           # Printf reimplementation
│   ├── ft_printf.c
│   ├── ft_printf.h
│   ├── flags/           # Flag handlers (-, 0, #, +, space)
│   ├── prints/          # Type-specific printers (char, str, int, hex, ptr)
│   └── utils/           # Helper utilities
│
└── get_next_line/       # Line reading from file descriptors
    ├── get_next_line.c
    └── get_next_line.h
```

For detailed documentation of each module, see the README files in respective folders:
- **[ft_printf/](ft_printf/README.md)** - Formatted output implementation
- **[get_next_line/](get_next_line/README.md)** - File reading utilities  
- **[lists/](lists/README.md)** - Linked list data structure
- **[memory/](memory/README.md)** - Memory operations

---

## Compilation & Usage

```bash
# Compile the library
make
```

This creates `libft.a` — a static library containing all functions.

**Using in your project:**
```c
#include "libft.h"
```

```bash
cc main.c -L. -lft -o program
```

---

## Testing

Each module was tested through:
- **Unit tests**: Small dedicated test files for each function
- **Edge cases**: NULL pointers, empty inputs, buffer overlaps, extreme values
- **Memory validation**: Valgrind checks for leaks and invalid access
- **Comparison testing**: Output validation against system functions

---

## What's Inside

| Module | Functions | Purpose |
|--------|-----------|---------|
| **Character checks** | 5 | `isalpha`, `isdigit`, `isalnum`, `isascii`, `isprint` |
| **String operations** | 20+ | `strlen`, `strchr`, `strjoin`, `split`, `substr`, etc. |
| **Memory operations** | 5 | `memset`, `memcpy`, `memmove`, `memchr`, `memcmp` |
| **Linked lists** | 9 | Create, add, delete, iterate, map |
| **Conversions** | 2 | `atoi`, `itoa` |
| **Output** | 4 | `putchar_fd`, `putstr_fd`, `putendl_fd`, `putnbr_fd` |
| **ft_printf** | 1 | Full printf with flags (`cspdiuxX%`) |
| **get_next_line** | 1 | Read lines from any file descriptor |

**Total:** 50+ functions

---

## Final Note

This library represents my transition from **writing C code** to **thinking like a C programmer**.

It is not perfect — but it is mine, fully understood, and designed to grow.

---

**Status:** Completed with bonuses ✅  
**Standards:** Follows 42 Norm, compiles with `-Wall -Wextra -Werror`  
**Memory:** Zero leaks (Valgrind verified)
