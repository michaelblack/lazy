#include <stdlib.h>
#include <stdarg.h>
#include "lazy.h"
#include "apply.h"

struct promise {
  char evaluated;
  union {
    struct {
      void * (*applier)(void *, void **);
      void * function;
      void ** args;
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

void * promiseFunction(promise * p) {
  return p->info.closure.function;
}

void * (*promiseApplier(promise * p))(void *, void **) {
  return p->info.closure.applier;
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

promise * delay(void * function, int arity, ...) {
  promise * p = malloc(sizeof(promise));

  p->info.closure.applier = apply(arity);
  p->info.closure.args = malloc(arity*sizeof(void *));
  va_list args; va_start(args, arity);
  for(int i = 0; i < arity; i++)
    p->info.closure.args[i] = va_arg(args, void *);
  va_end(args);
  
  p->info.closure.function = function;
  
  p->evaluated = 0;
  return p;
}

void * force(promise * p) {
  if(evaluated(p))
    return evaluation(p);

 
  p->info.evaluation = promiseApplier(p)(promiseFunction(p), promiseArgs(p));
  p->evaluated = 1;

  free(p->info.closure.args);
  
  return evaluation(p);
}
