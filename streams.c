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

stream * filter(int (*predicate)(void *), stream * s) {
  if ((*predicate)(s->head)) {
    return streamcons(s->head, delay(&filter, 2, predicate, force(s->tail)));
  }

  return filter(predicate, (stream *) force(s->tail));
}


stream * map(void * (*function)(void *), stream * s) {
  return streamcons(function(head(s)), delay(&map, 2, function, force(s->tail)));
}


stream * iterate(void * (*f)(void *), void * x) {
  return streamcons(x, delay(&iterate, 2, f, f(x)));
}

stream * zip2(void * (*f)(void *, void *), stream * s1, stream * s2) {
  return streamcons( f(head(s1), head(s2)), delay(&zip2, 3, f, tail(s1), tail(s2)));
}


stream * unfold(pair * (*f)(void *), void * acc) {
  pair * p = f(acc);
  void * fst = first(p); void * snd = second(p);
  free(p);
  return streamcons( fst, delay(&unfold, 2, f, snd));
}
