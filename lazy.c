#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
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

promise * delay(void * function, int args, ...) {
  promise * p = malloc(sizeof(promise));

  if (args < 0 || args > 9) {
    printf("delay: %d arguments unsupported, delay only support 0-9 arguments.\n", args);
    exit(1);
  }
  switch(args) {
  case 0:
    p->info.closure.applier = &apply0; break;
  case 1:
    p->info.closure.applier = &apply1; break;
  case 2:
    p->info.closure.applier = &apply2; break;
  case 3:
    p->info.closure.applier = &apply3; break;
  case 4:
    p->info.closure.applier = &apply4; break;
  case 5:
    p->info.closure.applier = &apply5; break;
  case 6:
    p->info.closure.applier = &apply6; break;
  case 7:
    p->info.closure.applier = &apply7; break;
  case 8:
    p->info.closure.applier = &apply8; break;
  case 9:
    p->info.closure.applier = &apply9; break;
  }
    
  p->info.closure.args = malloc(args*sizeof(void *));
  va_list params; va_start(params, args);
  for(int i = 0; i < args; i++)
    p->info.closure.args[i] = va_arg(params, void *);
  va_end(params);
  
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
