Lazy
====

An implementation of delayed evaluation and streams in c.


lazy.h
------
lazy.h contains four functions that work with 'promises'. A promise is a stucture that holds information on how to call a function with already given arguments.

| Signature | Description |
| --- | --- | 
| `promise * delay(void * function, int arity, ...)` | Returns a promise to evaluate `function` on the passed variadic arguments at some point in the future.  0 ≤ arity ≤ 15 |
| `promise * promiseWrap(void * x)` | Wraps an already evaluated value in a promise. This is useful for when a function expect a promise, but you do not need to delay evaluation (such as `streamcons`). Practically equivalent to `delay( &id, 1, x)`. |
| `void * force(promise * p)` | Forces a promise to become evaluated and returns the result. `force` uses memoization so that when it is called again on the same promise, it will not have to recompute the answer. This is imortant to note if your function has a value based on external state (if this is the case, see `softForce`). |
| `void * softForce(promise * p)` | Does the same thing as force except for two important differences. It does not memoize, and it will throw an error if `force` (not `softForce`) has been previously called on p. This is because the memoization deallocates the arguments passed to a promise, so `softForce` will be unable to reevaluate. |

streams.h
---------
streams.h contains functions for creating and manipulating streams (linked lists where the tails are delayed).

| Signature | Description |
| --------- | ----------- |
| `stream * streamCons(void * head, promise * tail) | Constructs a stream from a value and a promise for the rest of the stream. |
| `void * head(stream * s)` | Fetches the head of a stream. |
| `stream * tail(stream * s)` | Fetches the tail of a stream and forces it. |
| `stream * map(void * (*f)(void *), stream * s)` | Lazily maps the function f to every element of the stream s.|
| `stream * filter(int (*predicate)(void *), stream * s)` | Lazily filters out all elements of s that do not satisfy the predicate. Note that while filter acts lazily, it will none the less perform the filter greedily until at least element that satisfies the predicate is found. If no element satisfies the predicate, filter will halt. |
| `stream * iterate(void * (*f)(void *), void * x)` | Creates a stream of succesive applications of f on x. i.e. `iterate(&f, x)` is `x, f(x), f(f(x)), f(f(f(x))), ...` |
| `stream * repeat(void * x)` | Creates a stream that consists only of x. Practically equivalent to `iterate(&id, x)`.|
| `stream * zip2(void * (*f)(void *, void *), stream * s, stream * t)` | Creates a new stream where corresponding elements of s and t are combined using f. |
| `list * take(int n, stream * s)` | Takes n elements from s and converts them into a list. This function relies on list.h. |
| `stream * drop(int n, stream * s)` | Drops n elements from the stream. i.e. `drop(2, one_through_infinity)` is `3,4,5,6...` |
| `stream * unfold(pair * (*unfolder)(void *), void * accumulator)` | Unfold takes an unfolder function takes the accumulator returns a pair consisting of 1) The value for the next (or initial) element of the stream and 2) the next accumulator to be used. Relies on pairs.h. | 
