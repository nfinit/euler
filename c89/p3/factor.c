/* PROBLEM 3 [ https://projecteuler.net/problem=3 ]
 * The prime factors of 13195 are 5, 7, 13 and 29.
 * What is the largest prime factor of the number 600,851,475,143?
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * SOLUTION: Trial division
 * Implements a simple, but laborious method which tests the given number n
 * against every number less than n. 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* TYPE DEFINITIONS */
typedef long double   DATA;
#define DATA_FORMAT   "%.0Lf"

/* OUTPUT STRINGS */
#define USAGE_STR   "usage: %s [value]\n"
#define ARGS_FAIL   "ERROR: %s only operates on positive integers!\n"

/* FUNCTION PROTOTYPES */
void trial_factor (DATA n);

/* BEGIN PROGRAM * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* trial_factor(n)
 * Factors n by trial division and prints the list
 */
void trial_factor (DATA n)
{
  DATA f; f = 2;
  printf("{"); while (n > 1)
  {
    if (fmod(n,f) == 0) { printf(DATA_FORMAT,f); n /= f; if (n > 1) printf (", "); }
    else f++;
  } printf("}\n");
}

/* MAIN FUNCTION
 * Takes in the maximum value as the first argument and arbitrary 
 * target divisors in subsequent arguments. Keeps track of and
 * prints sum of matching numbers when loop is completed.
 */
int main (int argc, char **argv)
{
  /* Variable declarations and setup */
  DATA n;

  /* Argument parsing */
  if (argc < 2) { printf(USAGE_STR,argv[0]); return 0; }
  n = floor(atof(argv[1]));
  if (n < 1) { printf(ARGS_FAIL,argv[0]); return 0; }

  /* Print pre-run statistics */
  printf("Factoring: " DATA_FORMAT "\n",n);

  /* Factor n */
  trial_factor(n);

  /* End of program */ 
  return 0;
}
