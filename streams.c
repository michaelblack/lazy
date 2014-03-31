#include <stdlib.h>
#include "lazy.h"
#include "list.h"
#include "pairs.h"
#include "streams.h"

/*
  Streams
*/

struct stream {
  void * head;
  promise * tail;
};

stream * streamcons(void * head, promise * tail) {
  stream * s = malloc(sizeof(stream));
  s->head = head;
  s->tail = tail;
  return s;
}

void * head(stream * s) {
  return s->head;
}

stream * tail(stream * s) {
  return (stream *)force(s->tail);
}


list * take(int n, stream * s) {
  list * head = listcons(NULL, NULL);
  stream * straveler = s;
  list * ltraveler = head;

  if(n<=0)
    return NULL;
  
  while(1) {

    ltraveler->head = straveler->head;
    straveler = (stream *) force(straveler->tail);

    if (n == 1) {
      break;
    }    

    ltraveler->tail = listcons(NULL,NULL);
    ltraveler = ltraveler->tail;
    n--;
  }
  
  return head;
}

void * filterhelper(void ** args) {
  return (void *) filter(args[0], args[1]);
}

stream * filter(int (*test)(void *), stream * s) {
  if ((*test)(s->head)) {
    void ** args = malloc(sizeof(void*)*2);
    args[0] = test; args[1] = force(s->tail);
    return streamcons(s->head, delay( &filterhelper, args));
  }

  return filter(test, (stream *) force(s->tail));
}

void * maphelper(void ** args) {
  return (void *) map(args[0], args[1]);
}

stream * map(void * (*function)(void *), stream * s) {
  void ** args = malloc(sizeof(void *) * 2);
  args[0] = function; args[1] = (stream *) force(s->tail);
  return streamcons((*function)(s->head), delay(&maphelper, args));
}

void * iteratehelper(void ** args) {
  return (void *) iterate((void * (*)(void *))args[0], args[1]);
}

stream * iterate(void * (*f)(void *), void * x) {
  void ** args = malloc(sizeof(void *) * 2);
  args[0] = f; args[1] = (*f)(x);
  return streamcons(x, delay(&iteratehelper, args));
}

void * zip2helper(void ** args) {
  return zip2(args[0], args[1], args[2]);
}

stream * zip2(void * (*f)(void *, void *), stream * s1, stream * s2) {
  void ** args = malloc(3 * sizeof(void *));
  args[0] = f; args[1] = tail(s1); args[2] = tail(s2);
  return streamcons( (*f)(head(s1), head(s2)), delay(&zip2helper, args));
}


void * unfoldhelper(void ** args) {
  return unfold(args[0], args[1]);
}

stream * unfold(pair * (*f)(void *), void * acc) {
  pair * p = (*f)(acc);
  void ** args = malloc(2 * sizeof(void *));
  args[0] = f; args[1] = second(p);
  return streamcons( first(p), delay( &unfoldhelper, args));
}
  
