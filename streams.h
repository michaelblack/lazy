#ifndef _STREAM_H
#define _STREAM_H

#include "list.h"
#include "pairs.h"

typedef struct stream stream;

stream * streamcons(void *, promise *);
void   * head(stream *);
stream * tail(stream *);
stream * filter(int (*)(void *), stream *);
stream * map(void * (*)(void *), stream *);
stream * iterate(void * (*)(void *), void *);
stream * zip2(void * (*)(void *, void *), stream *, stream *);
stream * unfold(pair * (*)(void *), void *);
list * take(int, stream *);

#endif
/*
  Descriptions:
  
  streamcons - Used for contructing a stream (an infinite list), takes a value and a promise for another stream
  head - returns the head of the stream
  tail - forces the tail of the stream and returns it
  filter - takes a predicate p and filters out all elements of a stream for which p is not true
  map - takes a function and applies it to each element of a stream
  iterate - takes a function f and x builds a stream of x, f x, f f x, f f f x ...
  zip2 - combines two streams into a single one by applying a function to their corresponding elements
  unfold - keeps building a list by passing along an accumulator. Takes a function that takes the accumulator
  and returns a pair of the new value to be in the list and the new accumulator
  take - turns the first n elements of a stream into a list

*/

  
