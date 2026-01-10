# Memory Operations Module

Low-level memory manipulation functions for byte-level operations on arbitrary memory regions.

## 📋 Overview

This module provides fundamental memory manipulation functions that operate at the byte level. These are critical for efficient data handling, buffer management, and implementing higher-level data structures. Understanding these functions is essential for mastering C programming and memory safety.

## 🎯 Functions

### `ft_memset`
```c
void *ft_memset(void *str, int c, size_t n);
```
**Description**: Fills the first `n` bytes of memory with the constant byte `c`.

**Use Cases**: Initialize buffers, clear structures, set arrays to default values.

---

### `ft_memcpy`
```c
void *ft_memcpy(void *dst, const void *src, size_t n);
```
**Description**: Copies `n` bytes from `src` to `dst`. **Does not handle overlapping memory regions.**

**⚠️ Warning**: Undefined behavior if `src` and `dst` overlap!

---

### `ft_memmove`
```c
void *ft_memmove(void *dst, const void *src, size_t n);
```
**Description**: Copies `n` bytes from `src` to `dst`. **Safely handles overlapping memory regions.**

**Key Feature**: Detects overlap direction and copies accordingly (forward or backward).

---

### `ft_memchr`
```c
void *ft_memchr(const void *s, int c, size_t n);
```
**Description**: Searches for the first occurrence of byte `c` in the first `n` bytes of `s`.

**Returns**: Pointer to the matching byte, or NULL if not found.

---

### `ft_memcmp`
```c
int ft_memcmp(const void *s1, const void *s2, size_t n);
```
**Description**: Compares the first `n` bytes of `s1` and `s2`.

**Returns**: 
- `0` if equal
- `< 0` if s1 < s2
- `> 0` if s1 > s2

## 🧠 Programming Concepts

### Pointer Arithmetic
All functions use pointer arithmetic to navigate memory:
```c
unsigned char *ptr = (unsigned char *)address;
ptr[i] = value;  // Access byte at offset i
```

### Type Casting
Memory functions treat all data as unsigned bytes:
```c
unsigned char *bytes = (unsigned char *)ptr;
```
This allows byte-level manipulation regardless of the original type.

### Overlapping Memory Regions

**The Critical Difference: memcpy vs memmove**

```
Overlapping Example:
buffer: [a][b][c][d][e][f][g][h]
         ↑─src    ↑─dst

Using memcpy (WRONG):
- Copies forward: a, b, a, b, a, b...
- Corrupts data!

Using memmove (CORRECT):
- Detects overlap
- Copies backward: [h], [g], [f]...
- Preserves data integrity
```

### Memory Safety
Key considerations:
1. **Null pointer checks**: Prevent segmentation faults
2. **Boundary validation**: Ensure `n` doesn't exceed buffer size
3. **Overlap detection**: Use `memmove` when unsure
4. **Type awareness**: Cast to `unsigned char *` for byte operations

## 💡 Usage Examples

### Initialize Memory
```c
// Zero out a structure
typedef struct s_data {
    int x;
    int y;
    char name[20];
} t_data;

t_data data;
ft_memset(&data, 0, sizeof(t_data));

// Initialize buffer with specific value
char buffer[100];
ft_memset(buffer, 'X', 100);
```

### Copy Data
```c
// Copy array safely (non-overlapping)
int src[] = {1, 2, 3, 4, 5};
int dst[5];
ft_memcpy(dst, src, sizeof(src));

// Copy with overlap protection
char text[] = "Hello World";
ft_memmove(text + 2, text, 9);  // Shift content right
// Result: "HeHello Wo"
```

### Search Memory
```c
// Find delimiter in buffer
char data[] = "name:value;age:25";
char *colon = ft_memchr(data, ':', 17);
// Points to first ':'

// Search in binary data
unsigned char bytes[] = {0xFF, 0x00, 0xAB, 0xCD};
unsigned char *found = ft_memchr(bytes, 0xAB, 4);
```

### Compare Memory
```c
// Compare structures
t_data d1 = {10, 20, "test"};
t_data d2 = {10, 20, "test"};
if (ft_memcmp(&d1, &d2, sizeof(t_data)) == 0)
    printf("Structures are identical\n");

// Compare binary data
unsigned char hash1[32];
unsigned char hash2[32];
if (ft_memcmp(hash1, hash2, 32) != 0)
    printf("Different hashes\n");
```

## 🔍 Common Pitfalls & Solutions

### Pitfall 1: Using memcpy with Overlapping Regions
```c
// WRONG - undefined behavior
char str[] = "abc";
ft_memcpy(str + 1, str, 2);  // Overlap!

// CORRECT - use memmove
ft_memmove(str + 1, str, 2);
```

### Pitfall 2: Forgetting sizeof
```c
// WRONG - only copies 1 byte (size of pointer)
int *arr = malloc(10 * sizeof(int));
ft_memcpy(arr, src, sizeof(arr));

// CORRECT
ft_memcpy(arr, src, 10 * sizeof(int));
```

### Pitfall 3: Null Pointer Dereference
```c
// Always check pointers
if (ptr != NULL)
    ft_memset(ptr, 0, size);
```

## 🎓 Key Learnings

1. **Byte-level operations**: All data can be treated as bytes
2. **Memory overlap**: Critical consideration for safe copying
3. **Pointer casting**: Converting between types for memory access
4. **Performance**: Direct memory operations are faster than loops
5. **Portability**: Works with any data type
6. **Endianness awareness**: Byte order matters for multi-byte values

## 📊 Performance

| Function | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|-------|
| `ft_memset` | O(n) | O(1) | Optimized by compiler |
| `ft_memcpy` | O(n) | O(1) | Fast, but unsafe for overlap |
| `ft_memmove` | O(n) | O(1) | Slightly slower than memcpy |
| `ft_memchr` | O(n) | O(1) | Early exit on match |
| `ft_memcmp` | O(n) | O(1) | Early exit on difference |

## 🔗 Related Functions

String operations (similar but null-terminated):
- `ft_strcpy()` - Copy strings
- `ft_strchr()` - Find character in string
- `ft_strcmp()` - Compare strings

Memory allocation:
- `ft_calloc()` - Allocate and zero memory
- `malloc()` - Allocate memory
- `free()` - Deallocate memory

## 📚 Standard Library Equivalents

These functions replicate the behavior of:
- `memset()` from `<string.h>`
- `memcpy()` from `<string.h>`
- `memmove()` from `<string.h>`
- `memchr()` from `<string.h>`
- `memcmp()` from `<string.h>`

## ⚠️ Critical Safety Rules

1. **Always check buffer sizes**: Prevent buffer overflows
2. **Validate pointers**: Check for NULL before dereferencing
3. **Use memmove for potential overlaps**: When in doubt, use memmove
4. **Respect object boundaries**: Don't access memory beyond allocated space
5. **Consider endianness**: For multi-byte integer comparisons

## 🔬 Advanced Applications

### Custom Data Structure Copying
```c
typedef struct s_node {
    int value;
    struct s_node *next;
} t_node;

// Deep copy of node (excluding pointer)
t_node *copy_node(t_node *src) {
    t_node *dst = malloc(sizeof(t_node));
    ft_memcpy(dst, src, sizeof(t_node));
    dst->next = NULL;  // Reset pointer
    return dst;
}
```

### Buffer Rotation
```c
void rotate_buffer(char *buf, size_t size, size_t shift) {
    char *temp = malloc(shift);
    ft_memcpy(temp, buf, shift);
    ft_memmove(buf, buf + shift, size - shift);
    ft_memcpy(buf + size - shift, temp, shift);
    free(temp);
}
```

---

[← Back to Main README](../../README.md)
