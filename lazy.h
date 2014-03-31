#ifndef _LAZY_H
#define _LAZY_H

typedef struct promise promise;

int evaluated(promise *);

promise * promiseWrap(void *);
promise * delay(void * function, int arity, ...);
void    * force(promise *);
void    * softForce(promise *);
#endif

/*
  Descriptions:
  
  evaluated - Returns 1 if the promise has been evaluated and 0 otherwise

  promiseWrap - wraps a value in a promise by making that value the evaluation of it
  delay - takes a function and an array of args to later be passed to the function
  force - forces the function stored in the promise to be evaluated and returns the result
  softForce - the same as force but it does not memoize and the promise will still be regarded as unevaluated
 

*/
