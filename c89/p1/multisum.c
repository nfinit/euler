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



#ifdef _P1_FAST
DATA factorial (DATA n);
DATA combination (DATA n, DATA r);
DATA *product_array (DATA *values, unsigned long num_values);
#else
char is_multiple (DATA n, DATA *divisors, unsigned long num_divisors);
#endif

/* BEGIN PROGRAM LOGIC */

#ifdef _P1_FAST
/* factorial(n)
 * Returns the factorial of n. One-line ternary implementation from
 * https://www.geeksforgeeks.org/program-for-factorial-of-a-number/
 * pending later optimization.
 */
DATA factorial (DATA n)
{ return (n==1 || n==0) ? 1: n * factorial(n - 1); }

/* combination(n)
 * Returns the number of possible combinations of r objects
 * from a set of n objects.
 */
DATA combination (DATA n, DATA r)
{ return factorial(n)/(factorial(r)*factorial(n-r)); }
  
/* product_array(values,num_values)
 * Creates an array containing all possible products of every value
 * within the given input. Used to eliminate over-matched numbers
 * when using the fast algorithm.
 */
DATA *product_array (DATA *values, unsigned long num_values)
{
  DATA *products, *temp;
  unsigned long num_products, current_product, n, c,i level, i;
  current_product = 0;
  for (n = 1; n <= num_values; n++) num_products += combination(num_values,n);
  num_products -= num_values;
  products = malloc(num_products*sizeof(DATA));
  temp = malloc((num_values)*sizeof(DATA));
  for (i = 0; i < num_values; i++) temp[i] = values[i];
  for (c = 0; c < num_values-1; c++)
  {
    for (i = 0; i < num_values; i++) temp[i] = values[i];
    for (level = c; level < num_values; level++) 
    {
      for (i = num_values-1; i > level; i--) temp[i] *= values[level];
      for (i = level+1; i < num_values; i++) products[current_product++] = temp[i];
    }
    
  }
  free(temp);
  return products;
}
#else
/* is_multiple(n,divisors,num_divisors)
 * Checks if a given number is a multiple of any one (or more) of the
 * arbitrary values given in an array.
 */
char is_multiple (DATA n, DATA *divisors, unsigned long num_divisors)
{ 
  unsigned long i; for (i = 0; i < num_divisors; i++) if (fmod(n,divisors[i]) == 0) return 1; 
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
  #else
  DATA duplicate_sum, product;
  unsigned long j;
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

  /* Main computation loops */
  #ifdef _P1_FAST
  for (i = 0; i < num_divisors; i++)
  { last_sum = sum; n = divisors[i]; sum += n*(max/n)*(((max/n)+1)/2); if (sum < last_sum) overflows++; }
  #else
  for (n = 1; n < max; n++) if (is_multiple(n,divisors,(unsigned long)argc-2)) 
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
