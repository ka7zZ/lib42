# lib42 Function Demonstrations

Complete guide to all functions in the lib42 library with explanations, use cases, and examples.

---

## Table of Contents
1. [Character Transformation](#character-transformation)
2. [Character Checking](#character-checking)
3. [Memory Operations](#memory-operations)
4. [String Operations](#string-operations)
5. [String to Integer Conversion](#string-to-integer-conversion)
6. [Output Functions](#output-functions)
7. [Linked Lists](#linked-lists)
8. [Hash Maps](#hash-maps)
9. [File Reading](#file-reading)
10. [Formatted Output](#formatted-output)

---

## 1. Character Transformation

### `ft_toupper(int c)`
**Purpose:** Converts a lowercase letter to uppercase.

**Implementation:**
```c
if (c >= 'a' && c <= 'z')
    return (c - 32);  // ASCII offset between upper and lower
return (c);
```

**Visual Representation:**
```
ASCII Table (partial):
  ...
  65: [A]  66: [B]  67: [C]  ...  90: [Z]
  ...
  97: [a]  98: [b]  99: [c]  ... 122: [z]
       ↑                              ↑
       |------ 32 positions -------|

Transformation:
  Input:  'a' (97)
          |
          | - 32
          ↓
  Output: 'A' (65)
```

**Key Points:**
- Subtracts 32 from ASCII value ('a' = 97, 'A' = 65)
- Returns unchanged if not lowercase
- Works with ASCII character set

**Example:**
```c
ft_toupper('a');  // Returns 'A' (65)
ft_toupper('Z');  // Returns 'Z' (90) - already uppercase
ft_toupper('5');  // Returns '5' (53) - not a letter
```

---

### `ft_tolower(int c)`
**Purpose:** Converts an uppercase letter to lowercase.

**Implementation:**
```c
if (c >= 'A' && c <= 'Z')
    return (c + 32);  // ASCII offset
return (c);
```

**Visual Representation:**
```
Transformation:
  Input:  'A' (65)
          |
          | + 32
          ↓
  Output: 'a' (97)

Before: [H][E][L][L][O]
After:  [h][e][l][l][o]
```

**Key Points:**
- Adds 32 to ASCII value
- Returns unchanged if not uppercase
- Inverse operation of `ft_toupper`

**Example:**
```c
ft_tolower('A');  // Returns 'a' (97)
ft_tolower('z');  // Returns 'z' (122) - already lowercase
ft_tolower('5');  // Returns '5' (53) - not a letter
```

---

## 2. Character Checking

These functions return `1` (true) or `0` (false).

### `ft_isalpha(int c)`
**Purpose:** Checks if character is alphabetic (A-Z or a-z).

**Implementation:**
```c
return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
```

**Visual Representation:**
```
ASCII Range Check:

  ['A' ... 'Z']  →  1 (true)
   ↑         ↑
   65       90

  ['a' ... 'z']  →  1 (true)
   ↑         ↑
   97      122

Test Cases:
  'A' → [✓] Inside range
  '@' → [✗] Before 'A'
  '5' → [✗] Between ranges
  'z' → [✓] Inside range
```

**Example:**
```c
ft_isalpha('A');  // Returns 1 (true)
ft_isalpha('z');  // Returns 1 (true)
ft_isalpha('5');  // Returns 0 (false)
ft_isalpha('@');  // Returns 0 (false)
```

---

### `ft_isdigit(int c)`
**Purpose:** Checks if character is a decimal digit (0-9).

**Implementation:**
```c
return (c >= '0' && c <= '9');
```

**Visual Representation:**
```
ASCII Range Check:

  ['0' '1' '2' '3' '4' '5' '6' '7' '8' '9']
   48  49  50  51  52  53  54  55  56  57
   ↑                                      ↑
   └──────────── Valid Range ─────────────┘

Test Cases:
  '/'  → [✗] ASCII 47 (before '0')
  '0'  → [✓] ASCII 48
  '5'  → [✓] ASCII 53
  '9'  → [✓] ASCII 57
  ':'  → [✗] ASCII 58 (after '9')
```

**Example:**
```c
ft_isdigit('5');  // Returns 1 (true)
ft_isdigit('0');  // Returns 1 (true)
ft_isdigit('A');  // Returns 0 (false)
```

---

### `ft_isalnum(int c)`
**Purpose:** Checks if character is alphanumeric (letter or digit).

**Implementation:**
```c
return ((c >= '0' && c <= '9') || 
        (c >= 'A' && c <= 'Z') || 
        (c >= 'a' && c <= 'z'));
```

**Visual Representation:**
```
Combination of ft_isalpha + ft_isdigit:

  Valid Ranges:
  [0-9]  [A-Z]  [a-z]
   ↓      ↓      ↓
  [✓]    [✓]    [✓]  → Returns 1

  All Others:
  [@]  [!]  [space]  [ç]
   ↓    ↓     ↓       ↓
  [✗]  [✗]   [✗]     [✗]  → Returns 0
```

**Relationship:** Combines `ft_isalpha` and `ft_isdigit`.

**Example:**
```c
ft_isalnum('A');  // Returns 1 (true)
ft_isalnum('5');  // Returns 1 (true)
ft_isalnum('@');  // Returns 0 (false)
```

---

### `ft_isascii(int c)`
**Purpose:** Checks if character is in ASCII range (0-127).

**Implementation:**
```c
return (c >= 0 && c <= 127);
```

**Visual Representation:**
```
ASCII Table (7-bit):

  0                                                   127
  │───────────────── Valid ASCII ─────────────────│
  [✓]                                                [✓]

  128                                                 255
  │─────────── Extended ASCII (8-bit) ──────────│
  [✗]                                                [✗]

Examples:
   0   → [✓] NUL (null character)
  32   → [✓] Space
  65   → [✓] 'A'
  127  → [✓] DEL
  200  → [✗] Extended
```

**Key Point:** ASCII uses 7 bits (0-127), extended ASCII uses 8 bits (0-255).

**Example:**
```c
ft_isascii(65);   // Returns 1 (true) - 'A'
ft_isascii(127);  // Returns 1 (true) - DEL
ft_isascii(200);  // Returns 0 (false) - extended ASCII
```

---

### `ft_isprint(int c)`
**Purpose:** Checks if character is printable (space to tilde).

**Implementation:**
```c
return (c >= 32 && c <= 126);
```

**Visual Representation:**
```
ASCII Categories:

  0        31  32                             126 127
  │Control│  │──── Printable ────│ DEL
  [✗✗✗✗✗✗]  [✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓✓] [✗]

Printable Range:
  [space][!]["...][A-Z][a-z][0-9][~]
    32    33  ...  65-90 97-122 48-57 126

Non-Printable:
  [\0][\n][\t][ESC][DEL]
    0   10   9   27  127
```

**Key Points:**
- 32 = space (first printable)
- 126 = tilde '~' (last printable)
- Excludes control characters (0-31) and DEL (127)

**Example:**
```c
ft_isprint('A');   // Returns 1 (true)
ft_isprint(' ');   // Returns 1 (true) - space is printable
ft_isprint('\n');  // Returns 0 (false) - newline is control char
ft_isprint('\t');  // Returns 0 (false) - tab is control char
```

---

## 3. Memory Operations

### `ft_memset(void *str, int c, size_t n)`
**Purpose:** Fills memory with a constant byte value.

**Implementation:**
```c
unsigned char *c_str = (unsigned char *)str;
size_t i = 0;
while (i < n)
{
    c_str[i] = (unsigned char)c;
    i++;
}
return (str);
```

**Visual Representation:**
```
Before: [?][?][?][?][?][?][?][?]
                ↓
        ft_memset(buffer, 'A', 8)
                ↓
After:  [A][A][A][A][A][A][A][A]

Partial Fill:
Before: [H][e][l][l][o][!][!][!]
                ↓
        ft_memset(buffer, '*', 5)
                ↓
After:  [*][*][*][*][*][!][!][!]
         ←──── n=5 ────→

```

**Use Cases:**
- Initialize arrays/buffers
- Clear sensitive data
- Set memory blocks to specific value

**Example:**
```c
char buffer[10];
ft_memset(buffer, 'A', 10);
// buffer = "AAAAAAAAAA"

int arr[5];
ft_memset(arr, 0, sizeof(arr));
// All bytes set to 0 (zeros array)
```

---

### `ft_memcpy(void *dst, const void *src, size_t n)`
**Purpose:** Copies `n` bytes from `src` to `dst` (no overlap handling).

**Implementation:**
```c
unsigned char *cast_dst = (unsigned char *)dst;
const unsigned char *cast_src = (const unsigned char *)src;
size_t i = 0;
while (i < n)
{
    cast_dst[i] = cast_src[i];  // Forward copy only
    i++;
}
return (dst);
```

**Visual Representation:**
```
Non-Overlapping Copy (Safe):

src:  [H][e][l][l][o][\0]
       ↓  ↓  ↓  ↓  ↓  ↓
       Copy forward (i=0 → n)
       ↓  ↓  ↓  ↓  ↓  ↓
dst:  [H][e][l][l][o][\0]

Overlapping Copy (DANGER!):

buffer: [a][b][c][d][e][f][g][h]
         ↑────src────→
             ↑────dst────→
         ↓  ↓  ↓  ↓
        [a][b][a][b][a][b][g][h]
                ↑── Corrupted!
```

**Key Limitation:** **Undefined behavior if regions overlap!**

**Example:**
```c
char src[] = "Hello";
char dst[10];
ft_memcpy(dst, src, 6);  // Copies "Hello\0"
// dst = "Hello"
```

---

### `ft_memmove(void *dst, const void *src, size_t n)`
**Purpose:** Copies `n` bytes from `src` to `dst` (handles overlapping regions).

**Implementation:**
```c
unsigned char *cast_dst = (unsigned char *)dst;
const unsigned char *cast_src = (const unsigned char *)src;

if (cast_dst <= cast_src)
{
    // Copy forward (dst before src)
    size_t i = 0;
    while (i < n)
    {
        cast_dst[i] = cast_src[i];
        i++;
    }
}
else
{
    // Copy backward (dst after src) - prevents overwriting
    while (n-- > 0)
        cast_dst[n] = cast_src[n];
}
return (dst);
```

**Visual Representation:**
```
Case 1: dst BEFORE src (Copy Forward)

buffer: [a][b][c][d][e][f][g][h]
         ↑─dst        ↑─src
         ↓  ↓  ↓  ↓
        [e][f][g][h][e][f][g][h]
         ←─────────────→
         Copy i=0→1→2→3
         (Same as memcpy)

Case 2: dst AFTER src (Copy Backward - CRITICAL!)

buffer: [a][b][c][d][e][f][g][h]
         ↑─src    ↑─dst
         
 Step 1: Copy from END first
 buffer: [a][b][c][d][e][f][d][h]
                         ↑────← Copy n-1
         
 Step 2: Continue backward
 buffer: [a][b][c][d][e][c][d][h]
                     ↑────← Copy n-2
         
 Step 3: Backward prevents corruption
 buffer: [a][b][a][b][c][d][e][h]
         ←───────────────────←
         Copy n→0 (backward)

Why Backward Matters:

Forward (WRONG):         Backward (CORRECT):
src: [a][b][c][d][e]     src: [a][b][c][d][e]
      ↓                         ↓  ↓  ↓  ↓  ↓
dst:    [a][?][?][?][?]  dst:    [a][b][c][d][e]
         ↑                   ←────────────────→
Overwrites [b] before     Copies [e] first,
it's read!                preserves all data!
```

**Difference from `memcpy`:**
- Detects overlap direction
- Copies backward when `dst > src` to avoid data loss

**Example with Overlap:**
```c
char buffer[10] = "abcdefghi";

// Shift right by 2 positions
ft_memmove(buffer + 2, buffer, 7);
// buffer = "ababcdefg"

// Using memcpy would cause undefined behavior!
```

---

### `ft_memchr(const void *s, int c, size_t n)`
**Purpose:** Searches for first occurrence of byte `c` in first `n` bytes.

**Implementation:**
```c
unsigned char *res = (unsigned char *)s;
unsigned char ch = (unsigned char)c;
size_t i = 0;

while (i < n)
{
    if (res[i] == ch)
        return (res + i);  // Return pointer to match
    i++;
}
return (NULL);  // Not found
```

**Visual Representation:**
```
Searching for 'W' in first 11 bytes:

data: [H][e][l][l][o][ ][W][o][r][l][d]
       0  1  2  3  4  5  6  7  8  9  10
       ↓  ↓  ↓  ↓  ↓  ↓  ✓
       ✗  ✗  ✗  ✗  ✗  ✗  Found!
                         ↑
                         return pointer here

Searching beyond limit:

data: [H][e][l][l][o][ ][W][o][r][l][d]
       0  1  2  3  4  5  6  7  8  9  10
       ←───── n=5 ───→
       ✗  ✗  ✗  ✗  ✗  stop
                         ↑
                    'W' not searched
                    return NULL
```

**Use Case:** Like `strchr` but works on raw memory (not just strings).

**Example:**
```c
char data[] = "Hello World";
char *ptr = ft_memchr(data, 'W', 11);
// ptr points to "World"

int arr[] = {1, 2, 3, 4};
int *found = ft_memchr(arr, 3, sizeof(arr));
// Finds byte value 3 (may not work as expected for integers)
```

---

### `ft_memcmp(const void *s1, const void *s2, size_t n)`
**Purpose:** Compares first `n` bytes of two memory regions.

**Implementation:**
```c
unsigned char *string1 = (unsigned char *)s1;
unsigned char *string2 = (unsigned char *)s2;
size_t i = 0;

while (i < n && string1[i] == string2[i])
    i++;

if (i == n)
    return (0);  // Equal
return (string1[i] - string2[i]);  // Difference
```

**Visual Representation:**
```
Case 1: Equal Memory
s1: [H][e][l][l][o]
s2: [H][e][l][l][o]
     ✓  ✓  ✓  ✓  ✓  → return 0

Case 2: First Difference
s1: [H][e][l][l][o]
s2: [H][e][l][p][!]
     ✓  ✓  ✓  ✗
              ↑
           'l'(108) - 'p'(112) = -4
           return negative

Case 3: Limited Comparison
s1: [H][e][l][l][o][ ][W][o][r][l][d]
s2: [H][e][l][l][o][ ][U][S][A]
     ←───── n=5 ───→
     ✓  ✓  ✓  ✓  ✓  stop → return 0
                       (difference ignored)
```

**Return Values:**
- `0`: Memory regions are equal
- `< 0`: First differing byte in s1 is less than in s2
- `> 0`: First differing byte in s1 is greater than in s2

**Example:**
```c
char s1[] = "Hello";
char s2[] = "Hello";
char s3[] = "Help";

ft_memcmp(s1, s2, 5);  // Returns 0 (equal)
ft_memcmp(s1, s3, 5);  // Returns negative ('l' < 'p')
ft_memcmp(s3, s1, 5);  // Returns positive ('p' > 'l')
```

---

## 4. String Operations

### Examination Functions

#### `ft_strlen(const char *str)`
**Purpose:** Returns length of string (excluding null terminator).

**Implementation:**
```c
size_t i = 0;
if (!str)
    return (i);
while (str[i])
    i++;
return (i);
```

**Visual Representation:**
```
String: [H][e][l][l][o][\0]
         0  1  2  3  4   5
         ↑              ↑
         |              |
         └─ Count=5 ──┘
         (\0 not counted)

Empty:  [\0]
         0
         Length = 0
```

**Example:**
```c
ft_strlen("Hello");    // Returns 5
ft_strlen("");         // Returns 0
ft_strlen(NULL);       // Returns 0 (safe)
```

---

#### `ft_strchr(const char *str, int ch)`
**Purpose:** Finds **first** occurrence of character in string.

**Implementation:**
```c
char c = ch;
while (*str != c)
{
    if (*str == '\0')
        return (NULL);
    str++;
}
return ((char *)str);  // Return pointer to match
```

**Visual Representation:**
```
Searching for 'W':

str: [H][e][l][l][o][ ][W][o][r][l][d][\0]
      ↓  ↓  ↓  ↓  ↓  ↓  ✓
      ✗  ✗  ✗  ✗  ✗  ✗  Found!
                      ↑
                      Return pointer here
                      (points to "World")

Searching for '\0':

str: [H][e][l][l][o][\0]
      ↓  ↓  ↓  ↓  ↓  ✓
                      ↑
                      Returns pointer to null terminator

Not Found:

str: [H][e][l][l][o][\0]
      ↓  ↓  ↓  ↓  ↓  ↓
      ✗  ✗  ✗  ✗  ✗  reached \0
      (searching for 'z')
      return NULL
```

**Key Point:** Returns pointer to character, not index.

**Example:**
```c
char *str = "Hello World";
char *ptr = ft_strchr(str, 'W');
// ptr points to "World"

ft_strchr(str, 'z');  // Returns NULL (not found)
ft_strchr(str, '\0'); // Returns pointer to null terminator
```

---

#### `ft_strrchr(const char *str, int ch)`
**Purpose:** Finds **last** occurrence of character in string.

**Implementation:**
```c
char *res = (char *)str;
int i = ft_strlen(res);

while (i >= 0)  // Search backward
{
    if (res[i] == (char)ch)
        return (res + i);
    i--;
}
return (NULL);
```

**Visual Representation:**
```
Searching for 'o' (LAST occurrence):

str: [H][e][l][l][o][ ][W][o][r][l][d][\0]
      0  1  2  3  4  5  6  7  8  9  10 11
      ←───────────────────────────────────────←
                      ←──────── Search backward
                      ↑
                   Found 'o' at index 7
                   (not at index 4)

Comparison:

ft_strchr:  Finds FIRST 'o'
str: [H][e][l][l][o][ ][W][o][r][l][d][\0]
                  ↑───────────────→ Returns this

ft_strrchr: Finds LAST 'o'
str: [H][e][l][l][o][ ][W][o][r][l][d][\0]
                          ↑──────────→ Returns this
```

**Difference from `strchr`:** Searches from end to beginning.

**Example:**
```c
char *str = "Hello World";
char *first = ft_strchr(str, 'o');   // Points to "o World"
char *last = ft_strrchr(str, 'o');   // Points to "orld"

ft_strrchr(str, 'H');  // Returns pointer to "Hello World"
```

---

#### `ft_strnstr(const char *haystack, const char *needle, size_t n)`
**Purpose:** Finds first occurrence of substring within first `n` characters.

**Implementation:**
```c
size_t i = 0, j;
if (needle[0] == 0)
    return ((char *)haystack);  // Empty needle matches

while (haystack[i] != '\0' && i < n)
{
    j = 0;
    while (haystack[i + j] == needle[j] && i + j < n)
    {
        if (needle[j + 1] == '\0')
            return ((char *)haystack + i);
        j++;
    }
    i++;
}
return (NULL);
```

**Visual Representation:**
```
Searching for "World" within n=20:

haystack: [H][e][l][l][o][ ][W][o][r][l][d][,]...
           0  1  2  3  4  5  6  7  8  9  10 11
           ←────────── n=20 ──────────────────→
                           ↑
                           Match found!
                           Return pointer here

Searching beyond limit:

haystack: [H][e][l][l][o][ ][W][o][r][l][d][,][ ][U]...
           0  1  2  3  4  5  6  7  8  9  10 11 12 13
           ←────── n=10 ──────→
                           ↑───────── Not searched
                                      (beyond limit)
           Return NULL

Matching Process:

i=6: haystack[6]='W', needle[0]='W' ✓
     haystack[7]='o', needle[1]='o' ✓
     haystack[8]='r', needle[2]='r' ✓
     haystack[9]='l', needle[3]='l' ✓
     haystack[10]='d', needle[4]='d' ✓
     needle[5]='\0' → Match complete!
```

**Key Point:** Limited search scope (only first `n` bytes).

**Example:**
```c
char *str = "Hello World, Hello Universe";
char *ptr = ft_strnstr(str, "World", 20);
// ptr points to "World, Hello Universe"

ft_strnstr(str, "Universe", 15);  // Returns NULL (beyond limit)
ft_strnstr(str, "", 10);          // Returns str (empty needle)
```

---

#### `ft_strncmp(const char *s1, const char *s2, size_t n)`
**Purpose:** Compares up to `n` characters of two strings.

**Implementation:**
```c
unsigned char *cs1 = (unsigned char *)s1;
unsigned char *cs2 = (unsigned char *)s2;
size_t i = 0;

while (i < n && cs1[i] == cs2[i] && cs1[i] != '\0')
    i++;

if (i == n)
    return (0);
return (cs1[i] - cs2[i]);
```

**Visual Representation:**
```
Case 1: Complete Match
s1: [H][e][l][l][o][\0]
s2: [H][e][l][l][o][\0]
     ✓  ✓  ✓  ✓  ✓
     i reaches 5, return 0

Case 2: Partial Match (n=3)
s1: [H][e][l][l][o][\0]
s2: [H][e][l][p][!][\0]
     ✓  ✓  ✓  stop
     ←─ n=3 ─→
     return 0 (first 3 match)

Case 3: Difference Found
s1: [H][e][l][l][o][\0]
s2: [H][e][l][p][!][\0]
     ✓  ✓  ✓  ✗
     ←─── n=5 ───→
              ↑
           'l'(108) - 'p'(112) = -4
           return negative

Case 4: Different Lengths
s1: [H][e][\0]
s2: [H][e][l][l][o][\0]
     ✓  ✓  ✗
     ←─── n=5 ───→
           ↑
        '\0'(0) - 'l'(108) = -108
        return negative
```

**Return Values:**
- `0`: Strings are equal (up to n characters)
- `< 0`: s1 is less than s2
- `> 0`: s1 is greater than s2

**Example:**
```c
ft_strncmp("Hello", "Hello", 5);   // Returns 0 (equal)
ft_strncmp("Hello", "Help", 3);    // Returns 0 (first 3 match)
ft_strncmp("Hello", "Help", 4);    // Returns negative ('l' < 'p')
ft_strncmp("Hello", "He", 5);      // Returns positive ('l' > '\0')
```

---

### Allocation Functions

#### `ft_strdup(const char *s)`
**Purpose:** Duplicates string (allocates new memory).

**Implementation:**
```c
size_t len = ft_strlen(s);
char *res = ft_calloc(len + 1, sizeof(char));
size_t i = 0;
while (i < len)
{
    res[i] = s[i];
    i++;
}
return (res);  // Caller must free!
```

**Visual Representation:**
```
Original (stack/static):
s:    [H][e][l][l][o][\0]
      │  │  │  │  │  │
      ↓  ↓  ↓  ↓  ↓  ↓
      Copy each byte
      ↓  ↓  ↓  ↓  ↓  ↓
res:  [H][e][l][l][o][\0]  (heap - malloc'd)
       ↑
       Must call free(res)!

Memory Layout:

Stack/Data Segment:        Heap:
┌───────────────┐      ┌───────────────┐
│ s: "Hello"     │      │ res: "Hello"  │
└───────────────┘      └───────────────┘
  (read-only)           (modifiable)
  (auto-freed)          (MUST FREE!)
```

**Key Point:** **Must free returned pointer!**

**Example:**
```c
char *original = "Hello";
char *copy = ft_strdup(original);
// copy = "Hello" (different memory)

copy[0] = 'J';
// original = "Hello"
// copy = "Jello"

free(copy);  // Required!
```

---

#### `ft_strjoin(char const *s1, char const *s2)`
**Purpose:** Concatenates two strings into new allocated string.

**Implementation:**
```c
size_t len = ft_strlen(s1) + ft_strlen(s2);
char *res = malloc((len + 1) * sizeof(char));

int i = -1;
while (s1[++i])
    res[i] = s1[i];

int j = 0;
while (s2[j])
    res[i++] = s2[j++];

res[i] = '\0';
return (res);
```

**Visual Representation:**
```
s1:  [H][e][l][l][o][\0]
      ↓  ↓  ↓  ↓  ↓
      Copy to result
      ↓  ↓  ↓  ↓  ↓
res: [H][e][l][l][o][?][?][?][?][?][?][\0]
                     ↑  ↑  ↑  ↑  ↑  ↑
                     Copy from s2
                     ↑  ↑  ↑  ↑  ↑  ↑
s2:                  [ ][W][o][r][l][d][\0]

Final:
res: [H][e][l][l][o][ ][W][o][r][l][d][\0]
     ←──── s1 ────→←─── s2 ───→

Memory Allocation:
  len(s1) + len(s2) + 1
     5    +    6    + 1 = 12 bytes
                       ↑
                 null terminator
```

**Example:**
```c
char *s1 = "Hello ";
char *s2 = "World";
char *joined = ft_strjoin(s1, s2);
// joined = "Hello World"

free(joined);  // Required!
```

---

#### `ft_split(char *str, char c)`
**Purpose:** Splits string into array of strings using delimiter.

**Returns:** NULL-terminated array of strings.

**Visual Representation:**
```
Input String:
str: [H][e][l][l][o][,][W][o][r][l][d][,][T][e][s][t][\0]
                     ↑                   ↑
                delimiter ','       delimiter ','

Splitting Process:
  Step 1: Count words (3 words)
  Step 2: Allocate array[4] (3 words + NULL)
  Step 3: Extract substrings

Result Array:
  ┌───────────────────────────────┐
  │ char **words               │
  └───────────────────────────────┘
       │
       ├───[0] ──→ [H][e][l][l][o][\0]
       │
       ├───[1] ──→ [W][o][r][l][d][\0]
       │
       ├───[2] ──→ [T][e][s][t][\0]
       │
       └───[3] ──→ NULL

Memory Structure:
  words[0] → "Hello"  (malloc'd)
  words[1] → "World"  (malloc'd)
  words[2] → "Test"   (malloc'd)
  words[3] → NULL
  words → array       (malloc'd)

  Must free each string AND the array!
```

**Example:**
```c
char *str = "Hello,World,Test";
char **words = ft_split(str, ',');
// words[0] = "Hello"
// words[1] = "World"
// words[2] = "Test"
// words[3] = NULL

// Free each string and array
int i = 0;
while (words[i])
    free(words[i++]);
free(words);
```

**Use Cases:**
- Parsing CSV data
- Tokenizing input
- Splitting paths

---

## 5. String to Integer Conversion

### `ft_atoi(const char *str)`
**Purpose:** Converts string to integer (ASCII to Integer).

**Implementation:**
```c
long number = 0;
int sign = 1;

// Skip whitespace (space, \t, \n, \v, \f, \r)
while ((*str >= 9 && *str <= 13) || *str == 32)
    str++;

// Handle sign
if (*str == '-')
{
    sign = -1;
    str++;
}
else if (*str == '+')
    str++;

// Convert digits
while (*str >= '0' && *str <= '9')
{
    number = number * 10 + (*str - '0');
    str++;
}

return (number * sign);
```

**Visual Representation:**
```
Input: "  -123abc"

Step 1: Skip Whitespace
[ ][ ][-][1][2][3][a][b][c][\0]
 →  →  ↑
      stop at '-'

Step 2: Handle Sign
[-][1][2][3][a][b][c][\0]
 ↑  ↑
 sign=-1
    start here

Step 3: Convert Digits
[1][2][3][a][b][c][\0]
 ↓  ↓  ↓  ✗

Digit Conversion:
 '1' (ASCII 49) - '0' (ASCII 48) = 1
 '2' (ASCII 50) - '0' (ASCII 48) = 2
 '3' (ASCII 51) - '0' (ASCII 48) = 3

Building Number:
 number = 0
 number = 0 * 10 + 1 = 1
 number = 1 * 10 + 2 = 12
 number = 12 * 10 + 3 = 123

Step 4: Apply Sign
 123 * (-1) = -123

Stop at 'a' (not a digit)
Return: -123
```

**Example:**
```c
ft_atoi("42");        // Returns 42
ft_atoi("-123");      // Returns -123
ft_atoi("  +456");    // Returns 456
ft_atoi("12abc");     // Returns 12 (stops at 'a')
ft_atoi("abc");       // Returns 0
```

---

### `ft_itoa(int value)`
**Purpose:** Converts integer to string (Integer to ASCII).

**Implementation Strategy:**
1. Count digits needed
2. Allocate memory
3. Fill from right to left using modulo

**Visual Representation:**
```
Converting 12345:

Step 1: Count Digits
 12345 → 5 digits
 Allocate: [?][?][?][?][?][\0] (6 bytes)

Step 2: Fill from Right to Left

 value = 12345
 12345 % 10 = 5  →  [?][?][?][?][5][\0]
 12345 / 10 = 1234

 value = 1234
 1234 % 10 = 4   →  [?][?][?][4][5][\0]
 1234 / 10 = 123

 value = 123
 123 % 10 = 3    →  [?][?][3][4][5][\0]
 123 / 10 = 12

 value = 12
 12 % 10 = 2     →  [?][2][3][4][5][\0]
 12 / 10 = 1

 value = 1
 1 % 10 = 1      →  [1][2][3][4][5][\0]
 1 / 10 = 0 (stop)

Converting -42:

Step 1: Count (1 sign + 2 digits = 3)
 Allocate: [?][?][?][\0]

Step 2: Set sign
 [-][?][?][\0]

Step 3: Convert positive value (42)
 42 % 10 = 2  →  [-][?][2][\0]
 42 / 10 = 4
 4 % 10 = 4   →  [-][4][2][\0]
 4 / 10 = 0 (stop)

Result: "-42"

Special Case - INT_MIN (-2147483648):
Cannot use value * -1 (overflow!)
Hard-coded: return ft_strdup("-2147483648")
```

**Example:**
```c
char *str;

str = ft_itoa(42);
// str = "42"
free(str);

str = ft_itoa(-123);
// str = "-123"
free(str);

str = ft_itoa(0);
// str = "0"
free(str);

str = ft_itoa(-2147483648);  // INT_MIN
// str = "-2147483648"
free(str);
```

**Key Point:** Handles INT_MIN (-2147483648) as special case.

---

## 6. Output Functions

These functions write to a file descriptor (`fd`).

### File Descriptors
- `0` = Standard Input (STDIN)
- `1` = Standard Output (STDOUT)
- `2` = Standard Error (STDERR)

### `ft_putchar_fd(char c, int fd)`
**Purpose:** Writes a single character to fd.

**Example:**
```c
ft_putchar_fd('A', 1);     // Prints 'A' to stdout
ft_putchar_fd('!', 2);     // Prints '!' to stderr
```

---

### `ft_putstr_fd(char *s, int fd)`
**Purpose:** Writes a string to fd.

**Example:**
```c
ft_putstr_fd("Hello", 1);        // Prints "Hello" to stdout
ft_putstr_fd("Error!", 2);       // Prints "Error!" to stderr
```

---

### `ft_putendl_fd(char *s, int fd)`
**Purpose:** Writes a string followed by newline to fd.

**Example:**
```c
ft_putendl_fd("Hello", 1);  // Prints "Hello\n"
```

---

### `ft_putnbr_fd(int n, int fd)`
**Purpose:** Writes an integer to fd.

**Example:**
```c
ft_putnbr_fd(42, 1);        // Prints "42"
ft_putnbr_fd(-123, 1);      // Prints "-123"
```

---

## 7. Linked Lists

### Structure
```c
typedef struct s_list
{
    void *content;        // Data pointer
    struct s_list *next;  // Next node
} t_list;
```

**Visual Representation:**
```
Single Node:
┌──────────────────┐
│   t_list node    │
├──────────────────┤
│ content  │  ptr  │ → points to data
│ next     │ NULL  │
└──────────────────┘

Linked List:
┌─────┐    ┌─────┐    ┌─────┐
│  A  │───→│  B  │───→│  C  │───→ NULL
└─────┘    └─────┘    └─────┘
 node1      node2      node3
```

### `ft_lstnew(void *content)`
**Purpose:** Creates a new list node.

**Implementation:**
```c
t_list *node = malloc(sizeof(t_list));
node->content = content;
node->next = NULL;
return (node);
```

**Visual Representation:**
```
Creating a new node:

Input: content pointer (e.g., &data)

Allocate Memory:
┌─────────────────┐
│  t_list node    │
├─────────────────┤
│ content: &data  │  ← Points to your data
│ next: NULL      │  ← Always NULL for new node
└─────────────────┘

Memory:
  Stack:               Heap:
  ┌────────────┐      ┌─────────────────┐
  │ data = 42  │      │ node:           │
  └────────────┘      │  content ─→ &data│
                      │  next = NULL    │
                      └─────────────────┘
```

**Example:**
```c
int data = 42;
t_list *node = ft_lstnew(&data);
// node->content points to data
// node->next is NULL
```

---

### `ft_lstadd_front(t_list **lst, t_list *new)`
**Purpose:** Adds node at the beginning of list.

**Visual Representation:**
```
Before:
   lst
    ↓
   NULL  (empty list)

After adding "World":
   lst
    ↓
  ┌───────┐
  │"World"│───→ NULL
  └───────┘

After adding "Hello":
   lst
    ↓
  ┌───────┐    ┌───────┐
  │"Hello"│───→│"World"│───→ NULL
  └───────┘    └───────┘
   (new)       (old head)

Process:
  Step 1: new->next = *lst
  Step 2: *lst = new
  
  new becomes new head!
```

**Example:**
```c
t_list *list = NULL;
ft_lstadd_front(&list, ft_lstnew("World"));
ft_lstadd_front(&list, ft_lstnew("Hello"));
// list: "Hello" -> "World" -> NULL
```

---

### `ft_lstadd_back(t_list **lst, t_list *new)`
**Purpose:** Adds node at the end of list.

**Visual Representation:**
```
Before:
   lst
    ↓
  ┌───────┐
  │"Hello"│───→ NULL
  └───────┘

After adding "World":
   lst
    ↓
  ┌───────┐    ┌───────┐
  │"Hello"│───→│"World"│───→ NULL
  └───────┘    └───────┘
  (existing)     (new)

Process:
  Step 1: Traverse to last node
  Step 2: last->next = new
  
  new becomes new tail!
  
Multiple additions:
   lst
    ↓
  ┌───┐    ┌───┐    ┌───┐
  │ A │───→│ B │───→│ C │───→ NULL
  └───┘    └───┘    └───┘
                     ↑
                   added last
```

**Example:**
```c
t_list *list = ft_lstnew("Hello");
ft_lstadd_back(&list, ft_lstnew("World"));
// list: "Hello" -> "World" -> NULL
```

---

### `ft_lstsize(t_list *lst)`
**Purpose:** Counts the number of nodes in list.

**Example:**
```c
t_list *list = ft_lstnew("A");
ft_lstadd_back(&list, ft_lstnew("B"));
ft_lstadd_back(&list, ft_lstnew("C"));
int size = ft_lstsize(list);  // Returns 3
```

---

### `ft_lstlast(t_list *lst)`
**Purpose:** Returns the last node of list.

**Example:**
```c
t_list *list = ft_lstnew("A");
ft_lstadd_back(&list, ft_lstnew("B"));
t_list *last = ft_lstlast(list);
// last->content points to "B"
```

---

### `ft_lstdelone(t_list *lst, void (*del)(void*))`
**Purpose:** Deletes a single node using delete function.

**Example:**
```c
void del(void *content)
{
    free(content);
}

char *str = ft_strdup("Hello");
t_list *node = ft_lstnew(str);
ft_lstdelone(node, del);  // Frees str and node
```

---

### `ft_lstclear(t_list **lst, void (*del)(void*))`
**Purpose:** Deletes all nodes in list.

**Example:**
```c
t_list *list = /* ... populated list ... */;
ft_lstclear(&list, del);
// All nodes freed, list is NULL
```

---

### `ft_lstiter(t_list *lst, void (*f)(void*))`
**Purpose:** Applies function to each node's content.

**Example:**
```c
void print_str(void *content)
{
    printf("%s\n", (char *)content);
}

t_list *list = /* ... list of strings ... */;
ft_lstiter(list, print_str);  // Prints each string
```

---

### `ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))`
**Purpose:** Creates new list by applying function to each node.

**Example:**
```c
void *duplicate(void *content)
{
    return (ft_strdup((char *)content));
}

t_list *list = /* ... original list ... */;
t_list *new_list = ft_lstmap(list, duplicate, del);
// new_list is a deep copy with transformed content
```

---

## 8. Hash Maps

The maps module provides a hash map implementation.

### Structure
```c
typedef struct s_map_item
{
    char *key;
    void *value;
} t_map_item;

typedef struct s_map
{
    t_map_item **items;
    size_t size;
    size_t capacity;
} t_map;
```

### `ft_mapnew(void)`
**Purpose:** Creates a new empty hash map.

---

### `ft_mapitem_add(t_map *map, char *key, void *value)`
**Purpose:** Adds or updates a key-value pair.

**Example:**
```c
t_map *map = ft_mapnew();
ft_mapitem_add(map, "name", "John");
ft_mapitem_add(map, "age", "25");
```

---

### `ft_mapitem_index(t_map *map, char *key)`
**Purpose:** Finds the index of a key in the map.

**Returns:** Index or -1 if not found.

---

### `ft_mapitem_del(t_map *map, char *key)`
**Purpose:** Removes a key-value pair from map.

---

### `ft_mapfree(t_map *map)`
**Purpose:** Frees all memory used by map.

---

## 9. File Reading

### `get_next_line(int fd)`
**Purpose:** Reads one line from file descriptor.

**Returns:** Line including `\n`, or NULL at EOF/error.

**Example:**
```c
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

**Use Cases:**
- Reading files line by line
- Processing input incrementally
- Handling standard input

**Key Feature:** Works with any buffer size (defined by BUFFER_SIZE).

---

## 10. Formatted Output

### `ft_printf(const char *format, ...)`
**Purpose:** Custom implementation of printf.

**Supported Format Specifiers:**
- `%c` - Character
- `%s` - String
- `%d` / `%i` - Signed decimal integer
- `%u` - Unsigned decimal integer
- `%x` - Hexadecimal lowercase
- `%X` - Hexadecimal uppercase
- `%p` - Pointer address
- `%%` - Literal percent sign

**Flags:**
- `-` - Left justify
- `0` - Zero padding
- `#` - Alternate form (0x for hex)
- ` ` (space) - Space before positive numbers
- `+` - Always show sign

**Example:**
```c
ft_printf("Hello %s!\n", "World");
// Output: Hello World!

ft_printf("Number: %d\n", 42);
// Output: Number: 42

ft_printf("Hex: %#x\n", 255);
// Output: Hex: 0xff

ft_printf("Pointer: %p\n", ptr);
// Output: Pointer: 0x7fff5fbff8a0

ft_printf("%05d\n", 42);
// Output: 00042

ft_printf("%-10s|\n", "left");
// Output: left      |
```

---

## Summary Tables

### Character Functions Quick Reference
| Function | Purpose | Returns |
|----------|---------|---------|
| `ft_isalpha` | Is letter? | 1 or 0 |
| `ft_isdigit` | Is digit? | 1 or 0 |
| `ft_isalnum` | Is letter or digit? | 1 or 0 |
| `ft_isascii` | Is ASCII (0-127)? | 1 or 0 |
| `ft_isprint` | Is printable (32-126)? | 1 or 0 |
| `ft_toupper` | Convert to uppercase | Character |
| `ft_tolower` | Convert to lowercase | Character |

### Memory Functions Quick Reference
| Function | Purpose | Overlap Safe? |
|----------|---------|---------------|
| `ft_memset` | Fill with byte | N/A |
| `ft_memcpy` | Copy bytes | ❌ NO |
| `ft_memmove` | Copy bytes | ✅ YES |
| `ft_memchr` | Find byte | N/A |
| `ft_memcmp` | Compare bytes | N/A |

### String Search Quick Reference
| Function | What it finds | Direction |
|----------|---------------|-----------|
| `ft_strchr` | First character | Forward |
| `ft_strrchr` | Last character | Backward |
| `ft_strnstr` | First substring | Forward (limited) |

---

## Best Practices

1. **Always free allocated memory:**
   - `ft_strdup`, `ft_strjoin`, `ft_split`, `ft_itoa` return malloc'd memory
   - Use `ft_lstclear` and `ft_mapfree` for complex structures

2. **Check return values:**
   - Functions may return NULL on allocation failure
   - Always validate pointers before dereferencing

3. **Use correct functions for overlap:**
   - Use `ft_memmove` when regions might overlap
   - Use `ft_memcpy` only when certain they don't overlap

4. **Choose right comparison:**
   - Use `ft_strncmp` for strings
   - Use `ft_memcmp` for raw memory

5. **Prefer safer alternatives:**
   - Use `ft_strlcpy` / `ft_strlcat` over `strcpy` / `strcat`
   - They prevent buffer overflows

---

## Function Count by Category

- **Character Operations:** 7 functions
- **Memory Operations:** 5 functions
- **String Operations:** 19 functions
- **Conversion:** 2 functions
- **Output:** 4 functions
- **Linked Lists:** 9 functions
- **Hash Maps:** 9 functions
- **File I/O:** 1 function
- **Formatted Output:** 10+ functions

**Total:** 65+ functions

