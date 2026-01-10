# lib42 - Custom C Library

A comprehensive C library developed as part of the 42 Common Core curriculum, extended with additional functionality for practical projects.

## 📖 Overview

**lib42** is a custom implementation of standard C library functions plus advanced data structures and utilities. This project represents a deep dive into low-level programming, memory management, and algorithm implementation in C.

The library started with the **libft** project (42's foundational C library project) and has been extended throughout the common core with additional modules for formatted output, file I/O, and data structures.

## 🎯 Project Goals

- **Master C fundamentals**: Pointers, memory allocation, type casting, and bit manipulation
- **Understand standard library internals**: Reimplementing libc functions from scratch
- **Practice memory safety**: Proper allocation, deallocation, and handling edge cases
- **Learn data structures**: Implementing linked lists, hash maps, and dynamic arrays
- **Build reusable code**: Creating a library that can be used across multiple 42 projects

## 🧠 Key Concepts & Learning Outcomes

### Memory Management
- Dynamic memory allocation with `malloc`, `free`, and `calloc`
- Understanding stack vs heap allocation
- Preventing memory leaks and dangling pointers
- Safe handling of overlapping memory regions (`memmove` vs `memcpy`)

### String Manipulation
- Null-terminated strings and buffer management
- String searching, parsing, and transformation algorithms
- Efficient string concatenation and splitting

### Data Structures
- Singly linked lists with various operations
- Hash map implementation for key-value storage
- Dynamic array management

### Algorithm Implementation
- String searching algorithms (substring matching)
- Number base conversions (decimal, hexadecimal)
- Parsing and tokenization

### System Programming
- File descriptor operations
- Buffered I/O for efficient file reading
- Variadic functions for formatted output

### Code Quality
- Norminette compliance (42's coding standard)
- Modular architecture with clear separation of concerns
- Comprehensive error handling

## 📚 Library Modules

### Core Functions

#### [Character Transformation](./changechar/)
Character case conversion functions.
- **Concepts**: ASCII manipulation, conditional transformations

#### [Character Checking](./checkchar/)
Character classification and validation functions.
- **Concepts**: ASCII ranges, boolean logic, input validation

#### [Memory Operations](./memory/)
Low-level memory manipulation functions.
- **Concepts**: Pointer arithmetic, byte-level operations, memory safety, overlapping regions

#### [String Operations](./strings/)
Comprehensive string manipulation and analysis functions.
- **Concepts**: String algorithms, dynamic allocation, buffer management, parsing

#### [String/Integer Conversion](./strtoint/)
Functions for converting between strings and integers.
- **Concepts**: Base conversion, parsing, digit extraction, overflow handling

#### [Output Functions](./puts/)
Functions for writing to file descriptors.
- **Concepts**: File descriptors, system calls, buffered I/O

### Data Structures

#### [Linked Lists](./lists/)
Complete singly linked list implementation.
- **Concepts**: Dynamic data structures, pointers, list traversal, memory management

#### [Hash Maps](./maps/)
Key-value storage with hash table implementation.
- **Concepts**: Hash functions, collision handling, dynamic resizing

### Advanced Features

#### [Get Next Line](./get_next_line/)
Efficient line-by-line file reading utility.
- **Concepts**: Buffered I/O, static variables, file descriptor management

#### [ft_printf](./ft_printf/)
Custom implementation of printf with format specifiers and flags.
- **Concepts**: Variadic functions, format parsing, number conversion, flag handling

## 🔧 Compilation & Usage

### Building the Library

```bash
cd lib42
make        # Compile the library
make clean  # Remove object files
make fclean # Remove object files and library
make re     # Recompile from scratch
```

This creates `libft.a`, which can be linked to your projects.

### Using in Your Project

```c
#include "libft.h"

int main(void)
{
    char *str = ft_strdup("Hello, 42!");
    ft_putendl_fd(str, 1);
    free(str);
    return (0);
}
```

Compile with:
```bash
gcc -Wall -Wextra -Werror main.c -L./lib42 -lft -o program
```

## 🧪 Testing

Comprehensive test suite available in the `testers/` directory.

```bash
cd testers/lib42_testers
./run_tests.sh
```

See the [Testing README](testers/lib42_testers/README.md) for more details.

## 📊 Project Statistics

- **Total Functions**: 65+
- **Lines of Code**: ~5,000+
- **Modules**: 10
- **Test Cases**: 100+
- **42 Projects Using This Library**: Multiple (ft_printf, get_next_line, push_swap, etc.)

## 📖 Complete Function Documentation

For detailed explanations with visual diagrams for every function, see:
- **[FUNCTION_DEMONSTRATIONS.md](FUNCTION_DEMONSTRATIONS.md)** - Complete guide with visual representations

## 🎓 Skills Developed

### Technical Skills
- ✅ Low-level C programming
- ✅ Memory management and debugging
- ✅ Algorithm implementation
- ✅ Data structure design
- ✅ Code optimization
- ✅ Unix system calls
- ✅ Makefile creation
- ✅ Library architecture

### Soft Skills
- ✅ Problem-solving and debugging
- ✅ Reading technical documentation
- ✅ Code organization and modularity
- ✅ Attention to detail (memory leaks, edge cases)
- ✅ Iterative development

## 🏆 42 Curriculum Integration

This library serves as the foundation for numerous 42 projects:
- **Libft**: Core implementation
- **ft_printf**: Formatted output
- **get_next_line**: File reading
- **push_swap**: Sorting algorithms
- **minishell**: Shell implementation
- **philosophers**: Threading and synchronization
- And many more...

## 📝 Code Standards

All code follows the **Norminette** (42's coding standard):
- Maximum 25 lines per function
- Maximum 5 functions per file
- No variable declarations in the middle of functions
- Specific formatting rules for indentation, spacing, and naming

## 🔮 Future Enhancements

- [ ] Thread-safe versions of functions
- [ ] Additional data structures (binary trees, queues)
- [ ] More string algorithms
- [ ] Performance optimizations
- [ ] Extended printf format specifiers

## 👨‍💻 Author

**aghergut** - 42 Madrid

## 📄 License

This project is part of the 42 School curriculum. Feel free to reference and learn from it, but respect academic integrity policies.

---

*Built with 💻 at 42 Madrid*
