#ifndef LIST_H
#define LIST_H

typedef struct list list;

struct list {
  void * head;
  list * tail;
};

list * listcons(void *, list *);

void foreach(void (*f)(void *), list *);

#endif
