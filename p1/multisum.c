/* PROBLEM 1 [ https://projecteuler.net/problem=1 ]
 * If we list all the natural numbers below 10 that are multiples of 3 or 5,
 * we get 3, 5, 6 and 9. The sum of these multiples is 23.
 * Find the sum of all the multiples of 3 or 5 below 1000.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
char is_multiple (unsigned long n, unsigned long *values, int num_values);

/* is_multiple(n,values,num_values)
 * Checks if a given number is a multiple of any one (or more) of the
 * values given in an array
 */
char is_multiple (unsigned long n, unsigned long *values, int num_values)
{
  int v;
  for (v = 0; v < num_values; v++) if (n%values[v] == 0) return 1;
  return 0;
}

int main (int argc, char **argv)
{
  return 0;
}
