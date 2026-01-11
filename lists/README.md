# Linked Lists - Dynamic Data Structure Implementation

> A complete implementation of singly linked lists in C, providing fundamental operations for dynamic data management.

## What are linked lists?

A **linked list** is a dynamic data structure where elements (nodes) are connected via pointers, unlike arrays where elements are stored contiguously in memory.

### Visual Representation
```
[data | next] → [data | next] → [data | next] → NULL
  Node 1          Node 2          Node 3
```

---

## Why Linked Lists?

### Advantages
- **Dynamic size**: Grows/shrinks as needed (no fixed capacity)
- **Efficient insertion/deletion**: O(1) at known positions
- **Memory efficiency**: Only allocates space for existing elements
- **Flexible data**: `void *content` allows any data type

### Disadvantages
- **No random access**: Must traverse from head (O(n) for access)
- **Extra memory**: Each node stores a pointer
- **Cache unfriendly**: Nodes may be scattered in memory

---

## Concepts Learned

### Pointer Manipulation
- **Double pointers**: `**lst` to modify the head pointer itself
- **Node linking**: `node->next = new_node`
- **Traversal**: `while (lst) { ... lst = lst->next; }`

### Memory Management
- **Malloc for each node**: `sizeof(t_list)`
- **Separate content freeing**: Using function pointers for flexibility
- **Avoiding leaks**: Freeing content before freeing node

### Functional Programming
- **Higher-order functions**: Functions that take functions as parameters
- **Mapping**: `ft_lstmap` transforms lists without modifying original
- **Iteration**: `ft_lstiter` applies side effects

### Data Structure Design
- **Abstraction**: Hiding implementation details
- **Generic content**: `void *` allows any data type
- **Operations**: Insert, delete, traverse, transform

---

## Common Pitfalls Avoided

1. **Forgetting to update head**: When adding to front, must update `*lst`
2. **Not freeing content**: `free(node)` doesn't free `node->content`
3. **Dereferencing NULL**: Always check `if (lst)` before accessing
4. **Lost references**: Saving `next` before freeing in loops
5. **Double free**: Calling `ft_lstclear` twice on same list
6. **Circular references**: Creating loops (A → B → A)

---

## Key Takeaways

1. **Dynamic structures are powerful**: No size limits like arrays
2. **Function pointers enable flexibility**: Generic delete/transform operations
3. **Memory management is critical**: Every malloc needs a corresponding free
4. **Traversal patterns are fundamental**: Most operations involve iteration
5. **Abstract data types**: Separating interface from implementation

This module provided the foundation for understanding more complex data structures like trees, graphs, and hash tables used in later projects.
