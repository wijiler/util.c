#define ARENA_H_
#ifdef ARENA_H_
#include<stddef.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include "../data.h"
// loosely based on https://github.com/tsoding/arena/blob/master/arena.h

// region of memory
struct pool
{
  struct pool* next;
  size_t count; // count of stuff in the pool
  size_t cCapacity; // current capacity (in bytes)
  LinkedList* data; // linked list of data in pool
};
// NOTE: do not use as enduser
struct pool* nreg(void* start)
{
  struct pool* nr = malloc(sizeof(struct pool));
  nr->count = 1;
  nr->cCapacity = sizeof(LinkedList) + sizeof(start);
  nr->data = LLinit(start);
  return nr;
}
// NOTE: do not use as enduser
struct pool* nreg_ll(LinkedList* start)
{
  struct pool* nr = malloc(sizeof(struct pool));
  nr->count = 1;
  nr->cCapacity = sizeof(LinkedList) + sizeof(start);
  nr->data = start;
  return nr;
}
// NOTE: do not use as enduser
void areg(struct pool* pool_v, void* item) {
  pool_v->cCapacity += sizeof(item);
  pool_v->count++;
  LLappend(pool_v->data,item);
}
// arena allocator
typedef struct { struct pool* start,*end; } arena;
/*
 * Descrip: Intializes an arena allocator
 * Param(start) | void* => the first bit of memory you want to allocate
*/
arena* init_arena(void* start)
{
  arena* ar = malloc(sizeof(arena) + sizeof(start));
  ar->start = nreg(start);
  ar->start->count = 1;
  ar->start->cCapacity = sizeof(start);
  ar->start->data = LLinit(start);
  return ar;
}
/*
 * Descrip: allocates a new pool of memory to an arena allocater
 * Param(a) | arena* => the arena you want to alloc to
 * Param(data) | LinkedList* => the data you want to allocate in the new pool
 */
void arena_alloc(arena* a, LinkedList* data)
{
  if (a->start->next == NULL)
    {
      a->end = nreg_ll(data);
      a->start->next = a->end;
      return;
    }
  else if(a->start->next == a->end)
    {
      struct pool* npool = nreg_ll(data);
      struct pool* oend = nreg_ll(a->end->data);
      a->start->next = oend; a->end = npool; a->start->next->next = a->end;
      return;
    }
    struct pool* lp = a->start->next;
    while (lp != a->end)
      lp = lp->next;
    struct pool* oend = nreg_ll(a->end->data);
    lp->next = oend;
    a->end = nreg_ll(data);
}
/*
 * Descrip => allocates a new pool of memory to an arena allocater
 * Param(a) | arena* => the arena you want to alloc to
 * Param(data) | void* => the variable you want to allocate in the new pool
 */
void arena_alloc_var(arena* a, void* data)
{
  if (a->start->next == NULL)
    {
      a->end = nreg(data);
      a->start->next = a->end;
      return;
    }
  else if(a->start->next == a->end)
    {
      struct pool* npool = nreg(data);
      struct pool* oend = nreg(a->end->data);
      a->start->next = oend; a->end = npool; a->start->next->next = a->end;
      return;
    }
    struct pool* lp = a->start->next;
    while (lp != a->end)
      lp = lp->next;
    struct pool* oend = nreg_ll(a->end->data);
    lp->next = oend;
    a->end = nreg(data);
}
/*
 * Descrip []=> [resizes;adds] |> memory to the specifed pool of an arena
 * Param(a) | arena* => the arena you need to realloc to
 * Param(index) | int => the index of the pool you need to realloc
 * Param(value) | void* => the optional value you want to append to the data
*/
void arena_realloc(arena* a,int index,void* value)
{

}
#endif // ARENA_H_
