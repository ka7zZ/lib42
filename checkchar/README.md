# Character Checking Module

Functions for validating and classifying characters based on their ASCII properties.

## 📋 Overview

This module provides boolean-style functions (returning 1 or 0) that check whether a character belongs to specific categories. These are essential for input validation, parsing, and text processing.

## 🎯 Functions

### `ft_isalpha`
```c
int ft_isalpha(int c);
```
**Description**: Checks if character is alphabetic (A-Z or a-z).

**Returns**: 1 if alphabetic, 0 otherwise.

---

### `ft_isdigit`
```c
int ft_isdigit(int c);
```
**Description**: Checks if character is a decimal digit (0-9).

**Returns**: 1 if digit, 0 otherwise.

---

### `ft_isalnum`
```c
int ft_isalnum(int c);
```
**Description**: Checks if character is alphanumeric (letter or digit).

**Returns**: 1 if alphanumeric, 0 otherwise.

**Note**: Combination of `ft_isalpha` and `ft_isdigit`.

---

### `ft_isascii`
```c
int ft_isascii(int c);
```
**Description**: Checks if character value is in the ASCII range (0-127).

**Returns**: 1 if valid ASCII, 0 otherwise.

---

### `ft_isprint`
```c
int ft_isprint(int c);
```
**Description**: Checks if character is printable (space to tilde: 32-126).

**Returns**: 1 if printable, 0 otherwise.

## 🧠 Programming Concepts

### Boolean Logic in C
These functions return integers as booleans (C89 standard):
- `1` represents true
- `0` represents false

### Range Checking
Efficient character validation using compound conditionals:
```c
// Check if in range A-Z OR in range a-z
return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
```

### ASCII Categories

```
0-31    : Control characters (non-printable)
32-126  : Printable characters
  32    : Space (first printable)
  48-57 : Digits '0'-'9'
  65-90 : Uppercase 'A'-'Z'
  97-122: Lowercase 'a'-'z'
127     : DEL (non-printable)
128-255 : Extended ASCII
```

### Composition Pattern
Functions can be built from simpler ones:
```c
ft_isalnum = ft_isalpha OR ft_isdigit
```

## 💡 Usage Examples

```c
#include "checkchar.h"

// Validate user input
char input = '5';
if (ft_isdigit(input))
    printf("Valid number\n");

// Parse identifiers (variable names)
char c = '_';
if (ft_isalnum(c) || c == '_')
    printf("Valid identifier character\n");

// Filter printable characters only
char str[] = "Hello\nWorld\t!";
int i = 0;
while (str[i])
{
    if (ft_isprint(str[i]))
        write(1, &str[i], 1);
    i++;
}
// Output: "HelloWorld!" (skips \n and \t)

// Count letters in string
int count_letters(char *str)
{
    int count = 0;
    while (*str)
    {
        if (ft_isalpha(*str))
            count++;
        str++;
    }
    return count;
}

// Validate ASCII-only input
int is_valid_ascii_string(char *str)
{
    while (*str)
    {
        if (!ft_isascii(*str))
            return 0;
        str++;
    }
    return 1;
}
```

## 🔍 Use Cases

### Input Validation
- Checking if user input contains only valid characters
- Validating numeric fields in forms
- Filtering special characters

### Parsing
- Tokenization in lexers/parsers
- Identifying identifier characters vs operators
- String analysis and categorization

### Data Cleaning
- Removing non-printable characters from text
- Converting/filtering extended ASCII
- Sanitizing user input

### Text Processing
- Counting specific character types
- Case-insensitive string comparison
- Character frequency analysis

## 🎓 Key Learnings

1. **Character classification**: Understanding ASCII table organization
2. **Boolean operations**: Using integers as boolean values in C
3. **Range validation**: Efficient boundary checking with && and ||
4. **Input sanitization**: Validating data before processing
5. **Composition**: Building complex checks from simple ones

## 📊 Performance

- **Time Complexity**: O(1) - all functions run in constant time
- **Space Complexity**: O(1) - no additional memory allocation
- **Optimized**: Direct comparison operations, no loops

## 🔗 Related Functions

Character transformation:
- `ft_toupper()` - Convert to uppercase
- `ft_tolower()` - Convert to lowercase

String operations:
- `ft_strlen()` - Can be combined with checks to validate entire strings
- `ft_atoi()` - Uses `ft_isdigit()` internally

## 📚 Standard Library Equivalents

These functions replicate the behavior of:
- `isalpha()` from `<ctype.h>`
- `isdigit()` from `<ctype.h>`
- `isalnum()` from `<ctype.h>`
- `isascii()` from `<ctype.h>`
- `isprint()` from `<ctype.h>`

## ⚠️ Important Notes

### Return Values
- Returns `1` for true (not necessarily `true` keyword)
- Returns `0` for false
- Can be used directly in conditionals: `if (ft_isdigit(c))`

### Type Safety
- Takes `int` parameter (not `char`) for compatibility
- Can handle EOF and extended values
- Follows standard C library conventions

---

[← Back to Main README](../../README.md)
