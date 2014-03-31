#include <stdlib.h>
#include <stdarg.h>
#include "lazy.h"
#include "apply.h"

/*
  Macros to make refactoring easier
*/

#define evaluated(p) (p->evaluated)
#define promiseFunction(p) (p->info.closure.function)
#define promiseApplier(p) (p->info.closure.applier)
#define promiseArgs(p) (p->info.closure.args)
#define evaluation(p) (p->info.evaluation)

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
  Functions for interacting with promises
*/

promise * promiseWrap(void * x) {
  promise * p = malloc(sizeof(promise));
  evaluation(p) = x;
  evaluated(p) = 1;

  return p;
}

promise * delay(void * function, int arity, ...) {
  promise * p = malloc(sizeof(promise));

  promiseApplier(p) = apply(arity);
  promiseArgs(p) = malloc(arity*sizeof(void *));
  va_list args; va_start(args, arity);
  for(int i = 0; i < arity; i++)
    promiseArgs(p)[i] = va_arg(args, void *);
  va_end(args);
  
  promiseFunction(p) = function;
  
  evaluated(p) = 0;
  return p;
}

void * force(promise * p) {
  if(evaluated(p))
    return evaluation(p);

 
  evaluation(p) = promiseApplier(p)(promiseFunction(p), promiseArgs(p));
  evaluated(p) = 1;

  free(promiseArgs(p));
  
  return evaluation(p);
}
