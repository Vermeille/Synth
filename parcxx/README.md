```
                      ___           _____  ____  __
                     | _ \__ _ _ _ / __\ \/ /\ \/ /
                     |  _/ _` | '_| (__ >  <  >  <
                     |_| \__,_|_|  \___/_/\_\/_/\_\
```

[![Build Status](https://travis-ci.org/Vermeille/parcxx.svg?branch=master)](https://travis-ci.org/Vermeille/parcxx)

ParCXX is a parser combinator library to allow writing parser by composition in
a declarative style. It's built following the monadic parser pattern.

Copy the content of src in your code, and include `parsec.h`.

A parser is a function that takes a beginning iterator and an end iterator, and
returns an optional that is either

* Nothing
* A pair of a value and an iterator to what remains to be parsed

Several combination operators are available (`a` and `b` are parsers, `f` is a
function):

* `a & b` parses `a` then `b` and if both of them succeeds, returns a pair
      `(result of a, result of b)`
* `a >> b` parses `a` then `b` and if both of them succeeds, returns only the
      result of b
* `a << b` parses `a` then `b` and if both of them succeeds, returns only the
      result of a
* `a >>= b` monadic bind operator
* `a % f` runs a and if it succeeds, applies f on the value returned
* `a | b` runs a and stops if it succeeds. If it fails, it runs b.
* `parse_while(a, x, f)` runs a until it fails then folds all the results
      with f starting with x
* `parse_while1` same as `parse_while` but forces at least one instance of
      `a` to exist.
* `!a` allows `a` to be present or not. It returns an optional.

Just look at the tests, it should be kinda clear enough.

Performance note: I found `clang++ -std=c++14 -O3` to generate very very
performant code. For instance `parse_uint()`, despite all the crazy lambdas and
combinators etc, is resolved into a very simple assembly loop very similar to
what would be produced by a handwritten `atoi()`. Be fearless if you enable
optimizations. `g++` was not as good though.
