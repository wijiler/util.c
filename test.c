#include "arena.h"
#include<stdio.h>
int main (void) {
  int foo = 3;
  struct memReg* treg = newReg(foo); // will give warning,you dont need to &lol it its fine
  printf("%i\n",treg->data[0]); // gives format warning,again its fine
  printf("%i\n",treg->cCapacity);
  regRealloc(treg,9);
  printf("%i\n",treg->cCapacity);
}
