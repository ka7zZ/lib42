# String to Integer Conversion Module

Functions for converting between string representations and integer values.

## 📋 Overview

This module handles bidirectional conversion between strings and integers - essential for parsing user input, formatting output, and working with numeric data in text form. These conversions are fundamental to any program that processes text-based data.

## 🎯 Functions

### `ft_atoi`
```c
long ft_atoi(const char *str);
```
**Description**: Converts a string to an integer (ASCII to Integer).

**Features**:
- Skips leading whitespace (space, tab, newline, etc.)
- Handles `+` and `-` signs
- Stops at first non-digit character
- Returns `long` for extended range

**Parameters**:
- `str`: String containing integer representation

**Returns**: The converted integer value

---

### `ft_itoa`
```c
char *ft_itoa(int value);
```
**Description**: Converts an integer to a string (Integer to ASCII).

**Features**:
- Handles negative numbers
- Allocates memory for result
- Special handling for INT_MIN (-2147483648)

**Parameters**:
- `value`: Integer to convert

**Returns**: Newly allocated string (must be freed by caller), or NULL on failure

## 🧠 Programming Concepts

### ASCII to Integer: The Digit Trick
Converting character digits to integers:
```c
char c = '5';              // ASCII value: 53
int digit = c - '0';       // 53 - 48 = 5

// Building multi-digit numbers:
// "123" -> 1*100 + 2*10 + 3*1
int number = 0;
number = number * 10 + (str[0] - '0');  // 0 * 10 + 1 = 1
number = number * 10 + (str[1] - '0');  // 1 * 10 + 2 = 12
number = number * 10 + (str[2] - '0');  // 12 * 10 + 3 = 123
```

### Integer to ASCII: Modulo and Division
Extracting digits from right to left:
```c
int value = 123;

// Extract digits:
123 % 10 = 3  (ones place)
123 / 10 = 12

12 % 10 = 2   (tens place)
12 / 10 = 1

1 % 10 = 1    (hundreds place)
1 / 10 = 0    (done)

// Convert digit to character:
char c = digit + '0';  // 3 + 48 = '3'
```

### Whitespace Handling
Characters considered whitespace:
```c
- ' '  (space, ASCII 32)
- '\t' (tab, ASCII 9)
- '\n' (newline, ASCII 10)
- '\v' (vertical tab, ASCII 11)
- '\f' (form feed, ASCII 12)
- '\r' (carriage return, ASCII 13)
```

### Sign Handling
Processing positive and negative numbers:
```c
int sign = 1;
if (*str == '-')
{
    sign = -1;
    str++;
}
else if (*str == '+')
    str++;

// After conversion:
result *= sign;
```

### Edge Cases

#### INT_MIN Special Case
The value `-2147483648` cannot be converted using `-1 * 2147483648` because `2147483648` exceeds INT_MAX. Solution: hard-code the string.

```c
if (value == -2147483648)
    return (ft_strdup("-2147483648"));
```

#### Overflow Considerations
Standard `atoi` behavior on overflow is undefined. Our implementation returns a `long` to provide extended range, but doesn't detect overflow.

## 💡 Usage Examples

### Parsing User Input
```c
#include "strtoint.h"

// Read numeric input
char input[100];
printf("Enter a number: ");
fgets(input, sizeof(input), stdin);
long number = ft_atoi(input);
printf("You entered: %ld\n", number);

// Parse command-line arguments
int main(int argc, char **argv)
{
    if (argc > 1)
    {
        int value = ft_atoi(argv[1]);
        printf("Argument as integer: %d\n", value);
    }
}
```

### Number Formatting
```c
// Convert integers to strings
int scores[] = {100, 85, 92, 78};
char *str_scores[4];

for (int i = 0; i < 4; i++)
{
    str_scores[i] = ft_itoa(scores[i]);
    printf("Score %d: %s\n", i, str_scores[i]);
    free(str_scores[i]);
}

// Build formatted output
int year = 2024;
char *year_str = ft_itoa(year);
char *message = ft_strjoin("The year is ", year_str);
ft_putendl_fd(message, 1);
free(year_str);
free(message);
```

### Data Validation
```c
// Validate numeric string before conversion
int is_valid_number(char *str)
{
    int i = 0;
    
    // Skip whitespace
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    
    // Check sign
    if (str[i] == '+' || str[i] == '-')
        i++;
    
    // Check if followed by digits
    if (!ft_isdigit(str[i]))
        return (0);
    
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

// Use validation
char *input = "  -42  ";
if (is_valid_number(input))
    int num = ft_atoi(input);
```

### CSV Parsing
```c
// Parse CSV with numeric fields
char *csv = "John,Doe,25,Engineer";
char **fields = ft_split(csv, ',');

char *name = fields[0];      // "John"
char *surname = fields[1];   // "Doe"
int age = ft_atoi(fields[2]); // 25
char *job = fields[3];       // "Engineer"

// Clean up
for (int i = 0; fields[i]; i++)
    free(fields[i]);
free(fields);
```

### Number Range Handling
```c
// Work with different integer ranges
void print_range_info(int value)
{
    char *str = ft_itoa(value);
    printf("Value: %s\n", str);
    
    if (value == -2147483648)
        printf("This is INT_MIN\n");
    else if (value == 2147483647)
        printf("This is INT_MAX\n");
    
    free(str);
}

print_range_info(INT_MIN);
print_range_info(INT_MAX);
print_range_info(0);
```

## 🔍 Parsing Behavior

### `ft_atoi` Parsing Rules

```c
ft_atoi("42")          → 42
ft_atoi("-123")        → -123
ft_atoi("+456")        → 456
ft_atoi("  \t789")     → 789  (skips whitespace)
ft_atoi("12abc")       → 12   (stops at 'a')
ft_atoi("abc")         → 0    (no digits)
ft_atoi("  -  5")      → 0    (space after sign)
ft_atoi("--5")         → 0    (double sign)
ft_atoi("")            → 0    (empty string)
```

### Real-World Parsing Scenarios
```c
// Configuration file parsing
char *port_str = "8080";
int port = ft_atoi(port_str);

// Math expression evaluation
char *expr = "10 + 20";
char **tokens = ft_split(expr, ' ');
int a = ft_atoi(tokens[0]);  // 10
int b = ft_atoi(tokens[2]);  // 20
int result = a + b;          // 30
```

## 🎓 Key Learnings

1. **Character-digit conversion**: Understanding `'0'` to `0` mapping
2. **Build-up vs breakdown**: `atoi` builds number, `itoa` breaks it down
3. **Sign handling**: Managing positive and negative values
4. **Whitespace normalization**: Robust input parsing
5. **Edge case handling**: INT_MIN, INT_MAX, overflow
6. **Memory management**: `itoa` allocates, caller must free
7. **Right-to-left digit extraction**: Using modulo for `itoa`

## 📊 Performance

| Function | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|-------|
| `ft_atoi` | O(n) | O(1) | n = string length |
| `ft_itoa` | O(log n) | O(log n) | n = value magnitude |

## ⚠️ Important Considerations

### Overflow Behavior
```c
// Standard atoi doesn't detect overflow
long result = ft_atoi("999999999999999999");
// Result is undefined for values beyond LONG_MAX
```

### Memory Management for `itoa`
```c
// WRONG - memory leak
printf("%s", ft_itoa(42));

// CORRECT
char *str = ft_itoa(42);
printf("%s", str);
free(str);
```

### Type Safety
```c
// atoi returns long, may need casting
long big_num = ft_atoi("123456789");
int small_num = (int)ft_atoi("42");  // Explicit cast

// Check range before casting
if (big_num >= INT_MIN && big_num <= INT_MAX)
    int safe_num = (int)big_num;
```

## 🔗 Related Functions

String operations:
- `ft_strlen()` - Calculate digit count
- `ft_strdup()` - Used internally by `itoa`
- `ft_split()` - Parse multiple numbers

Character checking:
- `ft_isdigit()` - Validate numeric characters
- `ft_isspace()` - Identify whitespace

## 📚 Standard Library Equivalents

These functions replicate the behavior of:
- `atoi()` from `<stdlib.h>` (returns `int`, ours returns `long`)
- `itoa()` - Non-standard function (not in standard C library)

## 🔬 Advanced Usage

### Custom Number Parsing
```c
// Parse hexadecimal string
long ft_atoi_hex(const char *str)
{
    long result = 0;
    while (*str)
    {
        int digit;
        if (*str >= '0' && *str <= '9')
            digit = *str - '0';
        else if (*str >= 'a' && *str <= 'f')
            digit = *str - 'a' + 10;
        else if (*str >= 'A' && *str <= 'F')
            digit = *str - 'A' + 10;
        else
            break;
        result = result * 16 + digit;
        str++;
    }
    return result;
}

// Usage
long hex = ft_atoi_hex("FF");  // 255
```

---

[← Back to Main README](../../README.md)
