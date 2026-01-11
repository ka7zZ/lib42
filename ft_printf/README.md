# ft_printf - Custom Printf Implementation

> A complete reimplementation of the standard C library's `printf()` function with bonus flag management.

## Project Goal

Recreate the behavior of `printf()` from scratch, handling variable arguments, format specifiers, and complex formatting flags. This project teaches **architectural design**, **string formatting algorithms**, and **modular code structure**.

---

## What I Learned

### Variadic Functions
- Understanding `va_list`, `va_start`, `va_arg`, `va_copy`, `va_end`
- Handling an unknown number of arguments at compile time
- Type safety considerations when extracting arguments

### Format String Parsing
- Building a **state machine** to parse format strings character by character
- Detecting and extracting flags, width, precision, and conversion specifiers
- Handling edge cases like `%%`, incomplete formats, or conflicting flags

### Struct-Based Architecture
- Designed a **flag structure** to store parsing state:
  ```c
  typedef struct s_flags
  {
      int prec;      // Precision value
      int precw;     // Precision width flag
      int space;     // Space before positive numbers
      int sign;      // Force sign (+)
      int left;      // Left-justify (-)
      int zpad;      // Zero-padding (0)
      int alt;       // Alternate form (#)
      int width;     // Minimum field width
  } t_flags;
  ```
- This struct centralizes all formatting information for each conversion

## Technical Implementation

### Algorithm Overview

1. **Parse format string**: Iterate through each character
2. **Detect `%`**: Start flag parsing
3. **Extract flags**: Check for `-`, `0`, `#`, `+`, ` ` in any order
4. **Extract width**: Read numeric field width
5. **Extract precision**: Read `.` followed by precision value
6. **Identify specifier**: Determine conversion type (`c`, `s`, `d`, etc.)
7. **Dispatch to handler**: Call appropriate print function with flags
8. **Apply formatting**: Handler applies width, padding, precision
9. **Return count**: Track total characters printed

### Example Flow
```
Input:   ft_printf("Hello %#08x", 255)
         
Parse:   "Hello " → print directly (6 chars)
         '%' → start format parsing
         '#' → set hash flag
         '0' → set zero flag
         '8' → set width to 8
         'x' → specifier is hex lowercase
         
Dispatch: ft_printpxx(255, flags)
         
Format:  Apply # → prepend "0x"
         Apply width 8 with zero padding
         Result: "0x0000ff"
         
Output:  "Hello 0x0000ff" (total: 15 chars)
Return:  15
```

### Performance Considerations
- Minimized calls to `write()` by buffering when possible
- Efficient number-to-string conversion algorithms
- Avoided unnecessary malloc in format parsing

---

## Architecture Decisions

### Why Separate Files for Each Handler?
- **Maintainability**: Easy to locate and modify specific conversion logic
- **Testing**: Can test each handler independently
- **Scalability**: Adding new specifiers doesn't clutter existing code
- **Code review**: Reviewers can focus on specific functionality

### Why a Flags Struct?
- **Clarity**: All formatting state in one place
- **Passing efficiency**: Single struct parameter instead of many ints
- **Extensibility**: Easy to add new flags without changing function signatures

---

## Common Pitfalls Avoided

1. **Forgetting to initialize flags**: Always zeroed struct before parsing
2. **Buffer overflow in number conversion**: Careful size calculations
3. **Not handling `va_list` properly**: Copied list when needed for multiple passes
4. **Mixing width and precision logic**: Clear separation in code
5. **Memory leaks in temporary buffers**: Freed all allocations

---

## Integration with Libft

This ft_printf is fully integrated into the main library:
- Uses `ft_strlen`, `ft_strchr`, `ft_putchar_fd` from libft core
- Shares compilation through main Makefile
- Exported through `libft.h` header
- Can be used alongside all other library functions

---

## Key Takeaways

1. **Planning matters**: Designing the struct and architecture first saved debugging time
2. **Modular code is maintainable code**: Separation made testing and fixes much easier
3. **Edge cases are everywhere**: Spent 40% of time handling special cases
4. **Documentation helps**: Comments explaining flag precedence were invaluable
5. **Testing early and often**: Incremental testing caught bugs before they compounded

This project transformed my understanding of how formatted output works and taught me to think architecturally about code organization.

---

**Validation**: Passed 42 evaluation with 122/100 (being my first large-scale project involving both code writing and architectural design, I initially misunderstood part of the bonus requirements at the time of submission. However, as I progressed through the Common Core, I later identified and fixed the issue.)
