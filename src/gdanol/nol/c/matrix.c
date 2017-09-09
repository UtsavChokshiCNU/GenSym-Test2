/* -*- Mode: C -*-
 *
 * Module Matrix
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * Andreas G. Hofmann & Mark A. Kramer
 *
 */

#include "matrix.h"
#define MEM_CHECK 0

int size_of_int = sizeof(int);
int size_of_unsigned_short = sizeof(unsigned short);
int size_of_double = sizeof(double);
int size_of_pointer_to_double = sizeof(pointer_to_double);
int size_of_matrix = sizeof(matrix);
int size_of_pointer_to_matrix = sizeof(pointer_to_matrix);
int size_of_element = sizeof(element);
int size_of_pointer_to_stack = sizeof(pointer_to_stack);
int size_of_pointer_to_memory_pool = sizeof(pointer_to_memory_pool);
int size_of_pool_matrix = sizeof(pool_matrix);
int size_of_pointer_to_pool_matrix = sizeof(pointer_to_pool_matrix);

/**********************************************************************

Stack Operations

**********************************************************************/


matrix *pop()
/* returns address of matrix at top of stack and restructures stack */
{
 pointer_to_stack pstack;
 matrix *top_matrix;
 pstack = ans;
 top_matrix = pstack->data;
 ans = pstack->next;
 free(pstack);
 return top_matrix;
}

void push(z)
matrix *z;
{
  pointer_to_stack pstack;
  pstack = (element *) malloc(size_of_element);  /* new element in stack */
  pstack->data = z;
  pstack->next = ans;
  ans = pstack;
}

void clear_stack(local_ptr)
pointer_to_stack local_ptr;
/* Clears stack from head down to local_ptr. If local_ptr = NULL entire stack is cleared */
{
  if(ans == local_ptr) return;
  fm(pop());
  clear_stack(local_ptr);
}


/**********************************************************************

Memory Allocation and Deallocation

**********************************************************************/

void initialize_memory_pool(number_of_pools)
int number_of_pools;
{
  int i,n,cols;
  mat_pool = (pointer_to_memory_pool) malloc(sizeof(memory_pool));
  mat_pool->number_of_pool_mats = number_of_pools;
  mat_pool->pool_mat_address = (pool_matrix **) calloc(number_of_pools,size_of_pointer_to_pool_matrix);
  cols = 1;
  for (i = 0; i<number_of_pools; ++i) {
    cols *= 2;
    if(i<7) n=1000;
      else n = 0;
    mat_pool->pool_mat_address[i] = make_pool_matrix(n,cols); 
  }
}

int pool_index(n)   /* Returns the memory pool index for any given vector length */
int n;
{
  int i=1,j= -1;
  if(n==1) return 0;
  while(i<n) {i *= 2;++j;}
  return j;
}

pool_matrix *make_pool_matrix(m, n)
int m, n;
{
  pool_matrix *x = NULL;
  int i;
  x = (pool_matrix *) calloc(1, size_of_pool_matrix);
  x->m = m;
  x->n = n;
  x->search_point = 1;  /* initially, search point is the first element */
  x->pm = (double **) calloc(m,size_of_pointer_to_double);  /* allocate spine */
  x->inuse = (unsigned short *) calloc(m,size_of_unsigned_short);  /* allocate inuse */
  x->pm -= 1;  /* backshift spine */
  x->inuse -= 1; /* backshift inuse */
  for (i = 1; i <= m; ++i) {
    x->pm[i] = (double *) calloc(n,size_of_double);  /* allocate rows */
    if(x->pm[i] == NULL) {
        printf("OUT OF MEMORY. UNRECOVERABLE ERROR. Goodbye!\n");
        signal_block_error("RPC extension process ran out of memory. You must kill and then restart the RPC process (See NOL Configurations->RPC menu).\n");
    }
    x->pm[i] -= 1;   /* backshift rows */
  }
  return x;
}


void expand_pool(pool_index,m)
int m,pool_index;
{
/* grow pool matrix at index pi */
  pool_matrix *x;
  int i,old_size,new_size,row_size;
  x = mat_pool->pool_mat_address[pool_index];
  old_size = x->m;
  new_size = old_size + m;
/*printf("Expanding pool %d, old size= %d, new size= %d\n",pool_index,old_size,new_size);*/
  x->pm = (double **)realloc(x->pm+1,new_size*size_of_pointer_to_double);/*reallocate spine*/
  if(x->pm == NULL) {
    printf("OUT OF MEMORY. UNRECOVERABLE ERROR. Goodbye!\n");
    signal_block_error("RPC extension process ran out of memory. You must kill and then restart the RPC process (See NOL Configurations->RPC menu).\n");
  }
  x->pm -= 1;  /* backshift spine */
  x->inuse = (unsigned short *) realloc(x->inuse+1,new_size*size_of_unsigned_short);
  if(x->inuse == NULL) {
    printf("OUT OF MEMORY. UNRECOVERABLE ERROR. Goodbye!\n");
    signal_block_error("RPC extension process ran out of memory. You must kill and then restart the RPC process (See NOL Configurations->RPC menu).\n");
  }
  x->inuse -= 1; /* backshift */
  for(i=old_size+1; i<=new_size; ++i) x->inuse[i] = 0;  /* initialize new storage */
/* now allocate new row storage for remaining */
  row_size = (int) pow(2.0,1.0+pool_index);
  for(i=old_size+1;i<=new_size;++i) {
      x->pm[i] = (double *) calloc(row_size,size_of_double);
      if(x->pm[i] == NULL) {
          printf("OUT OF MEMORY. UNRECOVERABLE ERROR. Goodbye!\n");
          signal_block_error("RPC extension process ran out of memory. You must kill and then restart the RPC process (See NOL Configurations->RPC menu).\n");
      }      
      x->pm[i] -= 1;
    }
  x->m = new_size;
}

matrix *allocate_from_pool(m, n, init)
int m, n, init;
/* m rows, n columns.  If init  = 0 then matrix is initialized to 0.0,
   otherwise, space is return uninitialized  */
{
  pointer_to_stack local_ptr = ans;
  matrix *z = NULL;
  pool_matrix *x;
  int i,j,pi,mtot;
/* prepare matrix z */
  z = (matrix *) calloc(1, size_of_matrix); /* allocate new matrix address */
  z->m = m;
  z->n = n;
  z->pm = (double **) calloc(m,size_of_pointer_to_double);  /* allocate spine */
  if(z->pm == NULL) {
      printf("OUT OF MEMORY. UNRECOVERABLE ERROR.\n");
      signal_block_error("RPC extension process ran out of memory. You must kill and then restart the RPC process (See NOL Configurations->RPC menu).\n");
  }
  z->pm -= 1;  /* backshift spine */
  z->pool_array_index = (int *) calloc(m,size_of_int); /* to store pool indices */
  if(z->pool_array_index == NULL) {
      printf("OUT OF MEMORY. UNRECOVERABLE ERROR. Goodbye!\n");
      signal_block_error("RPC extension process ran out of memory. You must kill and then restart the RPC process (See NOL Configurations->RPC menu).\n");
  }
  z->pool_array_index -= 1;
  pi = pool_index(n);
  x = mat_pool->pool_mat_address[pi];
  mtot = x->m;
  j = 1;
  i = x->search_point;
  while(j<=m) {
    if(i>mtot) {expand_pool(pi,m); mtot = x->m;}
/*printf("I = %d, j=%d, m=%d,mtot = %d\n",i,j,m,mtot); */   
    if(!x->inuse[i]) {
      x->inuse[i] = 1;
      z->pm[j] = x->pm[i];
/*printf("Assigning pool element %d to matrix element %d\n",i,j);*/      
      z->pool_array_index[j] = i; 
      ++i; ++j;
    } else ++i;
  }  
  x->search_point = (unsigned) i;  /* last element of pool matrix assigned to z */ 
#if MEM_CHECK==2
  ++matcnt;
  printf("Created matrix at address %d of size %d by %d\n",z,z->m,z->n);
  printf("Pool memory locations of the rows of this matrix are:\n");
  for(i=1;i<m;++i) printf("%d, ",z->pool_array_index[i]);
  printf("%d\n\n",z->pool_array_index[m]);
/*  print_pool(pi); */
#endif
/* initialize elements to 0.0 if necessary */  
  if(init==0) {for(i=1; i<=m; ++i) for(j=1;j<=n; ++j) z->pm[i][j] = 0.0;}
  matrix_return (z);
}


void fm(z)  /* free matrix */
matrix *z;
{
  int i,pi,m;
  pool_matrix *x;
  if(z == NULL) return;
#if MEM_CHECK==2
--matcnt;
printf("Clearing matrix address %d of size %d by %d\n",z,z->m,z->n);
#endif
  m = z->m;
  pi = pool_index(z->n);
  x = mat_pool->pool_mat_address[pi];
  for(i=1;i<=m;++i) {
    x->inuse[z->pool_array_index[i]] = 0;
  }
  if(x->search_point > z->pool_array_index[1]) x->search_point = z->pool_array_index[1];
  free (z->pm + 1); /* deallocate spine of pmat */
  free (z->pool_array_index + 1);
  z->m = 0;  /* this CAN be felt in the calling program; pmat is like an address */
  z->n = 0;
  free(z); /* frees space for the structure, size_of_matrix*/
}


void memory_summary()
{
  int i,j,inuse;
  pool_matrix *x;
  printf("Memory summary:\n");
  for(i=0;i<14;++i) {
    x = mat_pool->pool_mat_address[i];
    inuse = 0;
    for(j=1;j<=x->m;++j) inuse += x->inuse[j];
    printf("  Array size: %d, Pool size: %d, In use: %d, Search pt: %d\n",x->n,x->m,inuse,x->search_point);
  }
  printf("\n");
}

/**********************************************************************

Non-primitive Matrix Routines

**********************************************************************/

matrix *ones (m, n)
int m, n;
/* Returns a pointer to a new m-by-n matrix that constains all
   1's as its elements. */
{
  pointer_to_stack local_ptr = ans;
  matrix *pmat = NULL;
  int i, j;
  set(pmat,newmat(m, n));  /* don't bother to initialize to zero */
  for (i=1; i<=m; ++i) for (j=1; j<=n; ++j) pmat->pm[i][j] = 1.0;
  matrix_return (pmat);
}

matrix *eye (n)
int n;

/* Returns a pointer to a new n-by-n matrix that constains ones
   on the diagonal, zeros elsewhere. */
{
  pointer_to_stack local_ptr = ans;
  matrix *pmat = NULL;
  int i;

  set(pmat,zeros(n,n));
  for (i=1; i<=n; ++i) {
    pmat->pm[i][i] = 1.0;
  }
  matrix_return (pmat);
}


matrix *mat_random (m, n, lb, ub)
int m, n;
double lb, ub;
/* Returns a pointer to a new m-by-n matrix that contains random
   elements between lb and ub as its elements */
{
  pointer_to_stack local_ptr = ans;
  matrix *pmat = NULL;
  int i, j;
  set(pmat,newmat(m, n));
  for (i=1; i<=m; ++i) {
    for (j=1; j<=n; ++j) {
      pmat->pm[i][j] = (ub - lb)*(((double) rand())/((double) RAND_MAX)) + lb;
    }
  }
  matrix_return (pmat);
}


matrix *d2m(d)
double d;
/* makes a 1x1 matrix out of d */
{
  pointer_to_stack local_ptr = ans;
  matrix *x=NULL;
  set(x,newmat(1,1));
  x->pm[1][1] = d;
  matrix_return(x);
}


matrix *i2m(i)
int i;
/* makes a 1x1 matrix out of i */
{
  pointer_to_stack local_ptr = ans;
  matrix *x=NULL;
  set(x,newmat(1,1));
  x->pm[1][1] = (double) i;
  matrix_return(x);
}



double m2d(a)
matrix *a;
/* makes double from first element of a */
{
  return a->pm[1][1];
}

int m2i(a)
matrix *a;
/* makes int from first element of a */
{
  int i;
  i = floor(a->pm[1][1] + DBL_EPSILON);
  return i; 
}

/**********************************************************************

Matrix Size and Shaping Primitives

**********************************************************************/

matrix *size(a)
matrix *a;
{
  pointer_to_stack local_ptr = ans;
  matrix *s = NULL;
  set(s,newmat(1,2));
  if (a == NULL) {
    s->pm[1][1] = 0;
    s->pm[1][2] = 0; }
  else {
    s->pm[1][1] = a->m;
    s->pm[1][2] = a->n; }
  matrix_return(s);
}

matrix *copy(a)
matrix *a;
/* Copies the elements of b to be the same as the elements of a. */
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *b = NULL;
  if(a==NULL) {matrix_return(b);}
  set(b, newmat(a->m,a->n));
  for (i=1; i<=a->m; ++i) {
    for (j=1; j<=a->n; ++j) {
      b->pm[i][j] = a->pm[i][j];
    }
  }
  matrix_return(b);
}


matrix *diag(a)
matrix *a;
/*makes a diagonal matrix out of vector a, or returns the main diagonal of matrix a */
{
  pointer_to_stack local_ptr = ans;
  matrix *d=NULL;
  int i,len;
  if(a->m==1) {
    len = a->n;
    set(d,zeros(len,len));    
    for(i=1;i<=len;++i) d->pm[i][i] = a->pm[1][i];
  }
  else if (a->n==1) {
    len = a->m;
    set(d,zeros(len,len));
    for(i=1;i<=len;++i) d->pm[i][i] = a->pm[i][1];
  }
  else {
    len = min(a->n,a->m);
    set(d,zeros(1,len));
    for(i=1;i<=len;++i) d->pm[1][i] = a->pm[i][i];
  }
  matrix_return(d);
}

matrix *reshape1 (a, m, n)
matrix *a;
int m,n;

/* Returns a new m-by-n matrix whose elements are taken columnwise
   from a.  Error results if A does not have m * n elements. */
{
  pointer_to_stack local_ptr = ans;
  char err_text[100];
  int i, j, i1, j1;
  matrix *c = NULL;
  if (a->m * a->n != m * n) {
    sprintf(err_text,"The matrix a does not have %d elements: In reshape1\n", m * n);
    signal_block_error (err_text);
  }
  set(c,newmat(m, n));
  i1 = 1;
  j1 = 1; 
  for (j=1; j<=a->n; ++j) {
    for (i=1; i<=a->m; ++i) {
      c->pm[i1][j1] = a->pm[i][j];
      if (i1 < m)
	++i1;
      else {
	i1 = 1;
	++j1;      
      }
    }
  }
  matrix_return (c);
}

matrix *reshape2 (a, m, n)
matrix *a;
int m,n;

/* Returns a new m-by-n matrix whose elements are taken row-wise
   from a.  Error results if A does not have m * n elements. */
{
  pointer_to_stack local_ptr = ans;
  int i, j, i1, j1;
  char err_text[100];
  matrix *c = NULL;
  if (a->m * a->n != m * n) {
    sprintf(err_text,"The matrix a does not have %d elements: In reshape2\n", m * n);
    signal_block_error (err_text);
  }
  set(c,newmat(m, n));
  i1 = 1;
  j1 = 1;
  for (i=1; i<=a->m; ++i) {
    for (j=1; j<=a->n; ++j) {
      c->pm[i1][j1] = a->pm[i][j];
      if(j1 < n)
        ++j1;
      else {
        j1 = 1;
        ++i1;
      }
    }
  }
  matrix_return (c);
}


matrix *part(a, m1, n1, m2, n2)
matrix *a;
int m1, n1, m2, n2;

/* Extracts submatrix from matrix a, from a[m1][n1] to a[m2][n2],
   returning the submatrix as a new matrix. 
   The indices m1, n1, m2, and n2 must all fit within the 
   dimensions of a. */
{
  pointer_to_stack local_ptr = ans;
  int i, j, i1, j1, m, n;
  char err_text[150];
  matrix *c = NULL;
  if (a->m < m1 || a->m < m2 || a->n < n1 || a->n < n2) {
    sprintf(err_text,"The submatrix specified by %d, %d, %d, %d overrun matrix a which is %d by %d: In part\n", m1, n1, m2, n2,a->m,a->n);
    signal_block_error (err_text);
  }
  m = m2 - m1 + 1; n = n2 - n1 + 1;
  if (n<=0 || m<=0) {matrix_return(c);} /* null part */
  set(c, newmat(m,n));
  i1 = 1; j1 = 1; 
  for (i=m1; i <= m2; ++i) {
    for (j=n1; j <= n2; ++j) {
      c->pm[i1][j1] = a->pm[i][j];
      if (j1 < n) ++j1;
      else {
	j1 = 1;
	++i1;
      }
    }
  }
  matrix_return (c);
}


matrix *row (a, m1)
matrix *a;
int m1;
/* Extracts row m1 from a and returns it as a new matrix */
{
  pointer_to_stack local_ptr = ans;
  int j,m,n;
  char err_text[150];
  matrix *c = NULL;
  m = a->m;
  n = a->n;
  if (m < m1) {
    sprintf(err_text,"Row %d lies outside of a which has %d rows: In row\n", m1,m);
    signal_block_error(err_text);
  }
  set(c,newmat(1,n));
  for(j=1;j<=n;++j) c->pm[1][j] = a->pm[m1][j];
  matrix_return(c);
}

matrix *column (a, n1)
matrix *a;
int n1;
/* Extracts column n1 from a and returns it as a new matrix oriented
   column-wise */
{
  pointer_to_stack local_ptr = ans;
  int i,m,n;
  char err_text[150];
  matrix *c = NULL;
  m = a->m;
  n = a->n;
  if (n < n1) {
    sprintf(err_text,"Column %d lies outside of source matrix which has %d columns: In column\n", n1,n);
    signal_block_error(err_text);
  }
  set(c,newmat(m,1));
  for(i=1;i<=m;++i) c->pm[i][1] = a->pm[i][n1];
  matrix_return(c);
}


matrix *append_lr (a, b)
matrix *a, *b;

/* Appends a and b in side-by-side (left and right) manner, returning the 
   result in a new matrix.  Error results if a and b do not have the same 
   number of rows. */ 
{
  pointer_to_stack local_ptr = ans;
  int i, j, n1;
  char err_text[150];
  matrix *c = NULL;
  if(a==NULL) {set(c,copy(b)); matrix_return(c);}
  if(b==NULL) {set(c,copy(a)); matrix_return(c);}
  if (a->m != b->m) {
    sprintf(err_text,"The row dimensions %d and %d are incompatible: In append_lr\n", a->m, b->m);
    signal_block_error(err_text);
  }
  n1 = a->n;
  set(c,newmat(a->m,n1+b->n));
  for (i=1; i <= a->m; ++i) {
    for (j=1; j <= n1; ++j)
      c->pm[i][j] = a->pm[i][j];
    for (j=1; j <= b->n; ++j)
      c->pm[i][j + n1] = b->pm[i][j];
  }
  matrix_return (c);
}

matrix *append_ud (a, b)
matrix *a, *b;
/* Appends b below a in up-and-down manner, returning the result
   in a new matrix.  Error results if a and b do not have the 
   same number of columns. */
{
  pointer_to_stack local_ptr = ans;
  int i, j, m1;
  matrix *c = NULL;
  char err_text[150];
  if(a==NULL) {set(c,copy(b)); matrix_return(c);}
  if(b==NULL) {set(c,copy(a)); matrix_return(c);}
  if (a->n != b->n) {
    sprintf(err_text,"The column dimensions %d and %d are incompatible: In append_ud\n", a->m, b->m);
    signal_block_error(err_text);
  }
  m1 = a->m;
  set(c,newmat(m1+b->m,a->n));
  for (j=1; j <= a->n; ++j) {
    for (i=1; i <= m1; ++i)
      c->pm[i][j] = a->pm[i][j];
    for (i=1; i <= b->m; ++i)
      c->pm[i + m1][j] = b->pm[i][j];
  }
  matrix_return (c);
}

matrix *insert(a, b, i)
matrix *a, *b;
int i;

/* Inserts matrix b in matrix a at column i of matrix a. Error results if a 
   and b do not have the same number of rows. */ 
{
  pointer_to_stack local_ptr = ans;
  matrix *c = NULL;
  char err_text[150];
  if (a->m != b->m) {
    sprintf(err_text,"Row dimensions %d and %d are incompatible: In insert\n ", a->m, b->m); 
    signal_block_error (err_text);
  }
  if (i>a->n) {set(c,append_lr(a,b));}
  else {set(c,append_lr(append_lr(part(a,1,1,a->m,i-1),b),part(a,1,i,a->m,a->n)));}
  matrix_return (c);
}


matrix *remove_col(a,i)
matrix *a;
int i;
/* removes column i from a */
{
  pointer_to_stack local_ptr = ans;
  matrix *c = NULL;
  if(i==1) {set(c,part(a,1,2,a->m,a->n));}
  else if(i==a->n) {set(c,part(a,1,1,a->m,a->n-1));}
  else if(i>1 && i<a->n) {set(c,append_lr(part(a,1,1,a->m,i-1),part(a,1,i+1,a->m,a->n)));}
  else signal_block_error("Tried to remove a non-existent column in remove_col");  
  matrix_return(c);
}


matrix *remove_row(a,i)
matrix *a;
int i;
/* removes row i from a */
{
  pointer_to_stack local_ptr = ans;
  matrix *c = NULL;
  if(i==1) {set(c,part(a,2,1,a->m,a->n));}
  else if(i==a->m) {set(c,part(a,1,1,a->m-1,a->n));}
  else if(i>1 && i<a->m) {set(c,append_ud(part(a,1,1,i-1,a->n),part(a,i+1,1,a->m,a->n)));}
  else signal_block_error("Tried to remove a non-existent row in remove_row");  
  matrix_return(c);
}


matrix *transpose (a)
matrix *a;
/* Allocates new matrix b that is n-by-m if a is m-by-n, and
   then fills b with transpose of a. */
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *b = NULL;
  set(b,newmat(a->n,a->m));
  for (i=1; i<=a->m; ++i) {
    for (j=1; j<=a->n; ++j) {
      b->pm[j][i] = a->pm[i][j];
    }
  }
  matrix_return (b);
}



/**********************************************************************

Matrix Arithmetic Primitives

**********************************************************************/

matrix *chsign(a)
matrix *a;
/* returns -a */
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *b = NULL;
  set(b,newmat(a->m,a->n));
  for (i=1; i<=a->m; ++i) {
    for (j=1; j<=a->n; ++j) {
      b->pm[i][j] = -a->pm[i][j];
    }
  }
  matrix_return (b);
}

matrix *add (a, b)
matrix *a, *b;

/* If a or b is a scalar (1x1 matrix), then the scalar value is added
   to all elements of the other argument.  Otherwise, a and b must
   have the same dimensions and an add is performed. */
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *sum_mat = NULL, *scalar_add(); 
  if (isscalar(a)) {
    set(sum_mat,scalar_add(m2d(a), b));
    matrix_return(sum_mat);
  }
  else if (isscalar(b)) {
    set(sum_mat,scalar_add(m2d(b), a));
    matrix_return(sum_mat);
  }
  check_dimensions(a,b," In add\n");
  set(sum_mat,newmat(a->m,a->n));
  for (i=1; i<=a->m; ++i) 
    for (j=1; j<=a->n; ++j) sum_mat->pm[i][j] = a->pm[i][j] + b->pm[i][j];
  matrix_return (sum_mat);
}

matrix *subtract (a, b)
matrix *a, *b;

/* If a or b is a scalar (1x1 matrix), then the scalar value is subtract
   from all elements of the other argument.  Otherwise, a and b must
   have the same dimensions and a subtract is performed. */
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *sum_mat = NULL, *scalar_subtract(), *scalar_mult();
  if (isscalar(b)) {
     set(sum_mat,scalar_subtract(m2d(b),a));
     matrix_return(sum_mat); 
  }
  else if (isscalar(a)) {
    set(sum_mat,scalar_mult(-1.0,scalar_subtract(m2d(a),b)));
    matrix_return(sum_mat);
  }
  check_dimensions(a,b," In subtract\n");
  set(sum_mat,newmat(a->m, a->n));
  for (i=1; i<=a->m; ++i) 
    for (j=1; j<=a->n; ++j) sum_mat->pm[i][j] = a->pm[i][j] - b->pm[i][j];
  matrix_return (sum_mat);
}

matrix *scalar_add (a, b)
matrix *b;
double a;
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *sum_mat = NULL; 
  set(sum_mat,newmat(b->m,b->n));
  for (i=1; i<=b->m; ++i) 
    for (j=1; j<=b->n; ++j) sum_mat->pm[i][j] = a + b->pm[i][j];
  matrix_return (sum_mat);
}

matrix *scalar_subtract (a, b)
matrix *b;
double a;
/* subtracts scalar a FROM each element of matrix b NOTE THIS WELL! */
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *sum_mat = NULL; 
  set(sum_mat,newmat(b->m,b->n));
  for (i=1; i<=b->m; ++i) 
    for (j=1; j<=b->n; ++j) sum_mat->pm[i][j] = b->pm[i][j] - a;
  matrix_return (sum_mat);
}


matrix *mult (a, b)
matrix *a, *b;
/* If a or b is a scalar (1x1 matrix), then the scalar value is multiplied
   by all elements of the other argument.  Otherwise, the number of columns
   of a must match the number of rows of b. */
{
  pointer_to_stack local_ptr = ans;
  int i, j, k;
  matrix *mult_mat = NULL, *scalar_mult();
  char err_text[150];
  double sum;
  if (isscalar(a)) {
     set(mult_mat,scalar_mult(m2d(a), b));
     matrix_return(mult_mat);
   }
  else if (isscalar(b)) {
    set(mult_mat,scalar_mult(m2d(b), a));
    matrix_return(mult_mat);
  }
  else if (a->n != b->m) {
    sprintf(err_text,"Column dimension of a (%d) incommensurate with the row dimension of b (%d): In mult\n", a->n, b->m);
    signal_block_error(err_text);
  }
  set(mult_mat,newmat(a->m, b->n));
  for (i=1; i<=a->m; ++i) {
    for (j=1; j<=b->n; ++j) {
      sum = 0.0;
      for (k=1; k<=b->m; ++k) sum = sum + a->pm[i][k] * b->pm[k][j];
      mult_mat->pm[i][j] = sum;
    }
  }
  matrix_return (mult_mat);
}

matrix *scalar_mult (a, b)
matrix *b;
double a;
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *mult_mat = NULL;
  set(mult_mat,newmat(b->m,b->n));
  for (i=1; i<=b->m; ++i) 
    for (j=1; j<=b->n; ++j) mult_mat->pm[i][j] = a*b->pm[i][j];
  matrix_return (mult_mat);
}

matrix *scalar_divide(a,b)
matrix *b;
double a;
/* divides elements of b by a */ 
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *c = NULL;
  if(a==0.0) signal_block_error("divisor is zero:  In scalar_divide\n");
  set(c,newmat(b->m, b->n));
  for (i=1; i<=b->m; ++i)
    for (j=1; j<=b->n; ++j) c->pm[i][j] = b->pm[i][j]/a;
  matrix_return(c);
}

matrix *absolute (a)
matrix *a;
/* matrix absolute value */ 
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *c = NULL; 
  set(c,newmat(a->m,a->n));
  for (i=1; i<=a->m; ++i) 
    for (j=1; j<=a->n; ++j) c->pm[i][j] = fabs(a->pm[i][j]);
  matrix_return (c);
}


matrix *bounds (a,lb,ub)
matrix *a;
double lb,ub;
/* replaces elements outside bounds by upper bound or lower bound */ 
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *c = NULL; 
  set(c,copy(a));
  for (i=1; i<=a->m; ++i) 
    for (j=1; j<=a->n; ++j) {
      if(a->pm[i][j]>ub) c->pm[i][j] = ub;
      else if(a->pm[i][j]<lb) c->pm[i][j] = lb;
  }
  matrix_return (c);
}



/**********************************************************************

Linear Equation Solving Routines

**********************************************************************/

matrix *ludcmp (a, index)
matrix *a;
int *index;

/* Given the square matrix a, returns the LU decomposition of a 
rowwise permutation of a.  Index is an integer vector which
records the row permutation effected by partial pivoting.
Singularity is indicated by NULL return: a fatal error is NOT induced */

{
  pointer_to_stack local_ptr = ans;
  int i, j, k, n, imax;
  double aamax, abs1, sum, dum, *pm_temp;
  matrix *lu = NULL, *vv = NULL, *d = NULL;

  n = a->n;
  set(lu,copy(a));
  set(d,ones(1,1));
  set(vv,zeros(1,n));
  for (i=1; i<=n; ++i) {
    aamax = 0.0;
    for (j=1; j<=n; ++j) {
      abs1 = fabs(lu->pm[i][j]);
      if (abs1 > aamax)
	aamax = abs1;
    }
    if (aamax == 0.0) {
      printf("Warning: Singular matrix encountered in ludcmp.\n");
      fm(lu); lu = NULL; fm (vv);
      matrix_return2(lu,d);
    }
    vv->pm[1][i] = 1.0 / aamax;
  }
  for (j=1; j<=n; ++j) {
    for (i=1; i<j; ++i) {
      sum = lu->pm[i][j];
      for (k=1; k<i; ++k) {
	sum = sum - lu->pm[i][k] * lu->pm[k][j];
      }
      lu->pm[i][j] = sum;
    }
    aamax = 0.0;
    for (i=j; i<=n; ++i) { 
      sum = lu->pm[i][j];
      for (k=1; k<j; ++k) {
	sum = sum - lu->pm[i][k] * lu->pm[k][j];
      }
      lu->pm[i][j] = sum;
      dum = vv->pm[1][i] * fabs(sum);
      if (dum >= aamax) {
	imax = i;
	aamax = dum;
      }
    }
    
    if (j != imax) {
      pm_temp = lu->pm[imax];
      lu->pm[imax] = lu->pm[j];
      lu->pm[j] = pm_temp;

/*parity switch here*/
      d->pm[1][1] = - d->pm[1][1];
      vv->pm[1][imax] = vv->pm[1][j];
    }

    index[j] = imax;
    if (lu->pm[j][j] == 0.0) {
      printf ("Warning: Singular matrix encountered in ludcmp.\n");
      printf("Warning: Singular matrix encountered in ludcmp.\n");
      fm(lu); lu = NULL; fm (vv);
      matrix_return2(lu,d);
    }
    if (j != n) {
      dum = 1.0 / lu->pm[j][j];
      for (i = j + 1; i<=n; ++i)
	lu->pm[i][j] = lu->pm[i][j] * dum;
    }
  }
  fm (vv);
  matrix_return2 (lu,d);
}


matrix *lubksb (lu, index, b)
matrix *lu, *b;
int *index;

/* Solves the set of linear equations Ax = b.  LU is the
   LU decomposition of a rowwise permutation of the A matrix
   (returned by ludcmp).  Index is the permutation vector 
   computed by ludcmp.  b, which is n by 1, is the right-hand 
   side column vector.  Lubksb returns the solution x (n by 1). */
{
  pointer_to_stack local_ptr = ans;
  int i, j, ii, ll, n;
  double sum;
  matrix *x = NULL;

  ii = 0;
  n = lu->n;
  set(x, copy(b));

  for (i=1; i<=n; i++) {
    ll = index[i];
    sum = x->pm[ll][1];
    x->pm[ll][1] = x->pm[i][1];
    if (ii)
      for (j=ii; j<=i-1; j++)
	sum -= lu->pm[i][j] * x->pm[j][1];
    else if (sum != 0.0) ii = i;
    x->pm[i][1] = sum;
  }

  for (i = n ; i >= 1; i--) {
    sum = x->pm[i][1];
    for (j = i + 1; j<=n; j++)
	sum -= lu->pm[i][j] * x->pm[j][1];
    x->pm[i][1] = sum / lu->pm[i][i];
  }
  matrix_return (x);
}


double det(a)
matrix *a;
/* Determinant of a matrix, see Numerical Recipes, section 2.5.
   If a is singular, det(a) returns 0.0  */
{
  pointer_to_stack local_ptr = ans;
  matrix *d = NULL, *lu = NULL, *ludcmp();
  double dd;
  int j,n,*index;
  n = a->m;
  if(a->n != n) signal_block_error("a matrix not square:  In det\n");
  index = (int *) calloc (n, sizeof(int)); index -= 1;
  set2(lu,d,ludcmp (a, index));
  if(lu == NULL) {free(index + 1); return 0.0;} /* singularity return */
  dd = m2d(d); 
  for(j=1;j<=n;++j) dd *= lu->pm[j][j];
  fm(lu);
  free (index + 1);
  return dd;
}



matrix *linear_solve (a, b)
matrix *a, *b;

/* Solves Ax = b using LU decomposition. A is a n by n matrix and b is
   a n by k matrix, where k >= 1 is the number of right-hand-side vectors.
   x is returned as a n by k matrix. */

{
/* In case of singularity, x is returned as a 1x1 matrix with value -99.9 */
  pointer_to_stack local_ptr = ans;
  matrix *lu = NULL, *ludcmp(), *lubksb(), *x=NULL;
  int i,n,k,*index;
  n = a->m;  k = b->n;  
  if(a->n != n) signal_block_error("a matrix not square:  In linear solve\n");
  if(b->m != n) signal_block_error("b does not have the same number of rows as a: In linear solve\n");
  index = (int *) calloc (n, sizeof(int));
  index -= 1;
  set(lu,ludcmp(a, index));
  if(lu == NULL) {free(index + 1); matrix_return(lu);} /* singularity return */
  for(i=1;i<=k;++i) {set(x,append_lr(x,lubksb (lu, index, column(b,i))));}  
  free (index + 1);
  fm(lu);
  matrix_return (x);
}


matrix *least_squares(a,b)
matrix *a, *b;
/*
   Solves Ax = b by least squares, where the number of rows of A (m) 
   (observations) exceeds the number of columns of A (n) (unknowns).
   b is a m by k vector of right-hand sides.  Answer is returned as a
   n by k matrix.  If problem is singular, least_squares returns the NULL matrix. */

{
  pointer_to_stack local_ptr = ans;
  matrix *at = NULL, *x=NULL, *linear_solve();
  set(at, transpose(a));
  set(x,linear_solve(mult(at,a),mult(at,b)));
  fm(at);
  matrix_return(x);
}


matrix *inverse (a)
matrix *a;

/*  The inverse of A is returned, calculated by LU solve of Ax = I
    If matrix is singular to working precision, inverse returns the NULL matrix  */
{
  pointer_to_stack local_ptr = ans;
  matrix *c=NULL, *linear_solve();
  if(a->n != a->m) signal_block_error("Non-square matrix in inverse\n");
  set(c,linear_solve(a,eye(a->n)));
  matrix_return(c);
}


/**********************************************************************

Element by Element Operations

**********************************************************************/



matrix *mult_ebe (a, b)
matrix *a, *b;

/* Element by element multiplication of a by b.  A and b
   must have the same dimensions. */
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *c = NULL;

  check_dimensions (a, b," In mult_ebe\n");
  set(c,newmat(a->m, a->n));
  for (i=1; i<=a->m; ++i) {
    for (j=1; j<=a->n; ++j) {
      c->pm[i][j] = a->pm[i][j] * b->pm[i][j];
    }
  }
  matrix_return (c);
}

matrix *divide_ebe (a, b)
matrix *a, *b;

/* Element by element division of a by b.  A and b
   must have the same dimensions. */
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *c = NULL;
  check_dimensions (a, b, " In divide_ebe\n");
  set(c,newmat(a->m, a->n));
  for (i=1; i<=a->m; ++i) {
    for (j=1; j<=a->n; ++j) {
      c->pm[i][j] = a->pm[i][j] / (b->pm[i][j] + DBL_MIN);
    }
  }
  matrix_return (c);
}

matrix *power_ebe (a, n)
matrix *a;
double n;

/* Element by element power. */
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *c = NULL;
  double expt();
  set(c,newmat(a->m, a->n));
  for (i=1; i<=a->m; ++i) {
    for (j=1; j<=a->n; ++j) {
      c->pm[i][j] = pow (a->pm[i][j], n);
    }
  }
  matrix_return (c);
}

matrix *sqroot (a)
matrix *a;

/* Element by element square root. */
{
  pointer_to_stack local_ptr = ans;
  int i, j;
  matrix *c = NULL;

  set(c,newmat(a->m,a->n));
  for (i=1; i<=a->m; ++i) {
    for (j=1; j<=a->n; ++j) {
      c->pm[i][j] = sqrt (a->pm[i][j]);
    }
  }
  matrix_return (c);
}

matrix *sum(a)
matrix *a;
/* Sum of elements for vector, column sums for matrix */
{
 pointer_to_stack local_ptr = ans;
 int i,j; 
 matrix *c = NULL;
 if (a->n == 1 || a->m == 1) {
   set(c,zeros(1,1));
   for(i=1; i<=a->m; ++i) 
      for(j=1; j<=a->n; ++j) 
        c->pm[1][1] += a->pm[i][j]; 
   }
 else {
   set(c,zeros(1,a->n));
   for(i=1; i<=a->m; ++i) 
      for(j=1; j<=a->n; ++j) 
        c->pm[1][j] += a->pm[i][j];
 }
 matrix_return(c);
}


matrix *mean(a)
matrix *a;
/* Mean of elements for vector, column sums for matrix */
{
 pointer_to_stack local_ptr = ans;
 int j,nn;
 matrix *c = NULL;
 set(c,sum(a));
 if(c->n == 1) {
   nn = max(a->m,a->n);
   c->pm[1][1] /= ((double) nn);
 }
 else for(j=1;j<=c->n;++j) c->pm[1][j] /= ((double) a->m);
 matrix_return(c);
}


matrix *cov(x)
matrix *x;
/* Covariance of x */
{
  pointer_to_stack local_ptr = ans;
  matrix *c=NULL,*xm=NULL;
  int m,n;
  m = x->m;
  n = x->n;
  set(xm,subtract(x,mult(ones(m,1),mean(x))));
  if(m==1) {set(c,zeros(1,1));}
  else {set(c,scalar_divide((double) m-1, mult(transpose(xm),xm)));}
  fm(xm);
  matrix_return(c);
}



matrix *sort(a)
matrix *a;
/* Column-by-column sort of matrix a */
{
  pointer_to_stack local_ptr = ans;
  int m,n,j;
  matrix *c=NULL;
  n = a->n;
  m = a->m;
  if(n == 1 || m == 1) {set(c,sort_array(a));}
  else {
    for(j=1;j<=n;++j) {set(c,append_lr(c,sort_array(column(a,j))));}
  }
  matrix_return(c);
}


matrix *sort_array(a)
matrix *a;
/* Heapsort of vector a -- See Numer Recipes in C p. 247
   Return is same shape as a, either row or column */
{
  pointer_to_stack local_ptr = ans;
  int m,n,l,j,ir,i;
  matrix *ra=NULL;
  double rra;
  n = a->n;
  m = a->m;
  if(n != 1 && m != 1) signal_block_error("Sort_array called with matrix argument\n");
  if(n==1) {set(ra,transpose(a));}
  else {set(ra,copy(a));}
  n = ra->n; 
  l = (n >> 1) + 1;
  ir = n;
  for(;;) {
    if(l > 1)
      rra = ra->pm[1][--l];
    else {
      rra = ra->pm[1][ir];
      ra->pm[1][ir] = ra->pm[1][1];
      if(--ir == 1) {
	ra->pm[1][1]=rra;
        if(a->n == 1) {set(ra,transpose(ra));}
	matrix_return(ra);
      }
    }
    i=l;
    j = l << 1;
    while(j <= ir) {
      if(j<ir && ra->pm[1][j] < ra->pm[1][j+1]) ++j;
      if(rra < ra->pm[1][j]) {
	ra->pm[1][i] = ra->pm[1][j];
	j += (i=j);
      }
      else j=ir+1;
    }
    ra->pm[1][i] = rra;
  }
}


/**********************************************************************

Logical Functions

***********************************************************************/

matrix *not(a)
matrix *a;
{
 pointer_to_stack local_ptr = ans;
 int i,j;
 matrix *c = NULL;
 set(c,newmat(a->m,a->n));
 for(i=1; i<=a->m; ++i) 
      for(j=1; j<=a->n; ++j) {
        if(false(a->pm[i][j])) c->pm[i][j] = 1.0;
        else c->pm[i][j] = 0.0; 
      }
 matrix_return(c);
}

matrix *and(a,b)
matrix *a,*b;
{
 pointer_to_stack local_ptr = ans;
 int i,j;
 matrix *c = NULL;
 check_dimensions(a,b, " In and\n");
 set(c,newmat(a->m,a->n));
 for(i=1; i<=a->m; ++i) 
      for(j=1; j<=a->n; ++j) {
        if(true(a->pm[i][j]) && true(b->pm[i][j])) c->pm[i][j] = 1.0;
        else c->pm[i][j] = 0.0;
      }
 matrix_return(c);
}


matrix *or(a,b)
matrix *a,*b;
{
 pointer_to_stack local_ptr = ans;
 int i,j;
 matrix *c = NULL;
 check_dimensions(a,b," In or\n");
 set(c,newmat(a->m,a->n));
 for(i=1; i<=a->m; ++i) 
      for(j=1; j<=a->n; ++j) {
        if(true(a->pm[i][j]) || true(b->pm[i][j])) c->pm[i][j] = 1.0;
        else c->pm[i][j] = 0.0;
      }
 matrix_return(c);
}

matrix *equal(a,b)
matrix *a,*b;
{
 pointer_to_stack local_ptr = ans;
 int i,j;
 matrix *c = NULL;
 check_dimensions(a,b," In equal\n");
 set(c,newmat(a->m,a->n));
 for(i=1; i<=a->m; ++i) 
      for(j=1; j<=a->n; ++j) {
        if(false(a->pm[i][j] - b->pm[i][j])) c->pm[i][j] = 1.0;
        else c->pm[i][j] = 0.0;
      }
 matrix_return(c);
}

matrix *not_equal(a,b)
matrix *a,*b;
{
 pointer_to_stack local_ptr = ans;
 int i,j;
 matrix *c = NULL;
 check_dimensions(a,b," In not_equal\n");
 set(c,newmat(a->m,a->n));
 for(i=1; i<=a->m; ++i) 
      for(j=1; j<=a->n; ++j) {
        if(true(a->pm[i][j] - b->pm[i][j])) c->pm[i][j] = 1.0;
        else c->pm[i][j] = 0.0;
      }
 matrix_return(c);
}

matrix *gt(a,b)
matrix *a,*b;
{
 pointer_to_stack local_ptr = ans;
 int i,j;
 matrix *c = NULL;
 check_dimensions(a,b,"In gt\n");
 set(c,newmat(a->m,a->n));
 for(i=1; i<=a->m; ++i) 
      for(j=1; j<=a->n; ++j) {
        if(a->pm[i][j] > b->pm[i][j]) c->pm[i][j] = 1.0;
        else c->pm[i][j] = 0.0;
      }
 matrix_return(c);
}


matrix *gte(a,b)
matrix *a,*b;
{
 pointer_to_stack local_ptr = ans;
 int i,j;
 matrix *c = NULL;
 check_dimensions(a,b," In gte\n");
 set(c,newmat(a->m,a->n));
 for(i=1; i<=a->m; ++i) 
      for(j=1; j<=a->n; ++j) {
        if(a->pm[i][j] >= b->pm[i][j]) c->pm[i][j] = 1.0;
        else c->pm[i][j] = 0.0;
      }
 matrix_return(c);
}


matrix *lt(a,b)
matrix *a,*b;
{
 pointer_to_stack local_ptr = ans;
 int i,j;
 matrix *c = NULL;
 check_dimensions(a,b," In lt\n");
 set(c,newmat(a->m,a->n));
 for(i=1; i<=a->m; ++i) 
      for(j=1; j<=a->n; ++j) {
        if(a->pm[i][j] < b->pm[i][j]) c->pm[i][j] = 1.0;
        else c->pm[i][j] = 0.0;
      }
 matrix_return(c);
}


matrix *lte(a,b)
matrix *a,*b;
{
 pointer_to_stack local_ptr = ans;
 int i,j;
 matrix *c = NULL;
 check_dimensions(a,b," In lte\n");
 set(c,newmat(a->m,a->n));
 for(i=1; i<=a->m; ++i) 
      for(j=1; j<=a->n; ++j) {
        if(a->pm[i][j] <= b->pm[i][j]) c->pm[i][j] = 1.0;
        else c->pm[i][j] = 0.0;
      }
 matrix_return(c);
}


matrix *find(a,b)
matrix *a,*b;
/* retains elements of vector a only if b[j] is non-zero */ 
{
  pointer_to_stack local_ptr = ans;
  int n,j;
  matrix *c=NULL;
  check_dimensions(a,b," In find\n");
  n = a->n;
  for(j=1; j<=n; ++j) {
    if(true(b->pm[1][j])) {
       set(c,append_lr(c,d2m(a->pm[1][j])));
    }
  }
  matrix_return(c);
}


matrix *sign(a)
matrix *a;
/* for each element returns 1 if gt 0, 0 if equal 0, -1 if lt 0 */ 
{
  pointer_to_stack local_ptr = ans;
  int i,j;
  matrix *c=NULL;
  set(c,newmat(a->m,a->n));
  for(i=1; i<=a->m; ++i)  
    for(j=1; j<=a->n; ++j) {
      if(a->pm[i][j] > 0.0) c->pm[i][j] = 1.0;
      else if(a->pm[i][j] < 0.0) c->pm[i][j] = -1.0; 
    }
  matrix_return(c);
}


/**********************************************************************

Maximum and minimum

**********************************************************************/

matrix *maximum(a)
/* For a vector, returns maximum and its index.  For a matrix, returns
   the maximum in each column and the corresponding indices */
matrix *a;
{
 pointer_to_stack local_ptr = ans;
 int i,j;
 matrix *c = NULL;
 matrix *index = NULL;
 if (a->n == 1 || a->m == 1) {  /* vector maximum */
   set(c,newmat(1,1));
   c->pm[1][1] = -DBL_MAX;
   set(index,zeros(1,1));
   for(i=1; i<=a->m; ++i)
      for(j=1; j<=a->n; ++j)
        if(a->pm[i][j] > c->pm[1][1]) {
           c->pm[1][1] = a->pm[i][j];
           index->pm[1][1] = (float)((i==1)?j:i);
      }
   }
 else {  /* matrix case */
   set(c,newmat(1,a->n));
   set(index,ones(1,a->n));
   for(j=1; j<=a->n; ++j) c->pm[1][j] = -DBL_MAX;
   for(i=1; i<=a->m; ++i) for(j=1; j<=a->n; ++j)
      if(a->pm[i][j] > c->pm[1][j]) {
           c->pm[1][j] = a->pm[i][j];
           index->pm[1][j] = (float) i;
      }
 }
 matrix_return2(c,index);
}


matrix *minimum(a)
matrix *a;
{
 pointer_to_stack local_ptr = ans;
 int i,j,k,l;
 matrix *c = NULL;
 matrix *index = NULL;
 if (a->n == 1 || a->m == 1) { /*vector case */
   set(c,newmat(1,1));
   c->pm[1][1] = DBL_MAX;
   set(index,zeros(1,1));
   for(i=1; i<=a->m; ++i)
      for(j=1; j<=a->n; ++j)
        if(a->pm[i][j] < c->pm[1][1]) {
           c->pm[1][1] = a->pm[i][j];
           index->pm[1][1] = (i==1)?j:i;
      }
   }
 else {
   set(c,newmat(1,a->n));
   for(j=1; j<=a->n; ++j) c->pm[1][j] = DBL_MAX;
   set(index,ones(1,2));
   for(i=1; i<=a->m; ++i)
      for(j=1; j<=a->n; ++j)
        if(a->pm[i][j] < c->pm[1][j]) {
           c->pm[1][j] = a->pm[i][j];
           k = index->pm[1][1];
           l = index->pm[1][2];
           if(c->pm[1][j] < a->pm[k][l]) {
           index->pm[1][1] = i;index->pm[1][2] = j;}
      }
 }
 matrix_return2(c,index);
}




matrix *length(a)
matrix *a;
{
  pointer_to_stack local_ptr = ans;
  matrix *len=NULL;
  set(len,maximum(size(a)));
  matrix_return(len);
}


double vnorm(x)  /* vector norm (2-norm) */
matrix *x;
{
  double sum=0.0;
  int i;
  if(x->n == 1) {for(i=1;i<=x->m;++i) sum += x->pm[i][1]*x->pm[i][1]; }
  else if(x->m == 1) {for(i=1;i<=x->n;++i) sum += x->pm[1][i]*x->pm[1][i]; }
  else signal_block_error("Vnorm was given a matrix instead of a vector");
  return sqrt(sum);
}


double ssq(x)
matrix *x;
{
 double sum = 0.0;
 int i,j;
 for(i=1;i<=x->m;++i) for(j=1;j<=x->n;++j) sum += x->pm[i][j]*x->pm[i][j];
 return sum;
}



/**********************************************************************

Error Functions

**********************************************************************/

int check_dimensions (a, b, comment)
matrix *a, *b;
char *comment;
{
  char err_text[150];
  if (a->m != b->m || a->n != b->n) {
    sprintf(err_text,"Dimensions %d by %d incommensurate with %d by %d: ", a->m, a->n, b->m, b->n);
    strcat(err_text,comment);
    signal_block_error(err_text);
    return 0;
  }
  return 1;
}

/**********************************************************************

Test Functions

**********************************************************************/

void print_matrix(pmat,string)
matrix *pmat;
char *string;
{
  int i, j, maxn, maxm;
  printf ("\n\nMatrix %s",string);
  printf ("     ");
  if(pmat == NULL) {printf("Null matrix\n"); return;}
  else printf(" size =  %d by %d\n", pmat->m, pmat->n);

/* Maxn and maxm limit the maximum sizes of the matrix to be printed */  
  maxn = min(pmat->n, 8);
  maxm = min(pmat->m, 5);  

  for (j=1; j<=maxn; j++) {
    printf ("%-12d", j);
  }
  printf ("\n    ");
  for (j=1; j<=maxn; j++) {
    printf ("------------");
  }

  for (i=1; i<=maxm; ++i) {
    printf ("\n%d  |", i);
    for (j=1; j<=maxn; ++j) {
      printf ("%-12.3g", pmat->pm[i][j]);
    }
  }
  printf ("\n\n");
}


void print_stack()

{
  pointer_to_stack pstack;
  pstack = ans;
  while(pstack != NULL) {
    if(pstack->data == NULL) printf("Stack element %d is a null matrix\n",pstack);
    else printf("Stack element %d is a %d by %d matrix\n",pstack,pstack->data->m,pstack->data->n);
    pstack = pstack->next;
  }
  printf("End of stack\n");
  return;
}



void print_pool(pi)
int pi;
{
  pool_matrix *x;
  int i,j;
  x = mat_pool->pool_mat_address[pi];
  printf("Current state of pool %d is:\n\n",pi);
  printf ("     ");
  for (j=1; j<=x->n; j++) {
    printf ("%-12d", j);
  }
  printf ("\n    ");
  for (j=1; j<=x->n; j++) {
    printf ("------------");
  }
  for (i=1; i<=x->m; ++i) {
    printf ("\n%d  |", i);
    for (j=1; j<=x->n; ++j) {
      printf ("%-12.3g", x->pm[i][j]);
    }
    if(x->inuse[i]) printf(" inuse"); else printf(" available");
  }
  printf ("\n\n");
}


/**********************************************************************

One-dimensional minimization

**********************************************************************/

#define GOLD 1.618034
#define GLIMIT 100.0
#define TINY 1.0e-20
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a):-fabs(a))
#define ITMAX 100
#define CGOLD 0.3819660
#define ZEPS 1.0e-10
  
void mnbrak(ax,bx,cx,fa,fb,fc,func,opt_arg)
double *ax,*bx,*cx,*fa,*fb,*fc,(*func)();
matrix **opt_arg;
{
  double ulim,u,r,q,fu,dum;
  *fa = (*func)(*ax,opt_arg);
  *fb = (*func)(*bx,opt_arg);
  if(*fb>*fa) {
    SHFT(dum,*ax,*bx,dum)
    SHFT(dum,*fb,*fa,dum)
  }
  *cx=(*bx)+GOLD*(*bx-*ax);
  *fc=(*func)(*cx,opt_arg);
  while (*fb>*fc) {
    r = (*bx-*ax)*(*fb-*fc);
    q = (*bx-*cx)*(*fb-*fa);
    u = (*bx)-((*bx-*cx)*q-(*bx-*ax)*r)/(2.0*SIGN(max(fabs(q-r),TINY),q-r));
    ulim = (*bx)+GLIMIT*(*cx-*bx);
    if((*bx-u)*(u-*cx) > 0.0) {
      fu = (*func)(u,opt_arg);
      if(fu < *fc) {
	*ax=(*bx);
	*bx=u;
	*fa=(*fb);
	*fb=fu;
	return;
      } else if (fu > *fb) {
	*cx = u;
	*fc=fu;
	return;
      }
      u=(*cx)+GOLD*(*cx-*bx);
      fu=(*func)(u,opt_arg);
    } else if ((*cx-u)*(u-ulim) > 0.0) {
      fu=(*func)(u,opt_arg);
      if(fu < *fc) {
	SHFT(*bx,*cx,u,*cx+GOLD*(*cx-*bx))
	SHFT(*fb,*fc,fu,(*func)(u,opt_arg))
	}
    } else if ((u-ulim)*(ulim-*cx) >= 0.0) {
      u=ulim;
      fu=(*func)(u,opt_arg);
    } else {
      u=(*cx)+GOLD*(*cx-*bx);
      fu = (*func)(u,opt_arg);
    }
    SHFT(*ax,*bx,*cx,u)
    SHFT(*fa,*fb,*fc,fu)
  }
}

double brent(ax,bx,cx,fb,f,tol,xmin,opt_arg)
/* ax, bx, and cx are the bracketing values, fb is the value of function f at b,
   f is the function, tol is convergence tolerance. Output xmin is the value of x at minimum.
   Output brent is the function value at the minimum.  */ 
double (*f)(),*xmin,fb,ax,bx,cx,tol;
matrix **opt_arg;
{
  int iter;
  double a,b,d,etemp,fu,fv,fw,fx,p,q,r,tol1,tol2,u,v,w,x,xm;
  double e=0.0;
  a = (ax < cx ? ax : cx);
  b = (ax > cx ? ax : cx);
  x=w=v=bx;
  fw=fv=fx=fb;
  for(iter=1;iter<=ITMAX;iter++) {
    xm = 0.5*(a+b);
    tol2=2.0*(tol1=tol*fabs(x)+ZEPS);
    if(fabs(x-xm) <= (tol2-.5*(b-a))) {
      *xmin = x;
      return fx;
    }
    if(fabs(e) > tol1) {
      r=(x-w)*(fx-fv);
      q=(x-v)*(fx-fw);
      p=(x-v)*q-(x-w)*r;
      q=2.0*(q-r);
      if(q>0.0) p = -p;
      q = fabs(q);
      etemp = e;
      e=d;
      if(fabs(p) >= fabs(0.5*q*etemp) || p <= q*(a-x) || p >= q*(b-x))
	d = CGOLD*(e=(x >= xm ? a-x : b-x));
      else {
	d=p/q;
	u=x+d;
	if (u-a < tol2 || b-u < tol2)
	  d=SIGN(tol1,xm-x);
      }
    } else {
      d = CGOLD*(e=(x >= xm ? a-x : b-x));
    }
    u=(fabs(d) >= tol1 ? x+d : x+SIGN(tol1,d));
    fu=(*f)(u,opt_arg);
    if(fu <= fx) {
      if(u >= x) a=x; else b=x;
      SHFT(v,w,x,u)
      SHFT(fv,fw,fx,fu)
    } else {
	if (u < x) a=u; else b=u;
	if (fu <= fw || w == x) {
	  v=w;
	  w=u;
	  fv=fw;
	  fw=fu;
      } else if (fu <= fv || v == x || v == w) {
	v=u;
	fv=fu;
      }
    }
  }
  signal_block_error("Failed to converge one-dimensional search");
  *xmin=x;
  return fx;
}












