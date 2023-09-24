#define ARENA_H_
#ifdef ARENA_H_
#include<stddef.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include "../data/data.h"
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
void areg(struct pool* pool_v, void* item) {
  pool_v->cCapacity += sizeof(item);
  pool_v->count++;
  LLappend(pool_v->data,item);
}
// arena allocator
typedef struct { struct pool* start,*end; } arena;
// initialize a new arena
arena* init_arena(void* start)
{
  arena* ar = malloc(sizeof(arena) + sizeof(start));
  ar->start->count = 1;
  ar->start->cCapacity = sizeof(start);
  ar->start->data = LLinit(start);
  return ar;
}
void arena_alloc(arena* a, LinkedList* data)
{
  if (a->start->next == NULL)
    {
      a->end = nreg(data);
      a->start->next = a->end;
    }
  else if(a->start->next == a->end)
    {
      struct pool* npool = nreg(data);
      struct pool* oend = nreg(a->end->data);
      a->start->next = oend; a->end = npool; a->start->next->next = a->end;
    }
  else {
    struct pool* lp = a->start->next;
    while (lp != a->end)
      lp = lp->next;

  }
}
#endif // ARENA_H_
