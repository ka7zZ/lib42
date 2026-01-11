# String Manipulation - Core Text Processing Functions

> A comprehensive suite of 20+ string manipulation functions, forming the backbone of text processing in C.

## Purpose

Reimplementing standard C library string functions teaches fundamental concepts:
- **Pointer arithmetic**: Direct memory addressing
- **Buffer safety**: Preventing overflows
- **Null-termination**: Proper C string handling
- **Edge cases**: Empty strings, NULL pointers, zero lengths

---

## Function Categories

### 1. String Examination
| Function | Description | Returns |
|----------|-------------|---------|
| `ft_strlen` | Calculate string length | Number of chars before `\0` |
| `ft_strchr` | Find first occurrence of char | Pointer to char or NULL |
| `ft_strrchr` | Find last occurrence of char | Pointer to char or NULL |
| `ft_strnstr` | Locate substring in string | Pointer to substring or NULL |
| `ft_strncmp` | Compare n bytes of strings | Integer (-1, 0, 1) |

### 2. **String Manipulation**
```c
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strtrim(char const *s1, char const *set);
char **ft_split(char const *s, char c);
```

---

### 3. String Conversion & Transformation

#### **ft_strmapi**
```c
char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
```
Creates a new string by applying function `f` to each character, passing its index.

**ft_striteri** - Similar but modifies in place:
```c
void ft_striteri(char *s, void (*f)(unsigned int, char*));
```

---

### 5. **String Tokenization**

**ft_strtok** - Split string by delimiter (modifies original)
```c
char *ft_strtok(char *str, const char *delim);
```

**ft_split** - Split string into array
```c
char **ft_split(char const *s, char c);
```

---

## Key Takeaways

1. **String manipulation is everywhere**: Foundation for most C programs
2. **Null termination is critical**: Every string must end with `\0`
3. **Buffer sizes matter**: Understanding dest_size prevents overflows
4. **const correctness**: Used `const char *` for read-only parameters
5. **Edge cases dominate**: NULL pointers, empty strings, size 0 all need handling

These functions became the most-used utilities in all subsequent 42 projects, proving the value of building a solid foundation.
