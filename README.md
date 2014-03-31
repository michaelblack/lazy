Lazy
====

An implementation of delayed evaluation and streams in c.


lazy.h
------
lazy.h contains three functions that work with 'promises'. A promise is a stucture that holds information on how to call a function with already given arguments.

`promise * delay(void * function, int arity, ...)` - Returns a promise to evaluate `function` on the passed variadic arguments at some point in the future. 0 ≤ arity ≤ 15

`promise * promiseWrap(void * x)` - Wraps an already evaluated value in a promise. This is useful for when a function expect a promise, but you do not need to delay evaluation (such as `streamcons`). Practically equivalent to `delay( &id, 1, x)`.

`void * force(promise * p)` - Forces a promise to become evaluated and returns the result. `force` uses memoization so that when it is called again on the same promise, it will not have to recompute the answer. This is imortant to note if your function has a value based on external state!


streams.h
---------
streams.h contains functions for creating and manipulating streams (linked lists where the tails are delayed).
See the header for more details.
