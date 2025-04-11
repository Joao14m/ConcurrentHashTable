#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "rwlock.h"

void* insert_t(void* arg){
    hashRecord* record = (hashRecord*)arg;
    insert(record->name, record->salary);
    return NULL;
}

void* search_t(void* arg){
    hashRecord* record = (hashRecord*)arg;
    hashRecord* s = search(record->name);
    
    if(s != NULL){
        print("Record found");
    } else {
        print("Record not found");
    }
    return NULL; 
}

void* delete_t(void* arg) {
    hashRecord* record = (hashRecord*) arg;
    delete(record->name);
    return NULL;
}