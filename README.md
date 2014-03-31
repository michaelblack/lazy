Lazy
====

A practice implementation of delayed evaluation and streams in c.


`lazy.h` contains functions for creating delayed evaluations.

`delay(void * function, int arity, ...)` - returns a promise to evaluate `function` on the passed variadic arguments at some point later. 0 ≤ arity ≤ 9

`promiseWrap(void * x)` - wraps an already evaluated value in a promise, useful for functions that expect a promise (such as streamcons).

`force(promise * p)` - forces a promise to become evaluated and returns the result. `force` uses memoization so that when it is called again on the same promise, it will not have to recompute the answer.

`streams.h` contains functions for creating and manipulating streams. See the header for more details.
