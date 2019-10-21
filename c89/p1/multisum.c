/* PROBLEM 1 [ https://projecteuler.net/problem=1 ]
 * If we list all the natural numbers below 10 that are multiples of 3 or 5,
 * we get 3, 5, 6 and 9. The sum of these multiples is 23.
 * Find the sum of all the multiples of 3 or 5 below 1000.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* INCLUDES AND FUNCTION PROTOTYPES */

#include <stdio.h>
#include <stdlib.h>

char is_multiple (unsigned long n, int valc, unsigned long *values);

/* BEGIN PROGRAM LOGIC */

/* is_multiple(n,values,num_values)
 * Checks if a given number is a multiple of any one (or more) of the
 * arbitrary values given in an array.
 */
char is_multiple (unsigned long n, int valc, unsigned long *values)
{
  int v;
  for (v = 0; v < valc; v++) if (n%values[v] == 0) return 1;
  return 0;
}

/* MAIN FUNCTION
 * Takes in the maximum value as the first argument and arbitrary 
 * target divisors in subsequent arguments. Keeps track of and
 * prints sum of matching numbers when loop is completed.
 */
int main (int argc, char **argv)
{
  /* Variable declaration and argument check */
  unsigned long n, c, s, m, vc, *v;
  m = 0;
  s = 0;
  if (argc < 2) { printf("usage: %s [n] [value(s)]\n",argv[0]); return 0; }

  /* Argument parsing */
  n = atol(argv[1]);
  vc = argc-2;
  v = malloc(vc*sizeof(unsigned long));
  for (c = 0; c < vc; c++) v[c] = atol(argv[c+2]);
  printf("Testing range:            0 < n < %lu\n",n);
  printf("Size of data:             %u bits\n",sizeof(unsigned long)*8);

  /* Main computation loop */
  for (c = 1; c < n; c++) if (is_multiple(c,argc-2,v)) { m++; s += c; }

  /* Result return and cleanup */ 
  printf("Matching values in range: %lu\n",m);
  printf("Sum of matching values:   %lu\n",s);
  return 0;
}
