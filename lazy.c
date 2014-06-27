#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "lazy.h"
#include "apply.h"

/*
  Acessor macros primarily for easy refactoring.
*/

#define evaluated(p) (p->evaluated)
#define functionOf(p) (p->info.delayed.function)
#define arityOf(p) (p->info.delayed.arity)
#define argsOf(p) (p->info.delayed.args)
#define evaluation(p) (p->info.evaluation)

struct promise {
  char evaluated;
  union {
    struct {
      void * function;
      int arity;
      void ** args;
    } delayed;
    void * evaluation;
  } info;
};

int isEvaluated(promise * p) {
  return (int)(evaluated(p));
}

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


  argsOf(p) = malloc(arity*sizeof(void *));
  va_list args; va_start(args, arity);
  for(int i = 0; i < arity; i++)
    argsOf(p)[i] = va_arg(args, void *);
  va_end(args);
  
  functionOf(p) = function;
  arityOf(p) = arity;
  evaluated(p) = 0;
  return p;
}

void * force(promise * p) {
  if(evaluated(p))
    return evaluation(p);

  free(argsOf(p));  
  evaluation(p) = apply(arityOf(p))(functionOf(p), argsOf(p));
  evaluated(p) = 1;
 
  return evaluation(p);
}

void * softForce(promise * p) {
    if (evaluated(p)) {
        printf("softForce: promise has been previously forced, unable to reevaluate.\n");
        exit(1);
    }
    return apply(arityOf(p))(functionOf(p), argsOf(p));
}

void freePromise(promise * p) {
  if(evaluated(p)) {
    free(p->info.evaluation);
  }
  else {
    free(p->info.delayed.args);
  }
  free(p);
}
