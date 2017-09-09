#include <stdlib.h>

#include "hashtable-impl.h"
/*#include "../iterator/iterator.h"*/

#define HASH(table, key) ((table)->hash(key) % (table)->num_buckets)


size_t hash_function (struct hashtable *table, void *key)
{
  return ((table)->hash(key) % (table)->num_buckets);
}


int init_hashtable(struct hashtable *table, 
                   size_t buckets, 
                   size_t (*hash)(void *elem),
                   void *(*cpkeyfun)(void *source),
                   void *(*cpvaluefun)(void *source),   
                   int (*keycmp)(void *key1, void *key2))
{
   size_t i;

   table->buckets = malloc(sizeof(*(table->buckets)) * buckets);
   if(!(table->buckets))
   {
      return 0;
   }
   table->num_buckets = buckets;
   table->num_elements = 0;
   table->hash = hash;
   table->cpkeyfun = cpkeyfun;
   table->cpvaluefun = cpvaluefun;
   table->keycmp = keycmp;

   /*initialize the elements in the table->buckets array*/
   for(i = 0;i < buckets;i++)
   {
      table->buckets[i] = NULL;
   } 

   /* Default values */
   table->key_free_function = free;
   table->value_free_function = free;

   return 1;
}

void set_key_free_function_hashtable(struct hashtable *table,
                                     void (*free_func)(void *ptr))
{
   table->key_free_function = free_func;
}

void set_value_free_function_hashtable(struct hashtable *table,
                                       void (*free_func)(void *ptr))
{
   table->value_free_function = free_func;
}

int insert_hashtable(struct hashtable *table, void* key, void* value)
{
   size_t ind;
   void *nkey;
   void *nvalue;
   struct element *elem;

   ind = hash_function(table,key);
   nkey = table->cpkeyfun(key);
   nvalue = table->cpvaluefun(value);
   elem = malloc(sizeof *elem);

   if(!elem || !nvalue || !nkey)
   {
      free(elem);
      table->value_free_function(nvalue);
      table->key_free_function(nkey);
      return 0;
   }
   /*all memory handling done, now put the key-value pair into the table */
   table->num_elements++;
   elem->key = nkey;
   elem->value = nvalue;

   /*add element to the front of the list*/
   elem->next = table->buckets[ind];
   table->buckets[ind] = elem;
   return 1;
}


void *get_hashtable(struct hashtable *table, void *key)
{
   size_t ind;
   struct element *tmp;

   ind = hash_function(table, key);
   if((tmp = table->buckets[ind]) == NULL)
   {
      /*There are no elements in this bucket*/
      return NULL;
   }

   /*search the rest of the bucket*/
   while((tmp) != NULL)
   {
      if(!(table->keycmp(key, tmp->key)))
      {
         return tmp->value;
      }
      tmp = tmp->next;
   }
   return NULL;
}


void *remove_hashtable(struct hashtable *table, void *key)
{
   size_t ind = hash_function(table, key);
   struct element *elem = table->buckets[ind];
   struct element *prev;

   if(elem == NULL)
   {
      /*no element with the given key*/
      return NULL;
   }

   /*check if it is the first element*/
   if(!(table->keycmp(key, elem->key)))
   {
      /*The reason for this check of the first element is that
        the buckets field needs to be changed. And that cannot 
        be done through the prev pointer
      */
      void *tmp = elem->value;
      table->buckets[ind] = elem->next;
      table->key_free_function(elem->key);
      free(elem);
      table->num_elements--;
      return tmp;
   }

   prev = elem;
   elem = elem->next;
   while(elem != NULL)
   {
      if(!(table->keycmp(key, elem->key)))
      {
         /*found the right element*/
         void *tmp = elem->value;
         prev->next = elem->next;
         table->key_free_function(elem->key);
         free(elem);
         table->num_elements--;
         return tmp;
      }
      prev = elem;
      elem = elem->next;
   }

   /*No element with the given key*/
   return NULL;
}

int delete_hashtable(struct hashtable *table, void *key)
{
   void *e = remove_hashtable(table, key);
   
   if(e == NULL)
   {
      return 0;
   }
   table->value_free_function(e);
   return 1;
}
#if 0
int rehash_hashtable(struct hashtable *table, size_t new_size)
{
   struct iterator keys;
   struct iterator values;
   struct hashtable tmp; /*A temporary hashtable*/
   size_t i;
   if(!iterator_hashtable(table, &keys, KEY)
      || !iterator_hashtable(table, &values, VALUE))
   {
      return 0;
   }

   tmp = *table;
   tmp.buckets = malloc(new_size * sizeof *(tmp.buckets));
   tmp.num_buckets = new_size;
   if(tmp.buckets == NULL)
   {
      return 0;
   }

   /*All buckets must be initialized to NULL*/
   for(i = 0;i < new_size;i++)
   {
      tmp.buckets[i] = NULL;
   } 

   /*insert everything into the new buckets*/
   while(more_iterator(&keys))
   {
      if(!insert_hashtable(&tmp, 
                           next_iterator(&keys), 
                           next_iterator(&values)))
      {
         free(tmp.buckets);
         return 0;
      }
   }
   table->num_buckets = new_size;
   free(table->buckets);
   table->buckets = tmp.buckets;
   free_iterator(&keys);
   free_iterator(&values);

   return 1;
}
#endif
unsigned num_elements_hashtable(struct hashtable *table)
{
   return table->num_elements;
}

double fill_factor_hashtable(struct hashtable *table)
{
   return (((double)table->num_elements)) / table->num_buckets;
}

unsigned collisions_hashtable(struct hashtable *table)
{
   unsigned count = 0;
   size_t i;
   struct element *e;

   for(i = 0;i < table->num_buckets;i++)
   {
      /* Check if the bucket is empty */
      if(table->buckets[i] != NULL)
      {
         /* Point to first element in bucket */
         e = table->buckets[i];
         /* This will skip the first element in the bucket which is 
            what we want */
         while((e = e->next) != NULL)
         {
            count++;
         }
      }
   }
   return count;
}

static void free_bucket(struct hashtable *table, struct element *elem)
{
   if(elem->next != NULL)
   {
      free_bucket(table, elem->next);
   }
   table->key_free_function(elem->key);
   table->value_free_function(elem->value);
   free(elem);
}


void free_hashtable(struct hashtable *table)
{
   size_t i;
   /*first all elements must be freed*/
   for(i = 0;i < table->num_buckets;i++)
   {
      if(table->buckets[i] != NULL)
      {
         free_bucket(table, table->buckets[i]);
      }
   }
   /*then free the buckets*/
   free(table->buckets);
}


/*  code to handle iterator below here */
#if 0
struct iterator_data
{
   struct hashtable *table; /*the table that is being iterated over*/
   size_t bucket; /*the bucket of the next element to return*/
   struct element *next; /*The element to return next*/
   struct element *previous; /*needed for remove and delete*/
   int what; /*KEY if keys should be returned, VALUE if values are returned*/
};

static int iterator_more(void *vdata)
{
   struct iterator_data *data = vdata;
   return !!data->next;
}


static void *iterator_next(void *vdata)
{
   /*This can perhaps be made nicer by decoding the data before
     starting processing. Something for another time perhaps :) */
   struct iterator_data *data = vdata;
   void *retval;
   
   /*Check if there actually is a next element and if there is, return it*/
   if(data->next != NULL)
   {
      retval = (data->what == KEY) ? (data->next->key) :(data->next->value);
      data->previous = data->next;
   }
   else
   {
      return NULL;
   }
   /*find the next element*/
   /*are there more elements in this bucket*/
   if(data->next->next == NULL)
   {
      /*find the next non-empty bucket*/
      do
      {
         if(data->table->buckets[++data->bucket] != NULL)
         {
            /*found it*/
            break;
         }
      } while(data->bucket < data->table->num_buckets);
      /*Did we find a bucket or did we just loop over the end*/
      if(data->bucket >= data->table->num_buckets)
      {
         data->next = NULL;
      }
      else
      {
         /*The next element is the first one in the new bucket*/
         data->next = data->table->buckets[data->bucket];
      }
   }
   else
   {
      /*The next element is in this bucket*/
      data->next = data->next->next;
   }
   return retval;
}

/*
  Note that this will delete the key.
*/
static void *iterator_remove(void *vdata)
{
   struct iterator_data *data = vdata;
   /*can only remove when iterating over keys and when there is 
     a previous element*/
   if((data->what != KEY) || (data->previous == NULL))
   {
      return NULL;
   }
   return remove_hashtable(data->table, data->previous->key);
}

/* This just returns 0*/
static int iterator_delete(void *vdata)
{
   struct iterator_data *data = vdata;
   /*can only delete when iterating over keys and when there is 
     a previous element*/
   if((data->what != KEY) || (data->previous == NULL))
   {
      return 0;
   }
   return delete_hashtable(data->table, data->previous->key);
}


static void iterator_free(void *vdata)
{
   free(vdata);
}

int iterator_hashtable(struct hashtable *table, 
                       struct iterator *iterator,
                       int key_or_value)
{
   struct iterator_data *data;
   data = malloc(sizeof *data);
   if(data == NULL)
   {
      return 0;
   }

   data->what     = key_or_value;
   data->table    = table;
   data->previous = NULL;
   data->bucket   = 0;

   /*No need for finding the first element when there are no elements*/
   if(table->num_elements != 0)
   {
      /*set up the next and bucket fields*/
      while(table->buckets[data->bucket] == NULL)
      {
         data->bucket++;
      }
      data->next = table->buckets[data->bucket];
   }

   iterator->data    = data;
   iterator->more    = iterator_more;
   iterator->next    = iterator_next;
   iterator->remove  = iterator_remove;
   iterator->delete  = iterator_delete;
   iterator->free_me = iterator_free;

   return 1;
}
#endif
