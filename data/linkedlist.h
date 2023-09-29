#ifndef DATA_H_
#define DATA_H_
#include <stdlib.h>
typedef struct region
{
  struct region* next;
  size_t size;
  void* data;
}
llreg;

typedef struct
{
  llreg* begin;
  int count;
  llreg* end;
} LinkedList;
// never needed by user
llreg* newreg(void* data) {
  llreg* nr = malloc(sizeof(llreg));
  nr->size = sizeof(data);
  nr->data = data;
  nr->next = NULL;
  return nr;
}
/*
 * initialize a linked list
*/
LinkedList* LLinit(void* init) {
  LinkedList* nll = malloc(sizeof(LinkedList));
  nll->begin = newreg(init);
  nll->count = 1; //[0,1]

  return nll;
}
/*
 * Descrip: appends an item on to the end of a linked list
 * Param(LL) = the linked list you want to append to
 * Param(data) = the data you want to append to the end of a linked list
*/
void LLappend(LinkedList* LL,void* data) {
  LL->count++;
  LL->end->next = NULL;
  if(LL->count > 1 )
  {
    llreg* nb = LL->begin->next;
    // traverse until the end
    while (nb->next != NULL)
      nb = nb->next;
    nb->next = newreg(LL->end->data);
    LL->end = newreg(data);
    return;
  }
    LL->begin->next = newreg(data);
    LL->end = newreg(data);
    LL->end->next = NULL;
    return;
}
#endif // DATA_H_
