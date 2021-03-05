/* PROBLEM 3 [ https://projecteuler.net/problem=3 ]
 * The prime factors of 13195 are 5, 7, 13 and 29.
 * What is the largest prime factor of the number 600,851,475,143?
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * SOLUTION: Trial division
 * Implements a simple, but laborious method which tests the given number n
 * against every number less than n. 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* OPTIONS */
#undef  _P3_DEBUG
 
/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* BASIC TYPE DEFINITIONS */
typedef long double   DATA;
#define DATA_FORMAT   "%.0Lf"

/* LINKED LIST NODE */
struct node
{
  DATA data;
  struct node* next;
};
typedef struct node node;

/* LINKED LIST STRUCTURE */
struct list 
{ 
  node* head; 
  size_t size;  
};
typedef struct list list;

/* OUTPUT STRINGS */
#define USAGE_STR   "usage: %s [value]\n"
#define ARGS_FAIL   "ERROR: %s only operates on positive integers!\n"
#define LALLOC_FAIL "ERROR: Factor list initialization failure!\n"
#define NALLOC_FAIL "ERROR: Could not allocate memory for factor list entry!\n"

/* FUNCTION PROTOTYPES */
void print_list     (list* l);
void destroy_list   (list* l);
void trial_factor   (DATA n, list* l);

/* BEGIN PROGRAM * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* print_list(*l)
 * Prints the contents of a list
 */
void print_list (list* l)
{
  node *c;

  if (l == NULL) return;
  c = l->head;

  printf("{");
  while (c != NULL)
  {
    printf(DATA_FORMAT,c->data);
    if(l->size > 1 && c->next != NULL) printf(", ");
    c = c->next;
  }
  printf("}\n");
  
  #ifdef _P3_DEBUG
  printf("(list size: %d bytes)\n",sizeof(list)+sizeof(node)*l->size);
  #endif
}

/* destroy_list(*l)
 * Frees an entire list, including nodes
 */
void destroy_list (list* l)
{
  node *c, *p;
  if (l == NULL) return;
  c = l->head;
  while (c != NULL) { p = c; c = p->next; free(p); }
  free(l);
}

/* trial_factor(n,*l)
 * Factors n by trial division and appends to a list 
 */
void trial_factor (DATA n, list* l)
{
  node *c, *p;
  DATA f,m; f = 2; m = sqrt(n); 

  /* initialize pointers: set c to the first null node in the list */
  p = NULL; c = l->head; while (c != NULL) { p = c; c = c->next; }    

  /* Test with f = 2 to check if n is even */ 
  if (fmod(n,f) == 0)
  {
    c = malloc(sizeof(node));
    if (p == NULL) { l->head = c; }
    else { p->next = c; }
    c->data = f; c->next = NULL;
    l->size++;
    p = c; c = c->next;
    n /= f;
  } f++; 

  /* Standard trial division by odd numbers for remaining factors
   * Loop terminates at f > m as a given number can only have one prime factor
   * greater than its square root 
   */
  while (n > 1)
  {
    if (fmod(n,f) == 0)
    {
      if (p && p->data == f) { n /= f; continue; } 
      c = malloc(sizeof(node));
      if (p == NULL) { l->head = c; }
      else { p->next = c; }
      c->data = f; c->next = NULL;
      l->size++;
      p = c; c = c->next;
      n /= f;
      if (f > m) break;
    } else f+=2;
  }
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
  list* l;

  /* Initialize the factor list */
  l = malloc(sizeof(list));
  if (!l) { printf(LALLOC_FAIL); return 0; }
  l->head = NULL; l->size = 0;

  /* Argument parsing */
  if (argc < 2) { printf(USAGE_STR,argv[0]); return 0; }
  n = floor(atof(argv[1]));
  if (n < 1) { printf(ARGS_FAIL,argv[0]); return 0; }

  /* Factor n */
  trial_factor(n,l);

  /* Clean up, print and destroy the results */
  if (l->size == 1) { printf(DATA_FORMAT " is prime\n",n); } 
  else { printf("Prime factors of " DATA_FORMAT ":\n",n); print_list(l); }
  destroy_list(l); 

  /* End of program */
  return 0;
}
