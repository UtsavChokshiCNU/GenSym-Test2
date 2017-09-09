/* -*- Mode: C -*-
 *
 * Header file for Matrix_Primitives
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * Mark A. Kramer
 *
 *
 */


#include <string.h>
#include <stdio.h>
#include <math.h>
#ifdef sun
#define DBL_EPSILON 2.2204460e-16
#define DBL_MAX 1.7976931348623157e+308
#define DBL_MIN 2.225073858507201e-308
#define RAND_MAX 2147483646
#else
#include <float.h>
#endif
#include <limits.h>
#include <stdlib.h>
#include <setjmp.h>

/**********************************************************************

Type Declarations and Global Data Structures

**********************************************************************/

#define true(a)  (fabs(a)>DBL_EPSILON)
#define false(a) (fabs(a)<=DBL_EPSILON)
#define isscalar(a) ((a)->m==1&&(a)->n==1)
#define isvector(a) ((a)->m==1||(a)->n==1)
#ifndef max
#define max(x,y) (((x)>(y))?(x):(y))
#endif
#ifndef min
#define min(x,y) (((x)<(y))?(x):(y))
#endif
#define round(x) (floor(x) + (fmod(x,1.0)<0.5?0:1))
#define zeros(x,y) allocate_from_pool(x,y,0)
#define newmat(x,y) allocate_from_pool(x,y,1)

typedef struct mat { /* basic matrix type */
  unsigned int m;    /* number of rows in a */
  unsigned int n;    /* number of columns in a */
  double **pm;       /* pointer to spine array which references rows */
  int *pool_array_index;  /* the corresponding pool location */
} matrix;

typedef struct pool_mat {  /* matrix for memory pool, has extra attributes */
  unsigned int m;    /* number of rows in a */
  unsigned int n;    /* number of columns in a */
  unsigned int search_point;  /* good place to start looking for available rows */
  unsigned short *inuse;  /* pointer to 0-1 array indicating if row is in use */
  double **pm;       /* pointer to spine array which references rows */
} pool_matrix;

typedef struct stack {
  struct mat *data;
  struct stack *next;
  struct stack *prev;
} element;

typedef struct memory_pool {
  unsigned int number_of_pool_mats;
  pool_matrix **pool_mat_address;  /* pointer to a spine array that holds pointers to pool matrices */
} memory_pool;

typedef double *pointer_to_double;
typedef matrix *pointer_to_matrix;
typedef element *pointer_to_stack;
typedef memory_pool *pointer_to_memory_pool;
typedef pool_matrix *pointer_to_pool_matrix;


/* Matrix return definitions.
   Note these definitions CANNOT HANDLE FUNCTIONAL RETURNS
   Each argument must be evaluated explicitly before calling */

#define matrix_return(x) push(x);return(x)

#define matrix_return2(x1,x2) push(x2);push(x1);return(x1)

#define matrix_return3(x1,x2,x3) push(x3);push(x2);push(x1);return(x1)

#define matrix_return4(x1,x2,x3,x4) push(x4);push(x3);push(x2);push(x1);return(x1)

#define matrix_return5(x1,x2,x3,x4,x5) push(x5);push(x4);push(x3);push(x2);push(x1);return(x1)

/* SET assigns x to the entire structure.  SET1, SET2, etc. assign a
   specific number of its x-arguments, ignoring (clearing) the rest */

#define set(x,y) y;fm(x);x=pop();clear_stack(local_ptr)

#define set2(x1,x2,y) y;fm(x1);fm(x2);x1=pop();x2=pop();clear_stack(local_ptr)

#define set3(x1,x2,x3,y) y;fm(x1);fm(x2);fm(x3);x1=pop();x2=pop();x3=pop();clear_stack(local_ptr)

#define set4(x1,x2,x3,x4,y) y;fm(x1);fm(x2);fm(x3);fm(x4);x1=pop();x2=pop();x3=pop();x4=pop();clear_stack(local_ptr)

#define set5(x1,x2,x3,x4,x5,y) y;fm(x1);fm(x2);fm(x3);fm(x4);fm(x5);x1=pop();x2=pop();x3=pop();x4=pop();x5=pop();clear_stack(local_ptr)

/************************************************************************

Function prototypes and global variables

*************************************************************************/

/* global variables */
pointer_to_stack ans;
pointer_to_memory_pool mat_pool;
int matcnt;


/* function prototypes */
void fm();
matrix *pop();
void check_for_duplicates();
void push();
void clear_stack();
matrix *allocate_from_pool();
matrix *ones();
matrix *eye();
matrix *d2m();
matrix *i2m();
double m2d();
int m2i();
matrix *size();
matrix *copy();
matrix *diag();
matrix *reshape1();
matrix *reshape2();
matrix *part();
matrix *row();
matrix *column();
matrix *append_lr();
matrix *append_ud();
matrix *insert();
matrix *remove_col();
matrix *remove_row();
matrix *transpose();
matrix *chsign();
matrix *add();
matrix *subtract();
matrix *scalar_add();
matrix *scalar_subtract();
matrix *mult();
matrix *scalar_mult();
matrix *scalar_divide();
matrix *absolute();
matrix *bounds();
matrix *ludcmp();
matrix *lubksb();
double det();
matrix *linear_solve();
matrix *least_squares();
matrix *inverse();
matrix *mult_ebe();
matrix *divide_ebe();
matrix *power_ebe();
matrix *sqroot();
matrix *sum();
matrix *mean();
matrix *cov();
matrix *sort();
matrix *sort_array();
matrix *not();
matrix *and();
matrix *or();
matrix *equal();
matrix *not_equal();
matrix *gt();
matrix *lt();
matrix *lte();
matrix *gte();
matrix *find();
matrix *sign();
matrix *maximum();
matrix *minimum();
matrix *mat_random();
double vnorm();
double ssq();

int check_dimensions();
void print_matrix();
void print_stack();
void print_pool();
void signal_block_error(char const* error_text);

/* prototypes for memory allocation and checking */

void initialize_memory_pool();
int pool_index();
void expand_pool();
pool_matrix *make_pool_matrix();
void memory_summary();







