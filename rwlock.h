#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

typedef struct _rwlock_t {
    sem_t writelock;
    sem_t lock;
    int readers;
} rwlock_t;

typedef struct hash_struct {
    uint32_t hash;
    char name[50];
    uint32_t salary;
    struct hash_struct *next;
} hashRecord;

void rwlock_init(rwlock_t *lock);

void rwlock_acquire_readlock(rwlock_t *lock);

void rwlock_release_readlock(rwlock_t *lock);

void rwlock_acquire_writelock(rwlock_t *lock);

void rwlock_release_writelock(rwlock_t *lock);

void *reader(void *arg);

void *writer(void *arg);