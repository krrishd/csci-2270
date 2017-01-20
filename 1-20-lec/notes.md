# Algorithms & Complexity

* Algorithms boil down to I/O + state change within the system.
* First step is to define pre/post-conditions
  * **Correctness**: needs to produce correct result.
  * **Cost**: memory use + runtime (aka time/space complexity).
    * runtime: there's too many variables to use actual runtime (OS, language, etc)
    * count code lines - theoretical runtime, each line cost = 1, actual runtime should be proportional to theoretical.
* **Pre-condition**: Condition that must be true for an algorithm to function as defined.
  * Ex: factorial(n), pre-condition that n > 0.
* **Post-condition**: Expected changes or return value after the algorithm executes.
  * Ex: A = <90, 23, 54>; sort(a); A = <23, 54, 90> is expected.

## Algorithmic Complexity

1. If T(n) includes multiple terms, keep largest term only. eg. n^2 + n, keep n^2
2. Omit any constants.
