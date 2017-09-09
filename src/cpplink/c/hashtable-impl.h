/* Copyright Thomas Stegen 2003 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <stddef.h>

/*#include "../iterator/iterator.h"*/

/*use with the iterator_hashtable function*/
#define KEY    0
#define VALUE  1

/*
  This struct is not intended to be opaque, should only be used
  explicitly by the user when returned from iterate_hashtable.
  And then only key and value are of interest.
*/
struct element
{
   void *key;
   void *value;
   struct element *next;
};

/*
  Note that this struct should be regarded as opaque. Accessing and changing
  the fields directly leads to undefined behaviour.
*/
struct hashtable
{
   struct element **buckets; /*an array of pointers to buckets*/
   size_t num_buckets;
   unsigned num_elements;
   size_t (*hash)(void *elem);
   /* a function that copies source into a new element and returns
      a pointer to that element, this is for keys */
   void *(*cpkeyfun)(void *source); 
   /* a function that copies source into a new element and returns
      a pointer to that element, this is for values */
   void *(*cpvaluefun)(void *source);
   /* a function that compares keys. returns 1 on equality*/
   int (*keycmp)(void *key1, void *key2);
   /*The function that is used to free keys, defaults to free*/
   void (*key_free_function)(void *ptr);
   /*The function that is used to free values with*/
   void (*value_free_function)(void *ptr);
};

/* 
   initialize the table to contain have as many buckets as 
   specified by buckets. 
   hash is a pointer to the hash function
   cpkeyfun is the function used to copy keys
   cpvaluefun is the function used to copy values.
   keycmp is the function used to compare two keys.
   Returns true on success, false otherwi tse.
*/
int init_hashtable(struct hashtable *table, 
                   size_t buckets, 
                   size_t (*hash)(void *elem),
                   void *(*cpkeyfun)(void *source),
                   void *(*cpvaluefun)(void *source),
                   int (*keycmp)(void *key1, void *key2));

/*
   This function will be used to free key values. If this function is not
   called, free will be used by default. One usage is to have a dummy function
   that does not free anything, useful if automatic variables are used.
*/
void set_key_free_function_hashtable(struct hashtable *table, 
                                     void (*free_func)(void *ptr));

/*
   This function will be used to free value values. If this function is not
   used free will be used by default. One usage is to have a dummy function
   that does not free anything, useful if automatic variables are used.
*/
void set_value_free_function_hashtable(struct hashtable *table, 
                                       void (*free_func)(void *ptr));

/*
  insert a key-value pair into the table. Returns true on success, 
  false otherwise.
*/
int insert_hashtable(struct hashtable *table, void* key, void* value);

/*
  get the value associated with key. Returns NULL if no value were found.
*/
void *get_hashtable(struct hashtable *table, void *key);

/*
  remove the element associated with the given key.
  returns the value of the removed element. NULL if no element
  is found. The element must be freed if it was copied when
  added to the table. The key will be freed as specified by
  set_key_free_function.
*/
void *remove_hashtable(struct hashtable *table, void *key);

/*
  Delete the element associated with the given key.
  Returns 0 if the element is not found, non-zero on success.
  is found. The key and value  will be freed as specified by
  set_key_free_function and set_value_free_function.
*/
int delete_hashtable(struct hashtable *table, void *key);

/*
  Change the size of the hashtable. Returns false on failure.
  If a failure occurs the table remains untouched. This can
  be a time consuming operation if there are many elements.
*/
int rehash_hashtable(struct hashtable *table, size_t new_size); 


/*
  Returns the number of elements in the hashtable
*/
unsigned num_elements_hashtable(struct hashtable *table);

/*
  Return the fill factor of this hashtable
*/
double fill_factor_hashtable(struct hashtable *table);


/*
  Returns the number of collisions. That is, the number of elements inserted
  into a bucket where there are other elements already.
*/
unsigned collisions_hashtable(struct hashtable *table);


#if 0
int iterator_hashtable(struct hashtable *table, 
                       struct iterator *iterator,
                       int key_or_value);
#endif
/*
  Free all the memory used by the hashtable.
*/
void free_hashtable(struct hashtable *table);


#ifdef	__cplusplus
}
#endif

#endif /*HASHTABLE_H*/

