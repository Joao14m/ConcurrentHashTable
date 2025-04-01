#include <pthread.h>

typedef struct __Zem_t {
    int value;
    pthread_cond_t  cond;
    pthread_mutex_t lock;
} Zem_t;

typedef Zem_t sem_t;

typedef struct _rwlock_t {
    sem_t writelock;
    sem_t lock;
    int readers;
} rwlock_t;

void Zem_init(Zem_t *z, int value);

void Zem_wait(Zem_t *z);

void Zem_post(Zem_t *z);

void rwlock_init(rwlock_t *lock);

void rwlock_acquire_readlock(rwlock_t *lock);

void rwlock_release_readlock(rwlock_t *lock);

void rwlock_acquire_writelock(rwlock_t *lock);

void rwlock_release_writelock(rwlock_t *lock);

void *reader(void *arg);

void *writer(void *arg);