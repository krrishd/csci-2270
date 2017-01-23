# 1/23

## Complexity

* Upper bound on the runtime of an algorithm.
* We want general performance, don't need exact number.
* O(1) < O(logn) < O(n) < O(n^2) < O(2^n) < O(n!)

## Sorting Algorithms

* **Purpose**: Re-order data to put into ascending or descending order.
  * Easier to find specified value if our data is sorted.
* Different strategies exist.
* **Trade-offs**: Memory and runtime requirements.
  * Algorithms simple to implement might be slow
  * Faster algorithms may be more complex to implement
  * etc

### Bubble sort: Slow & simple

* Elements "bubble" to correct location.

```python

def BubbleSort(A) # A is an array, post-algo A is in ascending order
  for i = 0 to A.end
    for j = 0 to A.end - i - 1
      if (A[j]) > A[j + 1])
        swap = A[j]
        A[j] = A[j + 1]
        A[j + 1] = swap
