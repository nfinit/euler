/* PROBLEM 1 [ https://projecteuler.net/problem=1 ]
 * If we list all the natural numbers below 10 that are multiples of 3 or 5,
 * we get 3, 5, 6 and 9. The sum of these multiples is 23.
 * Find the sum of all the multiples of 3 or 5 below 1000.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* INCLUDES, DEFINITIONS AND FUNCTION PROTOTYPES */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long double DATA;

char is_multiple (DATA n, DATA *divisors, unsigned long num_divisors);

/* BEGIN PROGRAM LOGIC */

/* is_multiple(n,divisors,num_divisors)
 * Checks if a given number is a multiple of any one (or more) of the
 * arbitrary values given in an array.
 */
char is_multiple (DATA n, DATA *divisors, unsigned long num_divisors)
{ 
  unsigned long i; for (i = 0; i < num_divisors; i++) 
                     if (fmod(n,divisors[i]) == 0) return 1; 
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
  DATA max, sum, n, *divisors, matches;
  unsigned long i, num_divisors, last_sum, overflows;
  sum = 0; overflows = 0; matches = 0;
  if (argc < 2) { printf("usage: %s [max] [divisor(s)]\n",argv[0]); return 0; }

  /* Argument parsing */
  max = atof(argv[1]);
  num_divisors = argc-2;
  divisors = (DATA *)calloc(num_divisors,sizeof(DATA));
  for (i = 0; i < num_divisors; i++) divisors[i] = atof(argv[i+2]);

  /* Print initial statistics */
  printf("Testing range:            0 < n < %.0Lf\n",max);
  printf("Data size:                %lu bits\n",(unsigned long)sizeof(DATA)*8);

  /* Main computation loops */
  for (n = 1; n < max; n++) if (is_multiple(n,divisors,(unsigned long)argc-2)) 
  { last_sum = sum; matches++; sum += n; if (sum < last_sum) overflows++; }
	
  /* Result return and cleanup */ 
  printf("Matching values in range: %.0Lf\n",matches);
  printf("Sum of matching values:   %.0Lf\n",sum);
  if (overflows) printf("WARNING: Overflow events (%lu) detected\n",overflows);
  free(divisors);
  return 0;
}
