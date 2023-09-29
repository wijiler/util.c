# Util.c
## A collection of useful c tools that I wrote (#10003407084579)
  
  
## alloc/arena.h
a basic arena allocator written in c  
Example usage:
```c++
#include "alloc.h"
int main(void) 
{
    int foo = 6;
    int bar = 7;
    arena* newarena = init_arena(); 
    arena_alloc_var(newarena,foo);
    arena_alloc_var(newarena,bar);
    return 0;
}
```

## misc/string.h
Better standard string.h  
 
## alloc.h
A collection of useful different allocators  

## data.h
A collection of common data structures  

## data/linkedlist.h
linked lists implemented in c  
Example usage:
``` c++
#include "data.h"
int main(void) 
{
    int foo = 6;
    int bar = 7;
    LinkedList* newList = LLinit(foo);
    LLappend(newList,bar);
    return 0;
}
```
