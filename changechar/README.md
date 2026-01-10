# Character Transformation Module

Functions for converting characters between uppercase and lowercase.

## 📋 Overview

This module provides simple character case transformation utilities that work with ASCII characters. These are fundamental string manipulation operations used extensively in text processing.

## 🎯 Functions

### `ft_toupper`
```c
int ft_toupper(int c);
```
**Description**: Converts a lowercase letter to uppercase.

**Parameters**:
- `c`: The character to convert (as int)

**Returns**: The uppercase equivalent if `c` is lowercase, otherwise returns `c` unchanged.

**Implementation Detail**: Subtracts 32 from the ASCII value when the character is in the range `'a'` to `'z'`.

---

### `ft_tolower`
```c
int ft_tolower(int c);
```
**Description**: Converts an uppercase letter to lowercase.

**Parameters**:
- `c`: The character to convert (as int)

**Returns**: The lowercase equivalent if `c` is uppercase, otherwise returns `c` unchanged.

**Implementation Detail**: Adds 32 to the ASCII value when the character is in the range `'A'` to `'Z'`.

## 🧠 Programming Concepts

### ASCII Character Encoding
These functions leverage the ASCII table structure where:
- Uppercase letters: `A-Z` (65-90)
- Lowercase letters: `a-z` (97-122)
- Difference: exactly 32 positions

### Conditional Transformation
```
if (character is lowercase)
    return (character - 32)
else
    return (character unchanged)
```

### Why `int` instead of `char`?
Following the standard C library convention:
- Allows returning `EOF` (-1) in stream operations
- Handles extended ASCII and special values
- Maintains compatibility with `<ctype.h>` functions

## 💡 Usage Examples

```c
#include "changechar.h"

// Convert single character
char c = 'a';
char upper = ft_toupper(c);  // 'A'

// Convert string to uppercase
char str[] = "hello world";
int i = 0;
while (str[i])
{
    str[i] = ft_toupper(str[i]);
    i++;
}
// str is now "HELLO WORLD"

// Case-insensitive comparison
char c1 = 'A', c2 = 'a';
if (ft_tolower(c1) == ft_tolower(c2))
    printf("Same letter, different case\n");
```

## 🔍 Edge Cases Handled

- **Non-alphabetic characters**: Returned unchanged (digits, punctuation, spaces)
- **Already correct case**: No modification needed
- **Extended ASCII**: Characters outside standard ASCII range remain unchanged

## 🎓 Key Learnings

1. **ASCII manipulation**: Understanding character encoding at the byte level
2. **Efficient conditionals**: Simple range checks for fast execution
3. **Type awareness**: Understanding int vs char for character functions
4. **Standard library compliance**: Following `<ctype.h>` conventions

## 📊 Performance

- **Time Complexity**: O(1) - constant time operation
- **Space Complexity**: O(1) - no additional memory needed
- **Optimized**: Single conditional check, no loops or function calls

## 🔗 Related Functions

- `ft_isalpha()` - Check if character is alphabetic
- `ft_isupper()` - Check if character is uppercase (not in this library)
- `ft_islower()` - Check if character is lowercase (not in this library)

## 📚 Standard Library Equivalent

These functions replicate the behavior of:
- `toupper()` from `<ctype.h>`
- `tolower()` from `<ctype.h>`

---

[← Back to Main README](../../README.md)
