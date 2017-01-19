def isPrime(n):
  isPrime = True
  for i in range(0, n):
    if (n % i) == 0 and i != 1:
      isPrime = False
  return isPrime