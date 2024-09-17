// implementing dequeue with doubly linked lists
//
// functions that needs to be implemented are:
// inserts
//
// insertFront() -> O(1)
// insertRear() -> O(1)
//
// deletions
//
// deleteFront() -> O(1)
// deleteRear() -> O(1)
//
// general
//
// getFront() -> O(1)
// getRear() -> O(1)
// isEmpty() -> O(1)
// size() -> O(1)
// erase() -> O(n)

// helper functions

// init()
// newNode()

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int val;
  struct Node *prev;
  struct Node *next;
};

struct Dequeue {
  struct Node *head;
  struct Node *tail;
  int size;
};

// helper
struct Node *newNode(int val) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->val = val;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

struct Dequeue *queueInit(int val) {
  struct Node *new_node = newNode(val);
  struct Dequeue *dequeue = ((struct Dequeue *)malloc(sizeof(struct Dequeue)));
  dequeue->head = new_node;
  dequeue->tail = new_node;
  dequeue->size = 1;
  return dequeue;
}

// insertions
struct Dequeue *insertFront(struct Dequeue *dequeue, int val) {
  struct Node *new_node = newNode(val);
  if (dequeue->head == NULL) {
    dequeue->head = new_node;
    dequeue->tail = new_node;
  } else {
    dequeue->head->prev = new_node;
    new_node->next = dequeue->head;
    dequeue->head = new_node;
  }
  dequeue->size += 1;
  return dequeue;
}

struct Dequeue *insertRear(struct Dequeue *dequeue, int val) {
  struct Node *new_node = newNode(val);
  if (dequeue->tail == NULL) {
    dequeue->head = new_node;
    dequeue->tail = new_node;
  } else {
    dequeue->tail->next = new_node;
    new_node->prev = dequeue->tail;
    dequeue->tail = new_node;
  }
  dequeue->size += 1;
  return dequeue;
}

// deletions
struct Dequeue *deleteFront(struct Dequeue *dequeue) {
  if (dequeue->head == NULL) {
    return dequeue;
  }
  struct Node *old_head = dequeue->head;
  dequeue->head = dequeue->head->next;
  if (dequeue->head != NULL) {
    dequeue->head->prev = NULL;
  } else {
    dequeue->tail = NULL;
  }
  free(old_head);
  dequeue->size -= 1;
  return dequeue;
}

struct Dequeue *deleteRear(struct Dequeue *dequeue) {
  if (dequeue->tail == NULL) {
    return dequeue;
  }
  struct Node *old_tail = dequeue->tail;
  dequeue->tail = dequeue->tail->prev;
  if (dequeue->tail != NULL) {
    dequeue->tail->next = NULL;
  } else {
    dequeue->head = NULL;
  }
  free(old_tail);
  dequeue->size -= 1;
  return dequeue;
}

// general
struct Node *getFront(struct Dequeue *dequeue) { return dequeue->head; }

struct Node *getRear(struct Dequeue *dequeue) { return dequeue->tail; }

bool isEmpty(struct Dequeue *dequeue) { return dequeue->size == 0; }

int getSize(struct Dequeue *dequeue) { return dequeue->size; }

struct Dequeue *erase(struct Dequeue *dequeue) {
  while (dequeue->head != NULL) {
    struct Node *nextItem = dequeue->head->next;
    free(dequeue->head);
    dequeue->head = nextItem;
  }
  dequeue->tail = NULL;
  dequeue->size = 0;
  return dequeue;
}

int main() {
  struct Dequeue *dequeue = queueInit(10);

  // Test insertions
  dequeue = insertFront(dequeue, 5);
  dequeue = insertRear(dequeue, 15);

  // Test size
  printf("Size: %d\n", getSize(dequeue)); // Expected: 3

  // Test front and rear
  printf("Front: %d\n", getFront(dequeue)->val); // Expected: 5
  printf("Rear: %d\n", getRear(dequeue)->val);   // Expected: 15

  // Test deletions
  dequeue = deleteFront(dequeue);
  printf("After deleteFront, size: %d\n", getSize(dequeue)); // Expected: 2
  printf("New Front: %d\n", getFront(dequeue)->val);         // Expected: 10

  dequeue = deleteRear(dequeue);
  printf("After deleteRear, size: %d\n", getSize(dequeue)); // Expected: 1
  printf("New Rear: %d\n", getRear(dequeue)->val);          // Expected: 10

  // Test erasing the dequeue
  dequeue = erase(dequeue);
  printf("After erase, isEmpty: %d\n", isEmpty(dequeue)); // Expected: 1 (true)

  free(dequeue);
  return 0;
}
