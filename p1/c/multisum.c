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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef BRUTEFORCE
  #define FAST
#endif

/* TYPE DEFINITIONS */
typedef unsigned long DATA;
#define DATA_FORMAT   "%lu"
typedef unsigned long INDEX;
#define INDEX_FORMAT  "%lu"

#ifdef FAST
/* PAIR struct for differentiating odd/even products
 * when generating correction tables for the fast algorithm 
 */
typedef struct {
  DATA *odd;
  DATA *even;
} PAIR;
#endif

/* OUTPUT STRINGS */
#define USAGE_STR   "usage: %s [max] [divisor(s)]\n"
#define ARGS_FAIL   "ERROR: %s only operates on positive integers!\n"
#define CALLOC_FAIL "ERROR: Correction table allocation failure!\n"
#define OPT_FAIL    "ERROR: Memory allocation failure during optimization!\n"

/* FUNCTION PROTOTYPES */
DATA   *optimize_divisors (DATA *set, INDEX *set_size);
INDEX  is_multiple        (DATA n, DATA *set, INDEX set_size);
DATA   brute_force_sum    (DATA *divisors, INDEX num_divisors, DATA max);

#ifdef FAST
/* Fast algorithm functions */
DATA factorial     (DATA n);
INDEX combination  (DATA n, DATA r);
DATA sum_divisible (DATA n, DATA max);
DATA correction    (DATA max, DATA *set, INDEX set_size, INDEX *alloc_status);
#endif

/* BEGIN PROGRAM * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* optimize_divisors (set, set_size)
 * Flags and removes any elements in the given set that are
 * divisible by some other element in the set, for eliminating
 * duplicated matches when using the fast summation algorithm
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
  if (!optimized_set) { printf(OPT_FAIL); return set; }

  /* Copy remaining values in old set to new set */
  j = 0; for (i = 0; i < orig_set_size; i++)
    if (set[i] > 0) { optimized_set[j] = set[i]; j++; }

  #ifdef VERBOSE 
  /* Print contents of optimized array */
  printf("Optimized search: {");
  for (i = 0; i < optimized_set_size; i++)
  { 
    printf(DATA_FORMAT,optimized_set[i]);
    if (i != optimized_set_size - 1) printf(", ");
  } 
  printf("} (" INDEX_FORMAT " byte",optimized_set_size*sizeof(DATA));
  if (optimized_set_size*sizeof(DATA) != 1) printf("s");
  printf(")\n");
  #endif

  /* Clean up old set, adjust set size and return the new set */
  free(set); *set_size = optimized_set_size; return optimized_set;
}

/* is_multiple (n, set, set_size)
 * Determines if n is a multiple of any member of the given set.
 * Used in brute force fallback solution.
 */
INDEX is_multiple (DATA n, DATA *set, INDEX set_size)
{
  INDEX i; for (i = 0; i < set_size; i++)
    if (fmod(n,set[i]) == 0) return 1;
  return 0;
}

/* brute_force_sum (divisors, num_divisors, max)
 * Performs a brute force search of values divisible by the input
 * set in the range 0 < n < max; O(n) fallback in case memory
 * allocation fails while generating the sum correction for
 * the faster O(1) algorithm
 */
DATA brute_force_sum (DATA *divisors, INDEX num_divisors, DATA max)
{
 DATA n, sum, matches; sum = 0; matches = 0; 
 for (n = 1; n <= max; n++) 
   if (is_multiple(n,divisors,num_divisors)) { sum += n; matches++; }
 #ifdef VERBOSE
 printf("Matches in range: " DATA_FORMAT "\n",matches);
 #endif
 return sum;
}

#ifdef FAST
/* Functions in this block are only needed for fast summation */

/* factorial (n)
 * Returns the factorial of n. One-line ternary/recursive implementation from
 * https://www.geeksforgeeks.org/program-for-factorial-of-a-number/
 */
DATA factorial (DATA n)
{ return (n==1 || n==0) ? 1: n * factorial(n - 1); }

/* combination (n)
 * Returns the number of possible combinations of r objects
 * from a set of n objects; used to determine the amount of
 * memory needed for a product table
 */
INDEX combination (DATA n, DATA r)
{ return floor(factorial(n)/factorial(r))*factorial(n-r); }

/* sum_divisible (n, max)
 * Summation formula returning the sum of values divisible by n
 * in the range 0 < n < max
 */
DATA sum_divisible (DATA n, DATA max)
{ return floor(n*floor(max/n)*(floor(max/n)+1)/2); }

/* correction (max, set, set_size)
 * Generates a correction to apply to multiple summations
 * based on the power set of the input, accounts for all possible
 * products of the input and adds or subtracts them from the
 * correction based on whether they are odd or even
 */
DATA correction (DATA max, DATA *set, INDEX set_size, INDEX *alloc_status)
{
 /* Variable declaration and initialization */
 INDEX power_set_size, odd_size, even_size, factors, i, j, e, o, le, lo;
 DATA current_product, odd_sum, even_sum; PAIR *correction_table;
 power_set_size = pow(2, set_size);
 odd_size = 0; even_size = 0; current_product = 1;
 e = 0; o = 0; le = 0; lo = 0;

 /* Determine size of correction tables */
 for (i = 1; i <= set_size; i++)
 {
   if (i%2 == 0) {
     even_size += combination(set_size,i);
     if (le >= even_size) { printf(CALLOC_FAIL); *alloc_status = 1; return 0; }
     le = even_size; 
   } else {
     odd_size += combination(set_size,i);
     if (lo >= odd_size) { printf(CALLOC_FAIL); *alloc_status = 1; return 0; }
     lo = odd_size; 
   }
 }
 
 #ifdef VERBOSE
 /* Print product table target size */  
 printf("Correction table: " INDEX_FORMAT " bytes\n",
        (INDEX)sizeof(DATA)*(even_size+odd_size+sizeof(PAIR)+2));
 #endif

 /* Initialize the correction table */
 correction_table = malloc(sizeof(PAIR));
 if (!correction_table) 
 { printf(CALLOC_FAIL); *alloc_status = 1; return 0; }
 correction_table->odd = (DATA *)calloc(odd_size+1,sizeof(DATA));
 if (!correction_table->odd) 
 { printf(CALLOC_FAIL); *alloc_status = 1; return 0; }
 correction_table->even = (DATA *)calloc(even_size+1,sizeof(DATA));
 if (!correction_table->even) 
 { printf(CALLOC_FAIL); *alloc_status = 1; return 0; }

 /* Populate the correction table with the products of the power
  * set of the input set (excluding singletons and the empty set)
  */
 for (i = 0; i < power_set_size; i++)
 { 
   factors = 0;
   /* Get product */
   for (j = 0; j < set_size; j++) 
     if (i & (1<<j)) 
      { current_product *= set[j]; factors++; }

   /* Validate product */
   for (j = 0; j < set_size; j++) 
     if (current_product == set[j]) 
     { current_product = 1; break; }   
   if (current_product <= 1) continue;

   /* Add product to even or odd table and reset */
   if (factors%2 == 0) {
     correction_table->even[e] = current_product;
     e++; current_product = 1;
   } else {
     correction_table->odd[o] = current_product;
     o++; current_product = 1;
   }
 }

 /* Generate correction components and clean up */
 o = 0; odd_sum = 0; e = 0; even_sum = 0; 
 while (correction_table->odd[o] != 0) 
   { odd_sum += sum_divisible(correction_table->odd[o],max); o++; }
 free(correction_table->odd);
 while (correction_table->even[e] != 0) 
   { even_sum += sum_divisible(correction_table->even[e],max); e++; }
 free(correction_table->even);
 free(correction_table);
  
 /* Correction is generated; all-clear and return */
 *alloc_status = 0;
 return -even_sum+odd_sum;
}

/* End fast algorithm functions */
#endif

/* MAIN FUNCTION
 * Takes in the maximum value as the first argument and arbitrary 
 * target divisors in subsequent arguments. Keeps track of and
 * prints sum of matching numbers when loop is completed.
 */
int main (int argc, char **argv)
{
  /* Variable declarations and setup */
  DATA max, sum, *divisors;
  INDEX i, num_divisors;

  #ifdef FAST
   INDEX correction_flag;
   correction_flag = 1;
  #endif

  /* Argument parsing */
  if (argc < 3) { printf(USAGE_STR,argv[0]); return 0; }
  max = floor(atof(argv[1]))-1;
  if (max < 1) { printf(ARGS_FAIL,argv[0]); return 0; }
  num_divisors = argc-2;
  divisors = (DATA *)calloc(num_divisors,sizeof(DATA));
  for (i = 0; i < num_divisors; i++) 
  { 
    divisors[i] = floor(atof(argv[i+2]));
    if (divisors[i] < 1) { printf(ARGS_FAIL,argv[0]); return 0; }
  }
  
  #ifdef VERBOSE
  /* Print pre-run statistics */
  printf("Testing range:    0 < n < " DATA_FORMAT "\n",max+1);
  printf("Data size:        " INDEX_FORMAT " bits\n",(INDEX)sizeof(DATA)*8);
  #endif

  /* Optimize divisor set */
  divisors = optimize_divisors(divisors,&num_divisors);

  #ifdef FAST
  /* Make initial summation pass and then correct it by eliminating duplicates;
   * fall back to brute force algorithm if correction fails
   */
  sum = 0; i = 0; while (divisors[i] > 0) 
  { sum += sum_divisible(divisors[i],max); i++; }
  sum += correction(max,divisors,num_divisors,&correction_flag);
  if (correction_flag) { printf("Using brute force search...\n");
    sum = brute_force_sum(divisors,num_divisors,max); } 
  #else
  /* Use brute force search in all cases 
   * if BRUTEFORCE is defined during compilation
   */
  sum = brute_force_sum(divisors,num_divisors,max);
  #endif

  /* Result return and cleanup */ 
  #ifdef VERBOSE
  printf("Sum of matches:   ");
  #endif
  printf(DATA_FORMAT "\n",sum);
  free(divisors); return 0;
}
