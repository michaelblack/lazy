#include <stdlib.h>
#include "list.h"

list * listcons(void * head, list * tail) {
  list * l = malloc(sizeof(list));
  l->head = head;
  l->tail = tail;
  return l;
}

void foreach(void (*action)(void *), list * l) {
  if(l == NULL)
    return;

  (*action)(l->head);
  foreach(action, l->tail);
}
