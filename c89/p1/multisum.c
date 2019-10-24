/* PROBLEM 1 [ https://projecteuler.net/problem=1 ]
 * If we list all the natural numbers below 10 that are multiples of 3 or 5,
 * we get 3, 5, 6 and 9. The sum of these multiples is 23.
 * Find the sum of all the multiples of 3 or 5 below 1000.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* TYPE DEFINITIONS */
typedef long double DATA;
#define DATA_FORMAT "%.0Lf"
typedef unsigned long INDEX;
#define INDEX_FORMAT "%lu"

char is_multiple (DATA n, DATA *divisors, INDEX num_divisors);

/* BEGIN PROGRAM LOGIC */

/* is_multiple(n, divisors, num_divisors)
 * Checks if a given number is a multiple of any one of the
 * arbitrary values given in the provided array.
 */
char is_multiple (DATA n, DATA *divisors, INDEX num_divisors)
{ 
  INDEX i; 
  for (i = 0; i < num_divisors; i++) 
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
  /* Variable declarations and setup */
  DATA max, sum, n, *divisors, matches;
  INDEX i, num_divisors;
  sum = 0; matches = 0;

  /* Argument parsing */
  if (argc < 2) { printf("usage: %s [max] [divisor(s)]\n",argv[0]); return 0; }
  max = atof(argv[1]);
  num_divisors = argc-2;
  divisors = (DATA *)calloc(num_divisors,sizeof(DATA));
  for (i = 0; i < num_divisors; i++) divisors[i] = atof(argv[i+2]);

  /* Pre-run statistics */
  printf("Testing range:    0 < n < " DATA_FORMAT "\n",max);
  printf("Data size:        " INDEX_FORMAT " bits\n",(INDEX)sizeof(DATA)*8);

  /* Main computation loop */
  for (n = 1; n < max; n++) 
    if (is_multiple(n,divisors,(INDEX)argc-2)) 
    { matches++; sum += n; }
	
  /* Result return and cleanup */ 
  printf("Matches in range: " DATA_FORMAT "\n",matches);
  printf("Sum of matches:   " DATA_FORMAT "\n",sum);
  free(divisors);
  return 0;
}
