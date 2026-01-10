# ft_printf Module

Custom implementation of the printf function with support for multiple format specifiers and flags.

## 📋 Overview

`ft_printf` is a recreation of the standard `printf()` function that handles formatted output. This project demonstrates deep understanding of variadic functions, format parsing, type handling, and complex string manipulation.

## 🎯 Function Signature

```c
int ft_printf(const char *format, ...);
```

**Parameters**:
- `format`: Format string with conversion specifiers
- `...`: Variable number of arguments to format

**Returns**: Number of characters printed (or -1 on error)

**Supported Conversions**:
```c
%c - Character
%s - String
%p - Pointer address
%d - Signed decimal integer
%i - Signed integer
%u - Unsigned decimal integer
%x - Unsigned hexadecimal (lowercase)
%X - Unsigned hexadecimal (uppercase)
%% - Literal '%' character
```

**Supported Flags**:
```c
-  : Left-justify within field width
0  : Zero-padding
#  : Alternate form (0x for hex, etc.)
' ': Space before positive numbers
+  : Always show sign
```

## 🧠 Programming Concepts

### Variadic Functions

Functions that accept variable number of arguments:

```c
#include <stdarg.h>

int ft_printf(const char *format, ...)
{
    va_list args;
    
    va_start(args, format);  // Initialize arg list
    
    // Access arguments
    int n = va_arg(args, int);
    char *s = va_arg(args, char *);
    
    va_end(args);  // Cleanup
    
    return (count);
}
```

**Visual**:
```
ft_printf("Value: %d, Name: %s", 42, "Alice");
                                  ↓    ↓
                              va_arg  va_arg
                              (int)   (char*)
```

### Format String Parsing

```c
"Hello %d %s!"
       ↓   ↓
    Parse  Parse
    
Process:
1. "Hello " → Print literally
2. "%d"     → Parse format, print argument
3. " "      → Print literally  
4. "%s"     → Parse format, print argument
5. "!"      → Print literally
```

**State machine**:
```
State: NORMAL
├─ Regular char → Print it
└─ '%' char → Switch to FORMAT state
    
State: FORMAT
├─ Parse flags: -, 0, #, space, +
├─ Parse width: number or *
├─ Parse precision: .number or .*
├─ Parse specifier: c, s, d, i, u, x, X, p
└─ Return to NORMAL state
```

### Flag Processing

```c
"%05d"  → Flag='0', Width=5, Specifier='d'
"%-10s" → Flag='-', Width=10, Specifier='s'
"%#x"   → Flag='#', Specifier='x'
"%+d"   → Flag='+', Specifier='d'
"% d"   → Flag=' ', Specifier='d'
```

**Flag combinations**:
```
ft_printf("%05d", 42);       // "00042"
ft_printf("%-5d", 42);       // "42   "
ft_printf("%+d", 42);        // "+42"
ft_printf("% d", 42);        // " 42"
ft_printf("%#x", 255);       // "0xff"
ft_printf("%#X", 255);       // "0XFF"
```

### Number Conversion

**Decimal to hexadecimal**:
```c
255 (decimal) → FF (hex)

Process:
255 / 16 = 15 remainder 15 → 'F'
15  / 16 = 0  remainder 15 → 'F'

Result: "FF"
```

**Negative numbers** (two's complement):
```c
-1 (signed) → 4294967295 (unsigned with %u)

Because:
-1 in binary (32-bit) = 11111111 11111111 11111111 11111111
Interpreted as unsigned = 2^32 - 1 = 4294967295
```

### Width and Padding

```c
// Right-align with spaces (default)
ft_printf("%5d", 42);
Output: "   42"
         ^^^
      3 spaces

// Left-align with spaces (-)
ft_printf("%-5d", 42);
Output: "42   "
           ^^^
      3 spaces

// Right-align with zeros (0)
ft_printf("%05d", 42);
Output: "00042"
         ^^^
      3 zeros

// Width with strings
ft_printf("%10s", "Hi");
Output: "        Hi"
         ^^^^^^^^
      8 spaces
```

### Pointer Formatting

```c
void *ptr = (void *)0x7fff5fbff710;

ft_printf("%p", ptr);
Output: "0x7fff5fbff710"
         ^^
      Prefix

Implementation:
1. Print "0x" prefix
2. Convert address to hexadecimal (lowercase)
3. Handle NULL: "(nil)" or "0x0"
```

## 💡 Usage Examples

### Basic Printing

```c
#include "ft_printf.h"

int main(void)
{
    int count;
    
    // Character and string
    ft_printf("Char: %c\n", 'A');
    ft_printf("String: %s\n", "Hello");
    
    // Integers
    ft_printf("Decimal: %d\n", 42);
    ft_printf("Integer: %i\n", -42);
    ft_printf("Unsigned: %u\n", 4294967295);
    
    // Hexadecimal
    ft_printf("Hex (lower): %x\n", 255);
    ft_printf("Hex (upper): %X\n", 255);
    
    // Pointer
    int x = 42;
    ft_printf("Address: %p\n", &x);
    
    // Literal %
    ft_printf("Percent: %%\n");
    
    // Return value
    count = ft_printf("Hello, %s!\n", "World");
    ft_printf("Printed %d characters\n", count);
    
    return (0);
}
```

**Output**:
```
Char: A
String: Hello
Decimal: 42
Integer: -42
Unsigned: 4294967295
Hex (lower): ff
Hex (upper): FF
Address: 0x7fff5fbff710
Percent: %
Hello, World!
Printed 14 characters
```

### Flag Usage

```c
// Zero-padding
ft_printf("%05d\n", 42);        // 00042
ft_printf("%08x\n", 255);       // 000000ff

// Left-justify
ft_printf("%-5d\n", 42);        // "42   "
ft_printf("%-10s\n", "Hi");     // "Hi        "

// Sign flags
ft_printf("%+d\n", 42);         // +42
ft_printf("%+d\n", -42);        // -42
ft_printf("% d\n", 42);         // " 42"
ft_printf("% d\n", -42);        // "-42" (- overrides space)

// Alternate form
ft_printf("%#x\n", 255);        // 0xff
ft_printf("%#X\n", 255);        // 0XFF
ft_printf("%#x\n", 0);          // 0 (no prefix for zero)
```

### Format Tables

```c
void print_table(void)
{
    ft_printf("╔════════╦═══════╦═══════╗\n");
    ft_printf("║ %-6s ║ %5s ║ %5s ║\n", "Name", "Age", "Score");
    ft_printf("╠════════╬═══════╬═══════╣\n");
    ft_printf("║ %-6s ║ %5d ║ %5d ║\n", "Alice", 25, 95);
    ft_printf("║ %-6s ║ %5d ║ %5d ║\n", "Bob", 30, 87);
    ft_printf("║ %-6s ║ %5d ║ %5d ║\n", "Carol", 28, 92);
    ft_printf("╚════════╩═══════╩═══════╝\n");
}
```

**Output**:
```
╔════════╦═══════╦═══════╗
║ Name   ║   Age ║ Score ║
╠════════╬═══════╬═══════╣
║ Alice  ║    25 ║    95 ║
║ Bob    ║    30 ║    87 ║
║ Carol  ║    28 ║    92 ║
╚════════╩═══════╩═══════╝
```

### Debug Output

```c
void debug_variable(char *name, void *ptr, char type)
{
    ft_printf("[DEBUG] %s = ", name);
    
    if (type == 'd')
        ft_printf("%d", *(int *)ptr);
    else if (type == 's')
        ft_printf("\"%s\"", *(char **)ptr);
    else if (type == 'p')
        ft_printf("%p", ptr);
    
    ft_printf(" (addr: %p)\n", ptr);
}

// Usage
int x = 42;
char *str = "Hello";
debug_variable("x", &x, 'd');
debug_variable("str", &str, 's');
```

**Output**:
```
[DEBUG] x = 42 (addr: 0x7fff5fbff710)
[DEBUG] str = "Hello" (addr: 0x7fff5fbff718)
```

### Memory Dump

```c
void hexdump(void *ptr, size_t size)
{
    unsigned char *bytes = (unsigned char *)ptr;
    
    ft_printf("Address: %p\n", ptr);
    
    for (size_t i = 0; i < size; i++)
    {
        if (i % 16 == 0)
            ft_printf("%08x: ", (unsigned int)i);
        
        ft_printf("%02x ", bytes[i]);
        
        if ((i + 1) % 16 == 0)
            ft_printf("\n");
    }
    
    if (size % 16 != 0)
        ft_printf("\n");
}

// Usage
int arr[] = {0x12345678, 0xABCDEF00};
hexdump(arr, sizeof(arr));
```

**Output**:
```
Address: 0x7fff5fbff710
00000000: 78 56 34 12 00 ef cd ab
```

### Progress Bar

```c
void show_progress(int current, int total)
{
    int percent = (current * 100) / total;
    int filled = percent / 2;  // 50 chars = 100%
    
    ft_printf("\r[");
    
    for (int i = 0; i < 50; i++)
    {
        if (i < filled)
            ft_printf("█");
        else
            ft_printf("░");
    }
    
    ft_printf("] %3d%%", percent);
}

// Usage
for (int i = 0; i <= 100; i++)
{
    show_progress(i, 100);
    usleep(50000);
}
ft_printf("\n");
```

**Output** (animated):
```
[██████████████████████████░░░░░░░░░░░░░░░░░░░░░░░░]  52%
```

### Colored Output

```c
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

void log_message(char *level, char *message)
{
    if (strcmp(level, "ERROR") == 0)
        ft_printf("%s[ERROR]%s %s\n", RED, RESET, message);
    else if (strcmp(level, "WARNING") == 0)
        ft_printf("%s[WARNING]%s %s\n", YELLOW, RESET, message);
    else if (strcmp(level, "INFO") == 0)
        ft_printf("%s[INFO]%s %s\n", BLUE, RESET, message);
    else if (strcmp(level, "SUCCESS") == 0)
        ft_printf("%s[SUCCESS]%s %s\n", GREEN, RESET, message);
}
```

### Number Formatting

```c
void format_numbers(void)
{
    // Decimal with padding
    ft_printf("ID: %05d\n", 42);           // ID: 00042
    
    // Hex addresses
    ft_printf("Addr: %#010x\n", 0xDEAD);   // Addr: 0x0000dead
    
    // Signed with space
    ft_printf("Temp: % d°C\n", 23);        // Temp:  23°C
    ft_printf("Temp: % d°C\n", -5);        // Temp: -5°C
    
    // Always show sign
    ft_printf("Delta: %+d\n", 10);         // Delta: +10
    ft_printf("Delta: %+d\n", -10);        // Delta: -10
    
    // Large unsigned
    ft_printf("Max: %u\n", 4294967295U);   // Max: 4294967295
}
```

## 🔍 Module Structure

### Core Files

#### `ft_printf.c`
Main function - parses format string and dispatches to handlers

#### `ft_printchar.c`
Handles `%c` - character printing

#### `ft_printstr.c`
Handles `%s` - string printing

#### `ft_printint.c`
Handles `%d` and `%i` - signed integers

#### `ft_printu.c`
Handles `%u` - unsigned integers

#### `ft_printpxx.c`
Handles `%p`, `%x`, `%X` - pointers and hexadecimal

### Helper Files

#### `ft_flagset.c`
Flag parsing and storage

#### `ft_flagadd.c`
Flag combination logic

#### `ft_flagalt.c`
Alternate form flag (`#`)

#### `ft_flagsign.c`
Sign flags (`+` and space)

#### `ft_flagspace.c`
Space flag handling

#### `ft_fill.c`
Width padding (spaces and zeros)

#### `ft_gethex.c`
Decimal to hexadecimal conversion

#### `ft_numlen.c`
Calculate number of digits

#### `ft_memlen.c`
Memory operations for formatting

## 📊 Implementation Details

### Algorithm Overview

```c
int ft_printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    
    va_start(args, format);
    
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            count += handle_conversion(format, args);
        }
        else
        {
            write(1, format, 1);
            count++;
        }
        format++;
    }
    
    va_end(args);
    return (count);
}
```

### Conversion Handling

```c
int handle_conversion(const char *format, va_list args)
{
    t_flags flags = parse_flags(format);
    
    if (flags.specifier == 'c')
        return (print_char(va_arg(args, int), flags));
    else if (flags.specifier == 's')
        return (print_string(va_arg(args, char *), flags));
    else if (flags.specifier == 'd' || flags.specifier == 'i')
        return (print_int(va_arg(args, int), flags));
    else if (flags.specifier == 'u')
        return (print_unsigned(va_arg(args, unsigned int), flags));
    else if (flags.specifier == 'x' || flags.specifier == 'X')
        return (print_hex(va_arg(args, unsigned int), flags));
    else if (flags.specifier == 'p')
        return (print_pointer(va_arg(args, void *), flags));
    
    return (0);
}
```

### Flag Structure

```c
typedef struct s_flags
{
    int     minus;      // Left-justify (-)
    int     zero;       // Zero-padding (0)
    int     hash;       // Alternate form (#)
    int     space;      // Space before positive ( )
    int     plus;       // Always show sign (+)
    int     width;      // Minimum field width
    char    specifier;  // Conversion specifier
}   t_flags;
```

## 📊 Performance

### Time Complexity
- **Parsing**: O(n) where n = format string length
- **Per argument**: O(m) where m = output length for that argument
- **Total**: O(n + Σm) for all arguments

### Space Complexity
- **Stack**: O(1) for va_list and flags
- **Output buffer**: Typically none (direct write)
- **Temporary**: O(k) for number-to-string conversions

## ⚠️ Important Considerations

### Variadic Argument Types

```c
// WRONG: Type mismatch
ft_printf("%d", "string");  // Undefined behavior

// WRONG: Missing argument
ft_printf("%d %s", 42);     // Accesses garbage memory

// CORRECT: Matching types
ft_printf("%d %s", 42, "text");
```

### Character Promotion

```c
// char promoted to int in variadic functions
char c = 'A';
ft_printf("%c", c);  // va_arg(args, int), not char

// Same for short
short s = 42;
ft_printf("%d", s);  // va_arg(args, int), not short
```

### Buffer Overflow Protection

```c
// Static strings are safe
ft_printf("%s", "Hello");

// Dynamic strings need null-termination
char *str = malloc(10);
strcpy(str, "Hello");
ft_printf("%s", str);  // OK - null-terminated

// Dangerous: no null terminator
char buf[5] = {'H', 'e', 'l', 'l', 'o'};
ft_printf("%s", buf);  // Undefined - may read past buffer
```

### Return Value

```c
// Use return value for error checking
int count = ft_printf("Hello");
if (count < 0)
    perror("ft_printf failed");

// Count includes all printed characters
count = ft_printf("Value: %d", 42);  // Returns 10
//                  123456789 10
```

## 🎓 Key Learnings

1. **Variadic functions**: Using `<stdarg.h>` macros
2. **Format parsing**: State machine design
3. **Type safety**: Matching format specifiers to arguments
4. **Number conversion**: Binary/decimal/hexadecimal
5. **Flag handling**: Complex interaction between modifiers
6. **Buffer management**: Efficient string building

## 🔗 Related Concepts

- **scanf**: Input counterpart to printf
- **sprintf**: Print to string buffer
- **fprintf**: Print to file stream
- **snprintf**: Safe bounded printing
- **Custom streams**: Redirecting output

## 📚 Standard Library Equivalents

```c
// Standard printf
printf("Hello %d\n", 42);

// Print to string
sprintf(buffer, "Value: %d", 42);

// Bounded string print
snprintf(buffer, size, "Value: %d", 42);

// Print to file
fprintf(file, "Value: %d\n", 42);

// Print to stderr
fprintf(stderr, "Error: %s\n", msg);
```

## 🚀 Advanced Features (Extended Versions)

Some extended versions support:

### Precision
```c
ft_printf("%.2f", 3.14159);     // 3.14
ft_printf("%.5s", "Hello");     // Hello (first 5 chars)
```

### Width with Variable
```c
int width = 10;
ft_printf("%*d", width, 42);    // "        42"
```

### Long/Short Modifiers
```c
ft_printf("%ld", 123456789L);   // long int
ft_printf("%hd", (short)42);    // short int
```

## 🔬 Testing ft_printf

```c
void test_printf(void)
{
    int std_ret, ft_ret;
    
    // Compare return values
    std_ret = printf("Test: %d\n", 42);
    ft_ret = ft_printf("Test: %d\n", 42);
    
    printf("Standard returned: %d\n", std_ret);
    printf("ft_printf returned: %d\n", ft_ret);
    
    // Test edge cases
    ft_printf("NULL string: %s\n", NULL);
    ft_printf("Zero: %d\n", 0);
    ft_printf("Negative: %d\n", -2147483648);
    ft_printf("Max unsigned: %u\n", 4294967295U);
}
```

---

[← Back to Main README](../../README.md)
