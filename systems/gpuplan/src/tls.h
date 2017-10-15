#ifndef THREADED_H
#define THREADED_H

/**
\file tls.h
\brief Thread local storage management

\par The downside of thread local storage is that it
cannot be used as a member of a struct. This
structure remedies that by managing tls pointer
arrays and assigning global unique identifiers to
owning structs

\par a user has to do two things:
    - declare a __thread variable as pointer to desired type
    - associated a tls_t with the struct whose instances local storage for the 
      desired type

\par Currently only flat structures are supported which can be allocated by 
manager itself. Therefore the size of a single storage unit has to be declared 
when creating the storage manager.
*/


#ifndef CPU_SET
#define CPU_SET __CPU_SET
#endif
#ifndef CPU_ZERO
#define CPU_ZERO __CPU_ZERO
#endif


/**
\brief These constructs prevent the compiler from optimizing (reordering) reads
and writes to memory location, which causes loss of atomicity properties.
*/
#define atomic_read(v)      (*(volatile uint32_t *)v)
#define atomic_write(v,a)   (*(volatile uint32_t *)v = (a))

#ifdef __X86_64__
#define atomic64_read(v)    (*(volatile uint64_t *)v)
#define atomic64_write(v,a) (*(volatile uint64_t *)v = (a))
#endif

/**
\def cache line size to optimize memory allocations for
*/
#define CACHE_LINE 6
static const size_t CACHE_LINE_SIZE = 1 << CACHE_LINE;
static const size_t CACHE_LINE_INT = (1 << CACHE_LINE) / sizeof (int);
static const size_t CACHE_LINE_INT_MASK =
    -((1 << CACHE_LINE) / sizeof (int));

#define cas(a, b, c) __sync_bool_compare_and_swap(a,b,c)
#define cas_ret(a, b, c) __sync_val_compare_and_swap(a,b,c)
#define fetch_or(a, b) __sync_fetch_and_or(a,b)
#define fetch_and(a, b) __sync_fetch_and_and(a,b)
#define fetch_add(a, b) __sync_fetch_and_add(a,b)
#define add_fetch(a, b) __sync_add_and_fetch(a,b)
#define fetch_sub(a, b) __sync_fetch_and_sub(a,b)
#define sub_fetch(a, b) __sync_sub_and_fetch(a,b)

#ifdef __x86_64__
#define atomic_ptr_read(v)      ((void*)(*(volatile uint64_t *)v)
#define atomic_ptr_write(v,a)   (*(volatile uint32_t *)v = (uint64_t)(a))
#else
#define atomic_ptr_read(v)      ((void*)(*(volatile uint32_t *)v)
#define atomic_ptr_write(v,a)   (*(volatile uint32_t *)v = (uint32_t)(a))
#endif


/**
\def maximum number of instances per storage supported by instance manager

\par enlarging this increases memory usage for the tls
*/
#define TLS_MAX_INSTANCES 128

/**
\struct general struct for maintaining statistics on storage  
*/
typedef struct stats_s {
    size_t              elts;
    size_t              misses;
    size_t              tests;
    size_t              rehashes;
    long long           compressed;
    size_t              mincomp;
    size_t              maxcomp;
    size_t              cache_hits;
    size_t              cache_misses;
} stats_t;

extern void add_stats(stats_t *res, stats_t *stat);

/**
\typedef Thread local storage manager
*/
typedef struct tls_s tls_t;

/**
\brief TLS Constructor

\param owner The owner struct to collect instances from
\param size The size of a single storage in the TLS
*/
extern tls_t       *TLScreate (void *owner, size_t size);

/**
\brief Gives a reference to the storage unit allocated for an instance.

\param tls the tls associated with the instance
\param tls_ref reference to the __thread variable that this tls_t was created for
\return a pointer to the correct tls unit
*/
extern void        *TLSgetInstanceRef (tls_t * tls);

/**
\todo implement following methods to handle more complex structs in tls
*/
typedef void       *(*constructor_f) ();
extern tls_t       *TLScreate_constr (void *owner,
                                      constructor_f constructor);

extern void        *TLSgetInstance (tls_t * tls);

extern void         TLSsetInstance (tls_t * tls);

extern int          tls_get_cpu_count();

#endif
