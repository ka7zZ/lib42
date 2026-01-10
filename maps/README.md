# Hash Map Module

Hash table implementation providing efficient key-value storage with string keys.

## 📋 Overview

This module implements a hash map (hash table) data structure that stores key-value pairs with O(1) average-case lookup, insertion, and deletion. It uses string keys and void pointer values for maximum flexibility.

## 📦 Data Structures

```c
typedef struct s_mapitem
{
    char                *key;
    void                *value;
    struct s_mapitem    *next;    // For collision handling
}   t_mapitem;

typedef struct s_map
{
    t_mapitem   **buckets;        // Array of bucket pointers
    size_t      capacity;         // Number of buckets
    size_t      size;             // Number of items stored
}   t_map;
```

### Visual Representation

```
Hash Map Structure:
                                                                                                                                                                                                                                               
map->buckets[0] → [key1|val1|NULL]
map->buckets[1] → [key2|val2|→] → [key5|val5|NULL]  (collision chain)
map->buckets[2] → NULL
map->buckets[3] → [key3|val3|NULL]
map->buckets[4] → [key4|val4|NULL]
     ...
map->buckets[15] → NULL

Capacity: 16
Size: 5 (number of items)
Load Factor: 5/16 = 0.3125
```

## 🎯 Functions

### Creation & Initialization

#### `ft_mapnew`
```c
t_map *ft_mapnew(size_t capacity);
```
**Description**: Creates a new hash map with the specified initial capacity.

**Parameters**:
- `capacity`: Number of buckets to allocate

**Returns**: Pointer to new map, or NULL if allocation fails.

**Visual**:
```
ft_mapnew(8)

Returns: map → buckets[0..7] (all NULL)
         capacity = 8
         size = 0
```

---

### Item Operations

#### `ft_mapitem_add`
```c
int ft_mapitem_add(t_map *map, char *key, void *value);
```
**Description**: Adds or updates a key-value pair in the map.

**Returns**: 
- `0` on success
- `-1` on failure (allocation error)

**Visual**:
```
Before: map[hash("name")] → NULL

After:  map[hash("name")] → [name|"Alice"|NULL]

If key exists (update):
Before: map[3] → [name|"Bob"|NULL]
After:  map[3] → [name|"Alice"|NULL]  (value replaced)
```

---

#### `ft_mapitem_del`
```c
int ft_mapitem_del(t_map *map, char *key);
```
**Description**: Removes a key-value pair from the map.

**Returns**:
- `0` on success
- `-1` if key not found

**Visual**:
```
Before: map[3] → [key1|val1|→] → [key2|val2|NULL]
                    ↑ (to delete)

After:  map[3] → [key2|val2|NULL]
```

---

#### `ft_mapitem_index`
```c
t_mapitem *ft_mapitem_index(t_map *map, char *key);
```
**Description**: Finds and returns the item with the specified key.

**Returns**: Pointer to item, or NULL if not found.

**Visual**:
```
map[hash("age")] → [name|val|→] → [age|val|NULL]
                                    ↑
                                Returns this
```

---

#### `ft_mapitem_replace`
```c
int ft_mapitem_replace(t_map *map, char *key, void *new_value);
```
**Description**: Replaces the value for an existing key.

**Returns**:
- `0` on success
- `-1` if key not found

---

### Map Operations

#### `ft_mapdup`
```c
t_map *ft_mapdup(t_map *map);
```
**Description**: Creates a deep copy of the map.

**Returns**: Pointer to new map, or NULL on failure.

---

#### `ft_mapfree`
```c
void ft_mapfree(t_map *map, void (*del_value)(void *));
```
**Description**: Frees the map and all its items.

**Parameters**:
- `map`: Map to free
- `del_value`: Function to free values (or NULL)

---

#### `ft_mapsize`
```c
size_t ft_mapsize(t_map *map);
```
**Description**: Returns the number of items in the map.

---

### Utility Functions

#### `ft_map_utils`
Contains hash function and internal helpers:
- Hash calculation (string → bucket index)
- Collision resolution
- Load factor management

---

## 🧠 Programming Concepts

### Hash Functions

A hash function converts keys to array indices:

```c
// Simple hash function (DJB2 algorithm)
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    
    return (hash);
}

// Get bucket index
size_t index = hash(key) % map->capacity;
```

**Key Properties**:
- Deterministic: Same key → same hash
- Uniform distribution: Keys spread across buckets
- Fast computation: O(n) where n = key length

### Collision Resolution

When two keys hash to the same bucket, use **chaining**:

```c
Bucket 3: [key1|val1] → [key2|val2] → [key3|val3] → NULL
          (Linked list handles collisions)
```

**Insertion with collision**:
```c
hash("apple") = 1234 → bucket 4
hash("orange") = 5678 → bucket 4  // Collision!

Solution: Chain them
bucket[4] → [apple|val] → [orange|val] → NULL
```

### Load Factor

```
Load Factor = size / capacity
```

**Example**:
- 100 items in 50 buckets = 2.0 load factor
- Average 2 items per bucket
- Higher load factor → more collisions

**Typical strategy**: Rehash when load factor > 0.75

### Time Complexity

| Operation | Average Case | Worst Case |
|-----------|-------------|-----------|
| Insert | O(1) | O(n) |
| Search | O(1) | O(n) |
| Delete | O(1) | O(n) |

**Worst case** occurs when all keys hash to same bucket (degenerates to linked list).

## 💡 Usage Examples

### Basic Operations

```c
#include "maps.h"
#include <stdio.h>

int main(void)
{
    // Create map with 16 buckets
    t_map *map = ft_mapnew(16);
    
    // Add key-value pairs
    ft_mapitem_add(map, "name", "Alice");
    ft_mapitem_add(map, "age", "25");
    ft_mapitem_add(map, "city", "Paris");
    
    // Retrieve values
    t_mapitem *item = ft_mapitem_index(map, "name");
    if (item)
        printf("Name: %s\n", (char *)item->value);
    
    // Update value
    ft_mapitem_add(map, "age", "26");  // Replaces old value
    
    // Delete item
    ft_mapitem_del(map, "city");
    
    // Check size
    printf("Map size: %zu\n", ft_mapsize(map));
    
    // Cleanup
    ft_mapfree(map, NULL);  // NULL = don't free values (static strings)
    
    return (0);
}
```

### Storing Allocated Data

```c
#include <string.h>

void delete_string(void *value)
{
    free(value);
}

int main(void)
{
    t_map *map = ft_mapnew(16);
    
    // Store dynamically allocated strings
    ft_mapitem_add(map, "name", strdup("Alice"));
    ft_mapitem_add(map, "city", strdup("Paris"));
    
    // Cleanup (free values too)
    ft_mapfree(map, delete_string);
    
    return (0);
}
```

### Configuration Storage

```c
typedef struct s_config
{
    char *key;
    char *value;
} t_config;

t_map *load_config(char *filename)
{
    t_map *config = ft_mapnew(32);
    FILE *file = fopen(filename, "r");
    char line[256];
    
    while (fgets(line, sizeof(line), file))
    {
        // Parse "key=value" format
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");
        
        if (key && value)
            ft_mapitem_add(config, strdup(key), strdup(value));
    }
    
    fclose(file);
    return (config);
}

// Usage
t_map *config = load_config("app.conf");
t_mapitem *item = ft_mapitem_index(config, "server_port");
if (item)
    printf("Port: %s\n", (char *)item->value);
```

### Word Frequency Counter

```c
void increment_count(t_map *map, char *word)
{
    t_mapitem *item = ft_mapitem_index(map, word);
    
    if (item)
    {
        // Word exists, increment count
        int count = *(int *)item->value;
        *(int *)item->value = count + 1;
    }
    else
    {
        // New word
        int *count = malloc(sizeof(int));
        *count = 1;
        ft_mapitem_add(map, strdup(word), count);
    }
}

void count_words(char *text)
{
    t_map *freq = ft_mapnew(64);
    char *word = strtok(text, " \t\n");
    
    while (word)
    {
        increment_count(freq, word);
        word = strtok(NULL, " \t\n");
    }
    
    // Print frequencies
    print_map(freq);
    
    ft_mapfree(freq, free);
}
```

### Caching System

```c
typedef struct s_cache
{
    t_map *data;
    time_t *timestamps;
} t_cache;

void *cache_get(t_cache *cache, char *key)
{
    t_mapitem *item = ft_mapitem_index(cache->data, key);
    
    if (item)
    {
        // Check if expired (5 minute TTL)
        time_t now = time(NULL);
        time_t timestamp = cache->timestamps[/* index */];
        
        if (now - timestamp < 300)
            return (item->value);
        
        // Expired, remove
        ft_mapitem_del(cache->data, key);
    }
    
    return (NULL);
}

void cache_set(t_cache *cache, char *key, void *value)
{
    ft_mapitem_add(cache->data, key, value);
    // Update timestamp...
}
```

### Symbol Table (Variable Storage)

```c
typedef enum e_type
{
    TYPE_INT,
    TYPE_STRING,
    TYPE_FLOAT
} t_type;

typedef struct s_variable
{
    t_type type;
    void *value;
} t_variable;

void set_variable(t_map *vars, char *name, t_type type, void *value)
{
    t_variable *var = malloc(sizeof(t_variable));
    var->type = type;
    var->value = value;
    
    ft_mapitem_add(vars, name, var);
}

void *get_variable(t_map *vars, char *name)
{
    t_mapitem *item = ft_mapitem_index(vars, name);
    
    if (item)
    {
        t_variable *var = (t_variable *)item->value;
        return (var->value);
    }
    
    return (NULL);
}

// Usage
t_map *variables = ft_mapnew(32);

int *x = malloc(sizeof(int));
*x = 42;
set_variable(variables, "x", TYPE_INT, x);

int *value = get_variable(variables, "x");
printf("x = %d\n", *value);  // x = 42
```

### Database-like Queries

```c
// Store user records
typedef struct s_user
{
    char *name;
    int age;
    char *email;
} t_user;

t_map *users = ft_mapnew(100);

// Add users
t_user *alice = create_user("Alice", 25, "alice@example.com");
ft_mapitem_add(users, "alice", alice);

// Lookup by username
t_mapitem *item = ft_mapitem_index(users, "alice");
if (item)
{
    t_user *user = (t_user *)item->value;
    printf("Email: %s\n", user->email);
}
```

## 🔍 Common Use Cases

### Configuration Management
- Store application settings
- Environment variables
- User preferences

### Caching
- Store computed results
- Reduce redundant calculations
- Speed up repeated lookups

### Symbol Tables
- Variable storage in interpreters
- Compiler symbol resolution
- Function name lookup

### Databases
- In-memory key-value store
- Index structures
- Query optimization

### Counting & Statistics
- Word frequency
- Event tracking
- Histogram generation

## 📊 Performance Analysis

### Space Complexity

```
Memory = capacity × sizeof(t_mapitem*) + size × sizeof(t_mapitem)
```

**Example**: 16 buckets, 10 items
- Buckets: 16 × 8 bytes = 128 bytes
- Items: 10 × (8 + 8 + 8) bytes = 240 bytes
- Total: ~368 bytes + key/value memory

### Time Complexity Factors

**Best case** O(1):
- Low load factor (< 0.75)
- Good hash distribution
- Few collisions

**Worst case** O(n):
- High load factor (> 2.0)
- Poor hash function
- All items in one bucket

### Optimization Strategies

1. **Choose good capacity**:
   ```c
   // Prime numbers reduce collisions
   t_map *map = ft_mapnew(53);  // Better than 50
   ```

2. **Monitor load factor**:
   ```c
   float load = (float)map->size / map->capacity;
   if (load > 0.75)
       resize_map(map);  // Rehash with larger capacity
   ```

3. **Use consistent keys**:
   ```c
   // Good: normalized keys
   ft_mapitem_add(map, "user_id", value);
   
   // Bad: mixed formatting
   ft_mapitem_add(map, "userId", value);
   ft_mapitem_add(map, "user_id", value);  // Different key!
   ```

## ⚠️ Important Considerations

### Key Lifetime

```c
// WRONG: Key on stack
void add_item(t_map *map)
{
    char key[10] = "temp";
    ft_mapitem_add(map, key, value);  // Dangling pointer!
}

// CORRECT: Duplicate key
ft_mapitem_add(map, strdup("temp"), value);
```

### Memory Management

```c
// Must free keys AND values
void free_item(void *value)
{
    free(value);
}

// Also need to free keys
t_mapitem *item = /* ... */;
free(item->key);
free_item(item->value);
free(item);
```

### Thread Safety

```c
// Not thread-safe by default
// For concurrent access:
pthread_mutex_t map_lock;

pthread_mutex_lock(&map_lock);
ft_mapitem_add(map, key, value);
pthread_mutex_unlock(&map_lock);
```

### NULL Values

```c
// NULL values are allowed
ft_mapitem_add(map, "optional", NULL);

// Check both item and value
t_mapitem *item = ft_mapitem_index(map, "optional");
if (item && item->value)
    process(item->value);
```

## 🎓 Key Learnings

1. **Hash functions**: Converting keys to indices efficiently
2. **Collision resolution**: Handling duplicate hash values
3. **Load factor**: Balancing speed vs space
4. **Amortized complexity**: Average O(1) operations
5. **Memory management**: Managing keys and values separately
6. **Data structure design**: Trade-offs and optimization

## 🔗 Related Concepts

- **Arrays**: Direct indexing (no hashing needed)
- **Binary Search Trees**: O(log n) operations, ordered
- **Tries**: Prefix-based key storage
- **Bloom Filters**: Probabilistic membership testing
- **Hash Sets**: Keys only, no values

## 📚 Standard Library Equivalents

- C++ `std::unordered_map`
- Java `HashMap`
- Python `dict`
- Ruby `Hash`
- JavaScript `Object` / `Map`

---

[← Back to Main README](../../README.md)
