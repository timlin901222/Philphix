#include "hashtable.h"

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
HashTable *createHashTable(int size, unsigned int (*hashFunction)(void *),
                           int (*equalFunction)(void *, void *)) {
  int i = 0;
  HashTable *newTable = malloc(sizeof(HashTable));
  if (NULL == newTable) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  newTable->size = size;
  newTable->buckets = malloc(sizeof(struct HashBucketEntry *) * size);
  if (NULL == newTable->buckets) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  for (i = 0; i < size; i++) {
    newTable->buckets[i] = NULL;
  }
  newTable->hashFunction = hashFunction;
  newTable->equalFunction = equalFunction;
  return newTable;
}

/* Task 1.2 */
void insertData(HashTable *table, void *key, void *data) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket location with table->hashFunction.
  // 2. Allocate a new hash bucket entry struct.
  // 3. Append to the linked list or create it if it does not yet exist. 

  int i;
  i = table->hashFunction(key);
  assert(i<table->size);
  struct HashBucketEntry entry = {
    .key = key,
    .data = data,
    .next = NULL
  };
  if (table->buckets[i] == NULL) {
    table->buckets[i] = &entry;
    return;
  }
  while (table->buckets[i]->next != NULL) {
    table->buckets[i] = table->buckets[i]->next;
  }
    table->buckets[i]->next = &entry;
    
  
}

/* Task 1.3 */
void *findData(HashTable *table, void *key) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket with table->hashFunction.
  // 2. Walk the linked list and check for equality with table->equalFunction.
  int i = table->hashFunction(key);
  while (!table->equalFunction(table->buckets[i]->key, key) && table->buckets[i] != NULL) {
    table->buckets[i] = table->buckets[i]->next;

  }
  if (table->buckets[i] == NULL) {
    return 0;
  }
  else {
    return table->buckets[i];
  }

}

/* Task 2.1 */
unsigned int stringHash(void *str) {
  // -- TODO --
  fprintf(stderr, "need to implement stringHash\n");
  /* To suppress compiler warning until you implement this function, */
  unsigned long hash = 5381;
    int c;

    char *s = str;

    while ((c = *s++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
  
}

/* Task 2.2 */
int stringEquals(void *s1, void *s2) {
  int i;
  // -- TODO --
  fprintf(stderr, "You need to implement stringEquals");
  /* To suppress compiler warning until you implement this function */
  if (sizeof(s1) != sizeof(s2)) {
    return 0;
  }
 
  for (i = 0; i < sizeof(s1); i++) {
    if (strcmp(s1, s2) != 0) {
      return 0;
    }
  }
  
  return 1;
}