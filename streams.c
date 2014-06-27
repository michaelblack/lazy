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

stream * streamCons(void * head, promise * tail) {
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
  if(s==NULL || n < 1) {
    return NULL;
  }
  return listcons(head(s), take(n-1, tail(s)));
}

stream * filter(int (*predicate)(void *), stream * s) {
  if (predicate(s->head)) {
    return streamCons(s->head, delay(&filter, 2, predicate, tail(s)));
  }

  return filter(predicate, (stream *) tail(s));
}


stream * map(void * (*f)(void *), stream * s) {
  return streamCons(f(head(s)), delay(&map, 2, f, tail(s)));
}


stream * iterate(void * (*f)(void *), void * x) {
  return streamCons(x, delay(&iterate, 2, f, f(x)));
}

stream * zip2(void * (*f)(void *, void *), stream * s1, stream * s2) {
  return streamCons( f(head(s1), head(s2)), delay(&zip2, 3, f, tail(s1), tail(s2)));
}


stream * unfold(pair * (*f)(void *), void * acc) {
  pair * p = f(acc);
  void * fst = first(p); void * snd = second(p);
  free(p);
  return streamCons( fst, delay(&unfold, 2, f, snd));
}

stream * unfoldIO(void * (*f)()) {
  return streamCons( f(), delay(&unfoldIO, 1, f));
}

stream * drop(int n, stream * s) {
  if(s == NULL || n == 0) {
    return s;
  }

  return drop(n-1, tail(s));
}

stream * repeat(void * x) {
  return streamCons(x, delay(&repeat, 1, x));
}

void sequence(void (*f)(void *), stream * s) {
  if(s == NULL) {
    return;
  }
  f(s->head);
  sequence(f, tail(s));
}
  

// Not tail recursive :/ should fix
void freeStream(stream * s) {
  free(head(s));
  if (!isEvaluated(s->tail)) {
    freePromise(s->tail);
  }
  else {
    freeStream(tail(s));
  }
  free(s);
}
