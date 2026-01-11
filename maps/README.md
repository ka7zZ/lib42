# Maps - String Array Management

> Functions for manipulating NULL-terminated string arrays (like `char **envp`).

## Purpose

Working with arrays of strings is common in C (environment variables, command arguments, file lists). These functions provide safe operations for:
- **Dynamic arrays**: Add/remove elements without manual reallocation
- **Array duplication**: Deep copying string arrays
- **Safe indexing**: Finding and replacing specific items
- **Memory management**: Proper cleanup of nested allocations

---

## Function Details

### ft_mapnew
Creates a new map with one element.

### ft_mapsize
Counts elements (like counting `argv` until NULL).

### ft_mapdup
Deep copy - duplicates both array and strings.

### ft_mapfree
Properly frees nested allocations.

### ft_mapitem_add
Adds item to end, handles reallocation.

### ft_mapitem_del
Removes element at index.

### ft_mapitem_replace
Replaces item at specific index.

### ft_mapitem_index
Finds first matching string.

---

## Notes

### Memory Management
All functions that modify maps handle reallocation internally:
- Old strings are freed when replaced
- Arrays are expanded as needed
- `ft_mapfree` cleans everything

### Return Values
- Functions returning `int` return `1` on success, `0` on failure
- `ft_mapitem_index` returns `-1` if not found
- Map functions set pointer to `NULL` after freeing

### NULL Safety
Functions handle NULL maps appropriately:
```c
ft_mapsize(NULL);          // Returns 0
ft_mapitem_index(NULL, "x");  // Returns -1
ft_mapfree(&null_ptr);     // Safe, does nothing
```

---

## Key Takeaways

1. **Maps simplify array management**: No manual reallocation needed
2. **Proper cleanup is automatic**: `ft_mapfree` handles nested memory
3. **Works like shell variables**: Perfect for env vars and argument lists
4. **Deep copies protect data**: `ft_mapdup` creates independent copies
5. **Index-based access**: Can find and modify specific elements

These functions make working with string arrays much safer and easier than manual array manipulation.
