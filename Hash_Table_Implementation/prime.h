#ifndef PRIME_H_INCLUDED
#define PRIME_H_INCLUDED

/* Checks if passed in int is a prime number
 * @param const int x: the int we are checking if it's prime or not
 * Returns:
 *  1    - prime
 *  0    - not prime
 *  -1   - undefined (i.e. x < 2)
 */
int is_prime(const int x);

/*
 * Returns the next prime after x, or x if x is prime
 */
int next_prime(int x);

#endif // PRIME_H_INCLUDED
