# String Operations Module

Comprehensive string manipulation, analysis, and transformation functions.

## 📋 Overview

This module provides a complete suite of string operations organized into logical categories: examination, manipulation, allocation, tokenization, transformation, and initialization. These functions are the workhorses of text processing in C and form the foundation of many higher-level operations.

## 🎯 Function Categories

### 📏 Examination Functions
Functions that analyze strings without modifying them.

#### `ft_strlen`
```c
size_t ft_strlen(const char *str);
```
Returns the length of a string (excluding null terminator).

#### `ft_strchr`
```c
char *ft_strchr(const char *str, int ch);
```
Finds the **first** occurrence of a character. Returns pointer to match or NULL.

#### `ft_strrchr`
```c
char *ft_strrchr(const char *str, int ch);
```
Finds the **last** occurrence of a character. Searches backward from end.

#### `ft_strnstr`
```c
char *ft_strnstr(const char *haystack, const char *needle, size_t n);
```
Finds first occurrence of substring within first `n` characters.

#### `ft_strncmp`
```c
int ft_strncmp(const char *s1, const char *s2, size_t n);
```
Compares up to `n` characters. Returns 0 if equal, negative if s1 < s2, positive if s1 > s2.

---

### ✏️ Manipulation Functions
Functions that modify strings in place or copy between buffers.

#### `ft_strlcpy`
```c
size_t ft_strlcpy(char *dst, const char *src, size_t size);
```
Safe string copy - guarantees null-termination and prevents buffer overflow.

#### `ft_strlcat`
```c
size_t ft_strlcat(char *dst, const char *src, size_t size);
```
Safe string concatenation with size limit.

#### `ft_strncat`
```c
void ft_strncat(char *dest, char *src, size_t n);
```
Concatenates up to `n` characters from source to destination.

---

### 🆕 Allocation Functions
Functions that create new strings (require `free()`).

#### `ft_strdup`
```c
char *ft_strdup(const char *s);
```
Duplicates a string in newly allocated memory.

#### `ft_substr`
```c
char *ft_substr(char const *s, unsigned int start, size_t len);
```
Extracts substring from index `start` with length `len`.

#### `ft_strjoin`
```c
char *ft_strjoin(char const *s1, char const *s2);
```
Concatenates two strings into a new string.

#### `ft_strtrim`
```c
char *ft_strtrim(char const *s1, char const *set);
```
Removes characters from `set` at beginning and end of string.

#### `ft_appendchar`
```c
char *ft_appendchar(char *str, char ch);
```
Appends a character to string, reallocating memory.

---

### ✂️ Tokenization Functions
Functions that split strings into components.

#### `ft_split`
```c
char **ft_split(char *s, char c);
```
Splits string by delimiter into null-terminated array of strings.

#### `ft_strtok`
```c
char *ft_strtok(char *str, const char *delim);
```
Tokenizes string by multiple delimiters (modifies original string).

---

### 🔄 Transformation Functions
Functions that apply transformations to strings.

#### `ft_striteri`
```c
void ft_striteri(char *s, void (*f)(unsigned int, char*));
```
Applies function to each character with its index (in-place modification).

#### `ft_strmapi`
```c
char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
```
Applies function to each character, returns new string.

---

### 🔧 Initialization Functions
Functions for memory initialization.

#### `ft_bzero`
```c
void ft_bzero(void *s, size_t n);
```
Sets `n` bytes to zero.

#### `ft_calloc`
```c
void *ft_calloc(size_t n, size_t size);
```
Allocates memory for `n` elements of `size` bytes and zeros it.

## 🧠 Programming Concepts

### Null-Terminated Strings
All string functions rely on the null terminator (`\0`):
```c
char str[] = "Hello";  // Actually: ['H']['e']['l']['l']['o']['\0']
```

### Pointer Return Values
Many functions return pointers:
- **Non-NULL**: Points to result or location in string
- **NULL**: Indicates not found or error

### Memory Allocation Patterns
Functions that allocate memory follow a pattern:
1. Calculate required size
2. Allocate with `malloc` or `calloc`
3. Copy/construct result
4. Return pointer (caller must `free`)

### Safe vs Unsafe Functions
```c
// UNSAFE - no bounds checking
strcpy(dst, src);    // Buffer overflow risk!
strcat(dst, src);    // Buffer overflow risk!

// SAFE - size-limited
ft_strlcpy(dst, src, size);   // Guarantees null-termination
ft_strlcat(dst, src, size);   // Prevents overflow
```

### Substring Searching Algorithms
Multiple approaches for finding substrings:
- **Linear search**: `ft_strnstr` scans character by character
- **Character search**: `ft_strchr` for single character (faster)
- **Reverse search**: `ft_strrchr` searches from end

## 💡 Usage Examples

### String Analysis
```c
char *str = "Hello, World!";

// Get length
size_t len = ft_strlen(str);  // 13

// Find character
char *comma = ft_strchr(str, ',');  // Points to ", World!"
char *last_l = ft_strrchr(str, 'l');  // Points to "ld!"

// Find substring
char *world = ft_strnstr(str, "World", 20);  // Points to "World!"

// Compare strings
if (ft_strncmp("abc", "abd", 3) < 0)
    printf("'abc' comes before 'abd'\n");
```

### String Copying
```c
char buffer[20];
char *src = "Hello";

// Safe copy with size limit
ft_strlcpy(buffer, src, sizeof(buffer));

// Safe concatenation
ft_strlcat(buffer, " World", sizeof(buffer));
// buffer = "Hello World"
```

### String Creation
```c
// Duplicate string
char *original = "Test";
char *copy = ft_strdup(original);
free(copy);

// Extract substring
char *str = "Hello World";
char *sub = ft_substr(str, 6, 5);  // "World"
free(sub);

// Join strings
char *s1 = "Hello ";
char *s2 = "World";
char *joined = ft_strjoin(s1, s2);  // "Hello World"
free(joined);

// Trim whitespace
char *str = "  \tHello  \n";
char *trimmed = ft_strtrim(str, " \t\n");  // "Hello"
free(trimmed);
```

### String Splitting
```c
// Split CSV
char *csv = "John,Doe,25,Engineer";
char **fields = ft_split(csv, ',');
// fields[0] = "John"
// fields[1] = "Doe"
// fields[2] = "25"
// fields[3] = "Engineer"
// fields[4] = NULL

// Free array
int i = 0;
while (fields[i])
    free(fields[i++]);
free(fields);

// Tokenize with multiple delimiters
char str[] = "word1,word2;word3 word4";
char *token = ft_strtok(str, ", ;");
while (token)
{
    printf("%s\n", token);
    token = ft_strtok(NULL, ", ;");
}
```

### String Transformation
```c
// Convert to uppercase using striteri
void to_upper(unsigned int i, char *c)
{
    if (*c >= 'a' && *c <= 'z')
        *c -= 32;
}
char str[] = "hello";
ft_striteri(str, to_upper);  // str = "HELLO"

// Create modified copy using strmapi
char encrypt_char(unsigned int i, char c)
{
    return c + i;  // Simple shift cipher
}
char *encrypted = ft_strmapi("abc", encrypt_char);
// encrypted = "ace" ('a'+0, 'b'+1, 'c'+2)
free(encrypted);
```

## 🔍 Common Use Cases

### Parsing
- Tokenizing command-line arguments
- Parsing configuration files
- Extracting data from formatted text

### Validation
- Checking input format
- Comparing strings
- Searching for patterns

### Text Processing
- Trimming whitespace
- Case conversion
- String manipulation

### Data Structures
- Building dynamic strings
- Implementing string buffers
- Managing text data

## 🎓 Key Learnings

1. **Memory management**: Distinguishing stack vs heap strings
2. **Buffer safety**: Preventing overflows with size-limited functions
3. **Pointer manipulation**: Understanding char pointers
4. **String algorithms**: Searching, comparing, parsing
5. **Null terminator**: Critical for all string operations
6. **Memory leaks**: Always free allocated strings

## 📊 Performance Considerations

| Function | Time | Space | Notes |
|----------|------|-------|-------|
| `ft_strlen` | O(n) | O(1) | Linear scan |
| `ft_strchr` | O(n) | O(1) | Early exit possible |
| `ft_strncmp` | O(n) | O(1) | Early exit on difference |
| `ft_strdup` | O(n) | O(n) | Allocates new string |
| `ft_split` | O(n) | O(n) | Allocates array + strings |
| `ft_strnstr` | O(n*m) | O(1) | Naive substring search |

## ⚠️ Safety Guidelines

1. **Always check return values**: NULL indicates failure
2. **Free allocated memory**: Prevent leaks
3. **Use size-limited functions**: `strlcpy`, not `strcpy`
4. **Validate input**: Check for NULL pointers
5. **Understand ownership**: Who is responsible for freeing?

## 🔗 Related Modules

- **[Memory Operations](../memory/)** - Low-level byte operations
- **[String/Int Conversion](../strtoint/)** - `atoi`, `itoa`
- **[Character Checking](../checkchar/)** - Character validation

---

[← Back to Main README](../../README.md)
