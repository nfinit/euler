/* PROBLEM 1 [ https://projecteuler.net/problem=1 ]
 * If we list all the natural numbers below 10 that are multiples of 3 or 5,
 * we get 3, 5, 6 and 9. The sum of these multiples is 23.
 * Find the sum of all the multiples of 3 or 5 below 1000.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * SOLUTION: Summation function
 * This solution implements a fast summation taking advantage of the
 * arithmetic sequence present in the set of all values divisible by n in
 * a given range. This program accepts arbitrary maximums and arbitrary 
 * sets of positive integer arguments, compensating for duplicate matches 
 * by eliminating sums of values divisible by products of the input set as
 * well as optimizing the input set itself.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* TYPE DEFINITIONS */
typedef long double DATA;
#define DATA_FORMAT  "%.0Lf"
typedef unsigned long INDEX;
#define INDEX_FORMAT "%lu"

/* FUNCTION PROTOTYPES */
char is_multiple (DATA n, DATA *set, INDEX set_size);
DATA factorial (DATA n);
DATA combination (DATA n, DATA r);
DATA *optimize_divisors (DATA *set, INDEX *set_size);
DATA *product_table (DATA *set, INDEX set_size, INDEX *set_products);

/* BEGIN PROGRAM * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* is_multiple (n, set, set_size)
 * Determines if n is a multiple of any member of the given set.
 */
char is_multiple (DATA n, DATA *set, INDEX set_size)
{
  INDEX i; for (i = 0; i < set_size; i++)
    if (fmod(n,set[i]) == 0) return 1;
  return 0;
}

/* factorial(n)
 * Returns the factorial of n. One-line ternary/recursive implementation from
 * https://www.geeksforgeeks.org/program-for-factorial-of-a-number/
 */
DATA factorial (DATA n)
{ return (n==1 || n==0) ? 1: n * factorial(n - 1); }

/* combination(n)
 * Returns the number of possible combinations of r objects
 * from a set of n objects.
 */
DATA combination (DATA n, DATA r)
{ return floor(factorial(n)/factorial(r))*factorial(n-r); }

/* optimize_divisors(set, set_size)
 * Flags and removes any elements in the given set that are
 * divisible by some other element in the set, for eliminating
 * duplicated matches when using the fast summation formula.
 */
DATA *optimize_divisors (DATA *set, INDEX *set_size)
{
  /* Declarations and initializations */
  DATA *optimized_set;
  INDEX optimized_set_size, orig_set_size, i, j;
  optimized_set_size = *set_size; orig_set_size = *set_size;

  /* Pass through input set and flag divisible values */
  for (i = 0; i < orig_set_size; i++)
    for (j = 0; j < orig_set_size; j++)
    {
      if ((j == i) || set[j] == -1) continue;
      if ((fmod(set[i],set[j]) == 0) || set[i] < 1) 
      { set[i] = -1; optimized_set_size--; break; } 
    }

  /* Allocate new optimized set with null terminator */
  optimized_set = (DATA *)calloc(optimized_set_size+1,sizeof(DATA));
  if (!optimized_set) { printf("ERROR: Divisor optimization failed due to memory allocation error!\n"); return set; }

  /* Copy remaining values in old set to new set */
  j = 0; for (i = 0; i < orig_set_size; i++)
    if (set[i] > 0) { optimized_set[j] = set[i]; j++; }

  /* Print contents of optimized array */
  printf("Optimized search: {");
  for (i = 0; i < optimized_set_size; i++)
  { printf("%.0Lf",optimized_set[i]); if (i != optimized_set_size - 1) printf(", "); } 
  printf("} (%lu byte",optimized_set_size*sizeof(DATA));
  if (optimized_set_size*sizeof(DATA) != 1) printf("s");
  printf(")\n");

  /* Return the new optimized set, adjust the size counter, and free the old one */
  free(set); *set_size = optimized_set_size; return optimized_set;
}

/* product_table(set, set_size)
 * Generates the power set of the input array to get all possible
 * products of the values it contains. Used for elimination of
 * duplicate matches when using the fast summation formula.
 */
DATA *product_table (DATA *set, INDEX set_size, INDEX *set_products)
{
  /* Variable declaration and initialization */
  DATA current_product, *product_table;
  INDEX power_set_size, product_table_size, i, j, n;
  power_set_size = pow(2, set_size);
  product_table_size = 0; current_product = 1; n = 0;
  *set_products = 0;

  /* Determine size of product table */
  for (i = 1; i <= set_size; i++) 
    product_table_size += combination(set_size,i);

  /* Print product table target size */  
  printf("Product table:    " INDEX_FORMAT " bytes\n",(INDEX)sizeof(DATA)*product_table_size);

  /* Initialize the product table */
  product_table = calloc(product_table_size,sizeof(DATA));

  /* Check if memory allocation succeeded */
  if (!product_table)
  {
    printf("ERROR: Product table allocation failure!\n");
    return product_table;
  }

  /* Populate the product table with the products of the power
   * set of the input set (excluding singletons and the empty set)
   */
  for (i = 0; i < power_set_size; i++)
  { 
    /* Get product */
    for (j = 0; j < set_size; j++) 
      if (i & (1<<j)) 
        { current_product *= set[j]; }

    /* Validate product */
    for (j = 0; j < set_size; j++) 
      if (current_product == set[j]) 
        { current_product = 1; break; }
    if (current_product <= 1) continue;

    /* Add product to table and reset */
    product_table[n] = current_product;
    n++; current_product = 1;
  }

  /* Product table is generated; return */
  *set_products = product_table_size;
  return product_table;
}

/* MAIN FUNCTION
 * Takes in the maximum value as the first argument and arbitrary 
 * target divisors in subsequent arguments. Keeps track of and
 * prints sum of matching numbers when loop is completed.
 */
int main (int argc, char **argv)
{
  /* Variable declarations and setup */
  DATA max, sum, over_sum, n, *divisors, *divisor_products, p;
  INDEX i, num_divisors, num_products;
  sum = 0; over_sum = 0; num_products = 0;

  /* Argument parsing */
  if (argc < 2) { printf("usage: %s [max] [divisor(s)]\n",argv[0]); return 0; }
  max = floor(atof(argv[1])); max--;
  if (max < 1) { printf("ERROR: %s only operates on positive integers!\n",argv[0]); return 0; }
  num_divisors = argc-2;
  divisors = (DATA *)calloc(num_divisors,sizeof(DATA));
  for (i = 0; i < num_divisors; i++) 
  { 
    divisors[i] = floor(atof(argv[i+2]));
    if (divisors[i] < 1) { printf("ERROR: %s only operates on positive integers!\n",argv[0]); return 0; }
  }

  /* Print pre-run statistics */
  printf("Testing range:    0 < n < " DATA_FORMAT "\n",max+1);
  printf("Data size:        " INDEX_FORMAT " bits\n",(INDEX)sizeof(DATA)*8);

  /* Optimize divisor set */
  divisors = optimize_divisors(divisors,&num_divisors);

  /* Generate divisor product table */
  divisor_products = product_table(divisors,num_divisors,&num_products);
  if (!divisor_products)
  {
    printf("Using brute force search...\n");
    for (i = 1; i <= max; i++)
      if (is_multiple(i,divisors,num_divisors)) sum+= i;
  } 
  else 
  {
    /* Optimize product table */
    divisor_products = optimize_divisors(divisor_products,&num_products);

    /* Initial summation pass over divisor table */
    i = 0; while (divisors[i] > 0)
      { n = divisors[i]; sum += floor(n*floor(max/n)*(floor(max/n)+1)/2); i++; }

    /* Corrective summation pass over divisor product table */
    i = 0; while (divisor_products[i] > 1)
    { 
      n = divisor_products[i];
      p = floor(n*floor(max/n)*(floor(max/n)+1)/2);
      over_sum += p;
      i++;
    }

    /* Correct final summation by subtracting the sum of any over-matched values */
    sum -= over_sum;
  }

  /* Result return and cleanup */ 
  printf("Sum of matches:   " DATA_FORMAT "\n",sum);
  free(divisors); return 0;
}
