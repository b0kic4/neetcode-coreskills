#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  char *key;
  int value;
  struct Node *next;
};

struct Bucket {
  struct Node *head;
};

struct Hashtable {
  struct Bucket *buckets; // -> Array of buckets
  int size;               // -> Number of buckets
};

struct Node *newNode(const char *name, int bday) {
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  new_node->key = strdup(name); // Allocating memory for the string key
  new_node->value = bday;
  new_node->next = NULL;
  return new_node;
}

struct Bucket *newBucket(struct Node *newNode) {
  struct Bucket *new_bucket = (struct Bucket *)malloc(sizeof(struct Bucket));
  new_bucket->head = newNode;
  return new_bucket;
}

struct Hashtable *createHashtable(int size) {
  struct Hashtable *hashtable =
      (struct Hashtable *)malloc(sizeof(struct Hashtable));
  hashtable->size = size;
  hashtable->buckets = (struct Bucket *)malloc(size * sizeof(struct Bucket));

  for (int i = 0; i < size; i++) {
    hashtable->buckets[i].head = NULL;
  }

  return hashtable;
}

int hashFunction(const char *str, int size) {
  int hash = 0;
  while (*str) {
    hash = (hash + *str) % size; // Sum ASCII values of the characters
    str++;
  }
  return hash;
}

void insert(struct Hashtable *htable, const char *key, int val) {
  int hashedKey = hashFunction(key, htable->size);
  struct Node *new_node = newNode(key, val);

  if (htable->buckets[hashedKey].head == NULL) {
    htable->buckets[hashedKey].head = new_node;
  } else {
    new_node->next = htable->buckets[hashedKey].head;
    htable->buckets[hashedKey].head = new_node;
  }
}

int *search(struct Hashtable *htable, const char *key) {
  int hashedKey = hashFunction(key, htable->size);

  struct Node *current = htable->buckets[hashedKey].head;

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return &current->value;
    }
    current = current->next;
  }

  return NULL;
}

void *delete(struct Hashtable *htable, const char *key) {
  int hashedKey = hashFunction(key, htable->size);
  struct Node *current = htable->buckets[hashedKey].head;
  struct Node *previous = NULL;

  // Traversing the linked list in the bucket to find the key
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      // Unlink the node from the list
      if (previous == NULL) {
        htable->buckets[hashedKey].head = current->next;
      } else {
        previous->next = current->next;
      }

      free(current->key); // Free the key (if dynamically allocated)
      free(current);      // Free the node

      return NULL;
    }

    previous = current;
    current = current->next;
  }
  return NULL;
}

int main() {
  struct Hashtable *hashtable = createHashtable(10);

  // Test 1: Insert key-value pairs (name as key, birthday as value)
  insert(hashtable, "Alice", 19950115); // Alice -> 15th January 1995
  insert(hashtable, "Bob", 19880612);   // Bob -> 12th June 1988
  insert(hashtable, "Eve", 20000101);   // Eve -> 1st January 2000

  // Test 2: Search for existing keys
  int *bday = search(hashtable, "Alice");
  if (bday != NULL) {
    printf("Alice's birthday: %d\n", *bday); // Should print: 19950115
  } else {
    printf("Alice not found!\n");
  }

  bday = search(hashtable, "Bob");
  if (bday != NULL) {
    printf("Bob's birthday: %d\n", *bday); // Should print: 19880612
  } else {
    printf("Bob not found!\n");
  }

  bday = search(hashtable, "Eve");
  if (bday != NULL) {
    printf("Eve's birthday: %d\n", *bday); // Should print: 20000101
  } else {
    printf("Eve not found!\n");
  }

  // Test 3: Search for a non-existing key
  bday = search(hashtable, "John");
  if (bday != NULL) {
    printf("John's birthday: %d\n", *bday);
  } else {
    printf("John not found!\n"); // Should print: John not found!
  }

  // Test 4: Delete a key
  delete (hashtable, "Alice");
  bday = search(hashtable, "Alice");
  if (bday != NULL) {
    printf("Alice's birthday: %d\n", *bday);
  } else {
    printf("Alice not found after deletion!\n"); // Should print this
  }

  // Test 5: Delete another key
  delete (hashtable, "Bob");
  bday = search(hashtable, "Bob");
  if (bday != NULL) {
    printf("Bob's birthday: %d\n", *bday);
  } else {
    printf("Bob not found after deletion!\n"); // Should print this
  }

  // Free the memory allocated for the hashtable and its buckets
  for (int i = 0; i < hashtable->size; i++) {
    struct Node *current = hashtable->buckets[i].head;
    while (current != NULL) {
      struct Node *next = current->next;
      free(current->key); // Free the dynamically allocated key
      free(current);      // Free the node
      current = next;
    }
  }
  free(hashtable->buckets);
  free(hashtable);

  return 0;
}
