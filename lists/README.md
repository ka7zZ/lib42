# Linked Lists Module

Implementation of singly linked list data structure with comprehensive manipulation functions.

## 📋 Overview

This module provides a complete linked list implementation with functions for creation, traversal, modification, and deletion. Linked lists are fundamental dynamic data structures that allow efficient insertion and deletion operations.

## 📦 Data Structure

```c
typedef struct s_list
{
    void            *content;  // Pointer to any type of data
    struct s_list   *next;     // Pointer to next node
}   t_list;
```

### Visual Representation
```
NULL ← start

After adding nodes:
start → [data1|next] → [data2|next] → [data3|NULL]
        Node 1          Node 2          Node 3
```

## 🎯 Functions

### Creation & Addition

#### `ft_lstnew`
```c
t_list *ft_lstnew(void *content);
```
**Description**: Creates a new node with the given content.

**Returns**: Pointer to new node, or NULL if allocation fails.

**Visual**:
```
ft_lstnew("Hello")

Returns: [Hello|NULL]
```

---

#### `ft_lstadd_front`
```c
void ft_lstadd_front(t_list **lst, t_list *new);
```
**Description**: Adds a new node at the beginning of the list.

**Visual**:
```
Before: *lst → [A|→] → [B|→] → [C|NULL]
        new → [X|?]

After:  *lst → [X|→] → [A|→] → [B|→] → [C|NULL]
```

---

#### `ft_lstadd_back`
```c
void ft_lstadd_back(t_list **lst, t_list *new);
```
**Description**: Adds a new node at the end of the list.

**Visual**:
```
Before: *lst → [A|→] → [B|→] → [C|NULL]
        new → [X|?]

After:  *lst → [A|→] → [B|→] → [C|→] → [X|NULL]
```

---

### Traversal & Measurement

#### `ft_lstsize`
```c
int ft_lstsize(t_list *lst);
```
**Description**: Counts the number of nodes in the list.

**Returns**: Number of nodes.

**Visual**:
```
lst → [A|→] → [B|→] → [C|NULL]
       1       2       3

Returns: 3
```

---

#### `ft_lstlast`
```c
t_list *ft_lstlast(t_list *lst);
```
**Description**: Returns the last node of the list.

**Visual**:
```
lst → [A|→] → [B|→] → [C|NULL]
                        ↑
                    Returns this
```

---

### Deletion

#### `ft_lstdelone`
```c
void ft_lstdelone(t_list *lst, void (*del)(void *));
```
**Description**: Deletes a single node using the given delete function.

**Parameters**:
- `lst`: Node to delete
- `del`: Function to delete content

**Visual**:
```
Before: node → [data|next]

1. del(data)    // Free the content
2. free(node)   // Free the node

After: (node is freed, memory returned to system)
```

---

#### `ft_lstclear`
```c
void ft_lstclear(t_list **lst, void (*del)(void *));
```
**Description**: Deletes and frees all nodes in the list.

**Visual**:
```
Before: *lst → [A|→] → [B|→] → [C|NULL]

Process:
1. del(C), free(C)
2. del(B), free(B)
3. del(A), free(A)

After: *lst = NULL
```

---

### Iteration & Transformation

#### `ft_lstiter`
```c
void ft_lstiter(t_list *lst, void (*f)(void *));
```
**Description**: Applies function f to the content of each node.

**Visual**:
```
lst → [A|→] → [B|→] → [C|NULL]
      ↓       ↓       ↓
     f(A)    f(B)    f(C)
     
(Original list is modified in place)
```

---

#### `ft_lstmap`
```c
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
```
**Description**: Creates a new list by applying function f to each node's content.

**Returns**: New list, or NULL if allocation fails.

**Visual**:
```
Original: lst → [A|→] → [B|→] → [C|NULL]
                 ↓       ↓       ↓
               f(A)    f(B)    f(C)
                 ↓       ↓       ↓
New list:      [A'|→] → [B'|→] → [C'|NULL]

(Original list unchanged)
```

---

## 🧠 Programming Concepts

### Dynamic Data Structures

Unlike arrays, linked lists:
- Grow and shrink dynamically
- Don't need contiguous memory
- Allow O(1) insertion/deletion at known positions

```c
// Array: Fixed size, contiguous
int arr[100];  // Wastes space if not full
               // Can't grow beyond 100

// Linked List: Dynamic, non-contiguous  
t_list *list = NULL;  // Starts empty
ft_lstadd_back(&list, ft_lstnew("item"));  // Grows as needed
```

### Pointer Manipulation

Linked lists require understanding pointer-to-pointer:

```c
// Single pointer: Can modify node content
void modify_content(t_list *node)
{
    node->content = new_data;  // OK
    node = NULL;               // Local change only
}

// Double pointer: Can modify list head
void modify_list(t_list **lst)
{
    *lst = NULL;  // Changes original list pointer
}
```

### Node Traversal Pattern

Standard idiom for iterating through a list:

```c
t_list *current = list;

while (current != NULL)
{
    // Process current->content
    current = current->next;  // Move to next node
}
```

### Memory Management

Each node requires explicit freeing:

```c
// Wrong: Memory leak
t_list *node = ft_lstnew("data");
node = NULL;  // Lost pointer, memory leaked

// Correct: Proper cleanup
t_list *node = ft_lstnew("data");
ft_lstdelone(node, free);  // Content and node freed
```

### Function Pointers

Used for flexible content operations:

```c
// Delete function example
void del_string(void *content)
{
    free(content);
}

// Transform function example
void *duplicate_string(void *content)
{
    return (strdup((char *)content));
}

// Usage
ft_lstclear(&list, del_string);
t_list *new_list = ft_lstmap(list, duplicate_string, del_string);
```

## 💡 Usage Examples

### Creating a List

```c
#include "lists.h"
#include <string.h>

int main(void)
{
    t_list *list = NULL;
    
    // Add elements to back
    ft_lstadd_back(&list, ft_lstnew(strdup("First")));
    ft_lstadd_back(&list, ft_lstnew(strdup("Second")));
    ft_lstadd_back(&list, ft_lstnew(strdup("Third")));
    
    // List: [First] → [Second] → [Third] → NULL
    
    printf("List size: %d\n", ft_lstsize(list));
    // Output: List size: 3
    
    // Cleanup
    ft_lstclear(&list, free);
    return (0);
}
```

### Adding to Front vs Back

```c
t_list *list = NULL;

// Add to back: Maintains order
ft_lstadd_back(&list, ft_lstnew(strdup("A")));
ft_lstadd_back(&list, ft_lstnew(strdup("B")));
ft_lstadd_back(&list, ft_lstnew(strdup("C")));
// Result: [A] → [B] → [C] → NULL

t_list *list2 = NULL;

// Add to front: Reverses order
ft_lstadd_front(&list2, ft_lstnew(strdup("A")));
ft_lstadd_front(&list2, ft_lstnew(strdup("B")));
ft_lstadd_front(&list2, ft_lstnew(strdup("C")));
// Result: [C] → [B] → [A] → NULL
```

### Iterating Through a List

```c
void print_list(t_list *list)
{
    t_list *current = list;
    int index = 0;
    
    while (current != NULL)
    {
        printf("[%d]: %s\n", index, (char *)current->content);
        current = current->next;
        index++;
    }
}

// Usage
t_list *list = /* ... create list ... */;
print_list(list);
// Output:
// [0]: First
// [1]: Second
// [2]: Third
```

### Using ft_lstiter

```c
void print_content(void *content)
{
    printf("- %s\n", (char *)content);
}

void uppercase_content(void *content)
{
    char *str = (char *)content;
    for (int i = 0; str[i]; i++)
        str[i] = toupper(str[i]);
}

// Print all items
ft_lstiter(list, print_content);

// Modify all items to uppercase
ft_lstiter(list, uppercase_content);
```

### Using ft_lstmap

```c
void *duplicate_and_uppercase(void *content)
{
    char *str = (char *)content;
    char *dup = strdup(str);
    
    if (!dup)
        return (NULL);
    
    for (int i = 0; dup[i]; i++)
        dup[i] = toupper(dup[i]);
    
    return (dup);
}

// Create transformed copy
t_list *uppercase_list = ft_lstmap(list, duplicate_and_uppercase, free);

// Original: [hello] → [world] → NULL
// New list: [HELLO] → [WORLD] → NULL
```

### Stack Implementation

```c
// Stack: Last In, First Out (LIFO)
typedef struct s_stack
{
    t_list *top;
} t_stack;

void push(t_stack *stack, void *data)
{
    ft_lstadd_front(&stack->top, ft_lstnew(data));
}

void *pop(t_stack *stack)
{
    if (!stack->top)
        return (NULL);
    
    t_list *node = stack->top;
    void *data = node->content;
    
    stack->top = node->next;
    free(node);  // Don't free content
    
    return (data);
}

// Usage
t_stack stack = {NULL};
push(&stack, "First");
push(&stack, "Second");
push(&stack, "Third");

printf("%s\n", (char *)pop(&stack));  // Third
printf("%s\n", (char *)pop(&stack));  // Second
printf("%s\n", (char *)pop(&stack));  // First
```

### Queue Implementation

```c
// Queue: First In, First Out (FIFO)
typedef struct s_queue
{
    t_list *front;
} t_queue;

void enqueue(t_queue *queue, void *data)
{
    ft_lstadd_back(&queue->front, ft_lstnew(data));
}

void *dequeue(t_queue *queue)
{
    if (!queue->front)
        return (NULL);
    
    t_list *node = queue->front;
    void *data = node->content;
    
    queue->front = node->next;
    free(node);
    
    return (data);
}

// Usage
t_queue queue = {NULL};
enqueue(&queue, "First");
enqueue(&queue, "Second");
enqueue(&queue, "Third");

printf("%s\n", (char *)dequeue(&queue));  // First
printf("%s\n", (char *)dequeue(&queue));  // Second
printf("%s\n", (char *)dequeue(&queue));  // Third
```

### Filtering a List

```c
t_list *filter_list(t_list *list, int (*predicate)(void *))
{
    t_list *filtered = NULL;
    t_list *current = list;
    
    while (current)
    {
        if (predicate(current->content))
        {
            void *dup = strdup((char *)current->content);
            ft_lstadd_back(&filtered, ft_lstnew(dup));
        }
        current = current->next;
    }
    
    return (filtered);
}

// Predicate function
int starts_with_a(void *content)
{
    char *str = (char *)content;
    return (str[0] == 'a' || str[0] == 'A');
}

// Usage
t_list *all = /* list with: apple, banana, avocado, cherry */;
t_list *a_words = filter_list(all, starts_with_a);
// Result: [apple] → [avocado] → NULL
```

## 🔍 Common Use Cases

### Task Management
```c
typedef struct s_task
{
    char *description;
    int priority;
} t_task;

t_list *todo_list = NULL;
ft_lstadd_back(&todo_list, ft_lstnew(create_task("Fix bug", 1)));
ft_lstadd_back(&todo_list, ft_lstnew(create_task("Write docs", 2)));
```

### History/Undo System
```c
t_list *history = NULL;

void record_action(char *action)
{
    ft_lstadd_front(&history, ft_lstnew(strdup(action)));
}

char *undo(void)
{
    if (!history)
        return (NULL);
    
    char *action = (char *)history->content;
    t_list *temp = history;
    history = history->next;
    free(temp);
    
    return (action);
}
```

### Graph Representation (Adjacency List)
```c
typedef struct s_vertex
{
    int id;
    t_list *neighbors;  // List of connected vertices
} t_vertex;

void add_edge(t_vertex *from, t_vertex *to)
{
    ft_lstadd_back(&from->neighbors, ft_lstnew(to));
}
```

## 📊 Performance

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| `ft_lstnew` | O(1) | O(1) |
| `ft_lstadd_front` | O(1) | O(1) |
| `ft_lstadd_back` | O(n) | O(1) |
| `ft_lstsize` | O(n) | O(1) |
| `ft_lstlast` | O(n) | O(1) |
| `ft_lstdelone` | O(1) | O(1) |
| `ft_lstclear` | O(n) | O(1) |
| `ft_lstiter` | O(n) | O(1) |
| `ft_lstmap` | O(n) | O(n) |

### Comparison with Arrays

| Operation | Array | Linked List |
|-----------|-------|-------------|
| Access element | O(1) | O(n) |
| Insert at front | O(n) | O(1) |
| Insert at back | O(1)* | O(n)** |
| Insert at middle | O(n) | O(1)*** |
| Delete at front | O(n) | O(1) |
| Search | O(n) | O(n) |
| Memory | Contiguous | Scattered |

\* Assuming dynamic array with capacity  
\** O(1) if keeping tail pointer  
\*** O(1) if you already have pointer to position

## ⚠️ Important Considerations

### Memory Leaks

```c
// WRONG: Leak - lost access to nodes
t_list *list = create_list();
list = NULL;  // Original list leaked

// CORRECT: Free before reassigning
ft_lstclear(&list, free);
list = NULL;
```

### Double Pointers

```c
// WRONG: Won't modify original list
void add_front_wrong(t_list *lst, t_list *new)
{
    new->next = lst;
    lst = new;  // Only changes local copy
}

// CORRECT: Modifies original
void add_front_correct(t_list **lst, t_list *new)
{
    new->next = *lst;
    *lst = new;  // Changes original through pointer
}
```

### NULL Checks

```c
// Always check for NULL
if (list == NULL)
    return ;

if (ft_lstnew(data) == NULL)
{
    // Handle allocation failure
    ft_lstclear(&list, free);
    return (NULL);
}
```

### Content Ownership

```c
// Who owns the content?
char *str = "static string";
t_list *node = ft_lstnew(str);
// Don't free static string!

char *str2 = strdup("allocated string");
t_list *node2 = ft_lstnew(str2);
ft_lstdelone(node2, free);  // OK to free
```

## 🎓 Key Learnings

1. **Dynamic memory**: Nodes allocated on-demand
2. **Pointer manipulation**: Single and double pointers
3. **Traversal algorithms**: Sequential access patterns
4. **Function pointers**: Generic operations on content
5. **Memory management**: Proper allocation and deallocation
6. **Data structure design**: Trade-offs between lists and arrays

## 🔗 Related Concepts

- **Arrays**: Contiguous, indexed access
- **Double Linked Lists**: Bidirectional traversal
- **Circular Lists**: Last node points to first
- **Skip Lists**: Multiple levels for faster search
- **Trees**: Hierarchical linked structures
- **Graphs**: Multiple connections per node

## 📚 Standard Library Equivalents

The standard C library doesn't have built-in linked lists, but similar functionality exists in:
- C++ `std::list`
- C++ `std::forward_list`
- BSD queue macros (`queue.h`)
- Linux kernel `list.h`

---

[← Back to Main README](../../README.md)
