#include "alloc.h"
#include "data.h"
#include<stdio.h>
int main (void) {
  int o = 23;
  arena* nar = init_arena(o);
  arena_alloc(nar,LLinit(o));
  arena_alloc(nar,LLinit(o));
  arena_alloc_var(nar,o);
  struct pool* testpool = arena_get(nar,1);
  free(nar);
  free(testpool);
}
