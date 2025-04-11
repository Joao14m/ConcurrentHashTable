#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "rwlock.h"
#include "utils.c"

uint32_t jenkins_one_at_a_time_hash(const char *key) {
    uint32_t hash = 0;
    
    while (*key) {
      hash += (unsigned char)(*key);
      hash += (hash << 10);
      hash ^= (hash >> 6);
      key++;
    }
    
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}  

hashRecord *head = NULL;
int read_loops;
int write_loops;
int counter = 0;
rwlock_t mutex;

static const char COMMAND_FILE[] = "commands.txt";
static const char OUTPUT_FILE[] = "output.txt"; 

pthread_mutex_t condMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

FILE* fp;
FILE* out;

int lockAcquire = 0;
int lockRelease = 0;

void insert(char *name, uint32_t salary){

}

void delete(char *name){

}

uint32_t search(char *name){

}

int main(int argc, char *argv[]) {
    fp = fopen(COMMAND_FILE, "r");
    out = fopen(OUTPUT_FILE, "w");

    if(fp == NULL){
        fprintf(stderr, "Error: File not found");
        exit(EXIT_FAILURE);
    }

    if(out == NULL){
        fprintf(stderr, "Error opening file");
        exit(EXIT_FAILURE);
    }

    rwlock_init(&mutex);

    int numThreads = 0;
    char strs[2][50];
    char command[50]; 

    pthread_t threads[numThreads];
    hashRecord* arr = malloc(sizeof(hashRecord));
    
    fscanf(fp, "%[^,],%d,%s", strs[0], &numThreads, strs[1]);
    fprint(out, "Running %d threads\n", numThreads);

    for(int i = 0; i < numThreads; i++){
        fscanf(fp, "%[^,],%[^,],%d", command, arr->name, &arr->salary);

        if(strcmp(command, "insert") == 0){
            pthread_create(&threads[i], NULL, insert_t, arr);
        } else if(strcmp(command, "delete") == 0){
            pthread_create(&threads[i], NULL, delete_t, arr);
        } else if(strcmp(command, "search") == 0){
            pthread_create(&threads[i], NULL, search_t, arr);
        } else {
            free(arr);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < numThreads; i++){
        pthread_join(threads[i], NULL);
    }

    fprintf(out, "Finished all threads.\n");
    fprintf(out, "Number of lock acquisitions: %d\n", lockAcquire);
    fprintf(out, "Number of lock releases: %d\n", lockRelease);

    free(arr);
    fclose(fp);
    fclose(out);

    return 0;
}
