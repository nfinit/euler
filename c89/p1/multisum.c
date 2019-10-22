/* PROBLEM 1 [ https://projecteuler.net/problem=1 ]
 * If we list all the natural numbers below 10 that are multiples of 3 or 5,
 * we get 3, 5, 6 and 9. The sum of these multiples is 23.
 * Find the sum of all the multiples of 3 or 5 below 1000.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* INCLUDES, DEFINITIONS AND FUNCTION PROTOTYPES */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _P1_FAST
typedef unsigned long DATA;
#else
typedef long double DATA;
#endif

#ifndef _P1_FAST
char is_multiple (long double n, int valc, long double *values);
#endif

/* BEGIN PROGRAM LOGIC */

/* is_multiple(n,values,num_values)
 * Checks if a given number is a multiple of any one (or more) of the
 * arbitrary values given in an array.
 */
#ifndef _P1_FAST
char is_multiple (long double n, int valc, long double *values)
{
  int v;
  for (v = 0; v < valc; v++) if (fmod(n,values[v]) == 0) return 1;
  return 0;
}
#endif

/* MAIN FUNCTION
 * Takes in the maximum value as the first argument and arbitrary 
 * target divisors in subsequent arguments. Keeps track of and
 * prints sum of matching numbers when loop is completed.
 */
int main (int argc, char **argv)
{
  /* Variable declaration and argument check */
  DATA max, sum, n, *divisors;
  #ifndef _P1_FAST
  DATA matches;
  #endif
  unsigned long i, num_divisors, last_sum, overflows;
  sum = 0; overflows = 0;
  #ifndef _P1_FAST
  matches = 0;
  #endif
  if (argc < 2) { printf("usage: %s [max] [divisor(s)]\n",argv[0]); return 0; }

  /* Argument parsing */
  #ifdef _P1_FAST
  max = atol(argv[1]);
  #else
  max = atof(argv[1]);
  #endif
  num_divisors = argc-2;
  divisors = malloc(num_divisors*sizeof(DATA));
  for (i = 0; i < num_divisors; i++)
  {
    #ifdef _P1_FAST
    divisors[i] = atol(argv[i+2]);
    #else
    divisors[i] = atof(argv[i+2]);
    #endif
  }
  #ifdef _P1_FAST
  printf("Testing range:            0 < n < %lu\n",max);
  #else
  printf("Testing range:            0 < n < %.0Lf\n",max);
  #endif
  printf("Data size:                %lu bits\n",(unsigned long)sizeof(DATA)*8);

  /* Main computation loop */
  #ifdef _P1_FAST
  for (i = 0; i < num_divisors; i++)
  { last_sum = sum; n = divisors[i]; sum += n*(max/n)*(((max/n)+1)/2); if (sum < last_sum) overflows++; }
  #else
  for (n = 1; n < max; n++) if (is_multiple(n,argc-2,divisors)) 
  { last_sum = sum; matches++; sum += n; if (sum < last_sum) overflows++; }
  #endif
  
  /* Result return and cleanup */ 
  #ifndef _P1_FAST
  printf("Matching values in range: %.0Lf\n",matches);
  printf("Sum of matching values:   %.0Lf\n",sum);
  #else
  printf("Sum of matching values:   %lu\n",sum);
  #endif
  if (overflows) printf("WARNING: Overflow events (%lu) detected\n",overflows);
  free(divisors);
  return 0;
}
