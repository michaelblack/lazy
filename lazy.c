#include <stdlib.h>
#include "lazy.h"

struct promise {
  char evaluated;
  union {
    struct {
      void * (*function)(void ** args);
      void ** (args);
    } closure;
    void * evaluation;
  } info;
};


/*
  Getters to make refactoring easier
*/

int evaluated(promise * p) {
  return (int)p->evaluated;
}

void * (*promiseFunction(promise * p))(void **) {
  return p->info.closure.function;
}

void ** promiseArgs(promise * p) {
  return p->info.closure.args;
}

void * evaluation(promise * p) {
  return p->info.evaluation;
}

/*
  Functions for interacting with promises
*/

promise * promiseWrap(void * a) {
  promise * p = malloc(sizeof(promise));
  p->info.evaluation = a;
  p->evaluated = 1;

  return p;
}

promise * delay(void * (*function)(void ** args), void ** args) {
  promise * p = malloc(sizeof(promise));
  
  p->info.closure.function = function;
  p->info.closure.args = args;
  p->evaluated = 0;
  return p;
}

void * force(promise * p) {
  if(evaluated(p))
    return evaluation(p);

  p->evaluated = 1;
  p->info.evaluation = (*(promiseFunction(p))) (promiseArgs(p));
  return evaluation(p);
}
