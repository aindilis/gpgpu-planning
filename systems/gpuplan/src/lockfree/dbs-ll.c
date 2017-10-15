//#include <config.h>
#include <stdlib.h>
#include <stdio.h>


#include <malloc.h>
#include <stdint.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <errno.h>

// #include <runtime.h>
#include "dbs-ll.h"

int
posix_memalign(void **memptr, size_t alignment, size_t size)
{
  void *ptr = NULL;
  int error = 0;
  
  if (alignment == 0 ||
      (alignment & (sizeof (void *) - 1)) != 0 ||
      (alignment & (alignment - 1)) != 0)
    error = EINVAL;
  else if (size != 0 &&
	   (ptr = memalign(alignment, size)) == NULL)
    error = ENOMEM;
  
  *memptr = ptr;
  return (error);
}

static const int        TABLE_SIZE = 29;

static const uint32_t   EMPTY = 0;
static const uint32_t   WRITE_BIT = 1 << 31;
static const uint32_t   WRITE_BIT_R = ~(1 << 31);
static const uint32_t   BITS_PER_INT = sizeof (int) * 8;

struct dbs_ll_s {
    size_t              length; //length of the state 
    size_t              bytes; //number of bytes in state
		size_t							hashLength;
    size_t              size;
    size_t              threshold;
    uint32_t            mask;
    char                *data;
    uint32_t           *table;
    hash32_f            hash32;
    pthread_key_t       local_key;
};

typedef struct local_s {
    stats_t             stat;
} local_t;


size_t
inc (size_t x)
{
    return x + 1;
}
size_t
dec (size_t x)
{
    return x - 1;
}
int
lt (size_t x, size_t y)
{
    return x < y;
}
int
gte (size_t x, size_t y)
{
    return x >= y;
}

typedef                 size_t (*op_f) (size_t x);
typedef int             (*comp_f) (size_t x, size_t y);

/**
 * Returns operators to walk up or down a cache line, depending on the starting
 * location.
 */
static inline int
walk_the_line (int idx, op_f * op, comp_f * comp)
{                                      // good movie
    size_t              line = (idx & CACHE_LINE_INT_MASK);
    if (idx - line < (CACHE_LINE_INT >> 1)) {
        *op = inc;
        *comp = lt;
        line += CACHE_LINE_INT;
    } else {
        *op = dec;
        *comp = gte;
    }
    return line;
}

local_t *
get_local (dbs_ll_t dbs)
{
    local_t            *loc = pthread_getspecific (dbs->local_key);
    if (loc == NULL) {
      posix_memalign((void**) &loc, CACHE_LINE_SIZE, sizeof (local_t));
        memset (loc, 0, sizeof (local_t));
        pthread_setspecific (dbs->local_key, loc);
    }
    return loc;
}

uint32_t
DBSLLmemoized_hash (const dbs_ll_t dbs, const int idx)
{
    return dbs->table[idx];
}

unsigned char * 
getDataPointer(const dbs_ll_t dbs, int idx)
{
	return &dbs->data[idx*dbs->length];
}

int
DBSLLlookup_hash (const dbs_ll_t dbs, const int *v, int *ret, uint32_t *hash, char insert)
{
    local_t            *loc = get_local (dbs);
    stats_t            *stat = &loc->stat;
    size_t              seed = 0;
    size_t              l = dbs->length;
    size_t              b = dbs->bytes;
		size_t							hL = dbs->hashLength;
    uint32_t            hash_rehash = hash ? *hash : dbs->hash32 ((char *)v, hL, 0);
    uint32_t            hash_memo = hash_rehash;
		//printf("hash value %i length %i \n ",hash_memo,(int)b);
    //avoid collision of memoized hash with reserved values EMPTY and WRITE_BIT
    while (EMPTY == hash_memo || WRITE_BIT == hash_memo)
        hash_memo = dbs->hash32 ((char *)v, hL, ++seed);
    uint32_t            WAIT = hash_memo & WRITE_BIT_R;
    uint32_t            DONE = hash_memo | WRITE_BIT;
    op_f                op;
    comp_f              comp;
    while (seed < dbs->threshold) {
        size_t              idx = hash_rehash & dbs->mask;
        size_t              line = walk_the_line (idx, &op, &comp);
        for (; comp (idx, line); idx = op (idx) & dbs->mask) {
            uint32_t           *bucket = &dbs->table[idx];
            if (EMPTY == *bucket) {
								if (!insert) return 0;
                if (cas (bucket, EMPTY, WAIT)) {
                    memcpy (&dbs->data[idx * l], v, b);
                    atomic_write (bucket, DONE);
                    stat->elts++;
                    *ret = idx;
                    return 0;
                }
            }
            if (DONE == (atomic_read (bucket) | WRITE_BIT)) {
                while (WAIT == atomic_read (bucket)) {}
                if (0 == memcmp (&dbs->data[idx * l], v, hL)) {
                    *ret = idx;
                    return 1;
                }
            }
            stat->misses++;
        }
        hash_rehash = dbs->hash32 ((char *)v, hL, hash_rehash + (seed++));
        stat->rehashes++;
    }
    printf("Hash table full");
    exit(1);
}

char *
DBSLLget (const dbs_ll_t dbs, const int idx, int *dst)
{
    *dst = dbs->table[idx];
    return &dbs->data[idx * dbs->length];
}

int
DBSLLlookup_ret (const dbs_ll_t dbs, const int *v, int *ret,char insert)
{
    return DBSLLlookup_hash (dbs, v, ret, NULL,insert);
}

int
DBSLLlookup (const dbs_ll_t dbs, const int *vector)
{
    int                *ret = malloc (sizeof (*ret));
    DBSLLlookup_hash (dbs, vector, ret, NULL,0);
    return *ret;
}

dbs_ll_t
DBSLLcreate (int length,int hashLength,int size)
{
  printf ("creating\n");
    return DBSLLcreate_sized (length, size, (hash32_f)SuperFastHash,hashLength);
}

dbs_ll_t
DBSLLcreate_sized (int length, int size, hash32_f hash32,int hashLength)
{
  dbs_ll_t dbs;
  printf ("creating size %d (%d hashing) %d \n", length, hashLength, size);

  posix_memalign((void**) &dbs,CACHE_LINE_SIZE, sizeof (struct dbs_ll_s));
    dbs->length = length;
    dbs->hash32 = hash32;
		dbs->hashLength = hashLength;
    dbs->bytes = length * sizeof (char); 
    dbs->size = 1 << size;
	printf ("space for %d elements, (%lu MB index, %lu MB data) \n",dbs->size,dbs->size*4/1024/1024,dbs->size*length/1024/1024);
    dbs->threshold = dbs->size / 100;
    dbs->mask = dbs->size - 1;
    posix_memalign((void**)&dbs->table,CACHE_LINE_SIZE, sizeof (uint32_t[dbs->size]));
    posix_memalign((void**)&dbs->data,CACHE_LINE_SIZE, sizeof (char[dbs->size * length]));
    memset (dbs->table, 0, sizeof (uint32_t[dbs->size]));
    pthread_key_create (&dbs->local_key, free);
    return dbs;
}

void
DBSLLfree (dbs_ll_t dbs)
{
    free (dbs->data);
    free (dbs->table);
    free (dbs);
}

stats_t *
DBSLLstats (dbs_ll_t dbs)
{
    stats_t            *res = malloc (sizeof (*res));
    stats_t            *stat = &get_local (dbs)->stat;
    memcpy (res, stat, sizeof (*res));
    return res;
}
