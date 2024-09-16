#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int val;
  struct Node *next;
};

// Function declarations
struct Node *newNode(int val);
int getLenght(struct Node *head);
void traverse(struct Node *head);
bool searching(struct Node *head, int target);
void printList(struct Node *head);

// Insertion functions
struct Node *insertAtBegining(struct Node *head, int val);
struct Node *insertAtEnd(struct Node *head, int val);
struct Node *insertAtPos(struct Node *head, int val, int pos);

// Deletion functions
struct Node *deleteAtEnd(struct Node *head);
struct Node *deleteAtBegining(struct Node *head);
struct Node *deleteAtPos(struct Node *head, int pos);

// Helper to create a new node
struct Node *newNode(int val) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->val = val;
  newNode->next = NULL;
  return newNode;
}

// Insertions
struct Node *insertAtBegining(struct Node *head, int val) {
  struct Node *new_node = newNode(val);
  new_node->next = head;
  return new_node;
}

struct Node *insertAtEnd(struct Node *head, int val) {
  struct Node *new_node = newNode(val);
  if (head == NULL) return new_node;

  struct Node *current = head;
  while (current->next != NULL) current = current->next;
  current->next = new_node;
  return head;
}

struct Node *insertAtPos(struct Node *head, int val, int pos) {
  if (pos < 1) {
    printf("Invalid position!\n");
    return head;
  }
  if (pos == 1) return insertAtBegining(head, val);

  int currentPos = 1;
  struct Node *current = head;
  struct Node *prev = NULL;

  while (current != NULL && currentPos < pos) {
    prev = current;
    current = current->next;
    currentPos++;
  }

  if (currentPos == pos) {
    struct Node *new_node = newNode(val);
    prev->next = new_node;
    new_node->next = current;
    return head;
  }

  if (current == NULL && currentPos < pos) {
    printf("Position out of bounds!\n");
  }

  return head;
}

// Deletions
struct Node *deleteAtBegining(struct Node *head) {
  if (head == NULL) return NULL;
  struct Node *temp = head;
  head = head->next;
  free(temp);
  return head;
}

struct Node *deleteAtEnd(struct Node *head) {
  if (head == NULL) return NULL;
  if (head->next == NULL) {
    free(head);
    return NULL;
  }
  struct Node *current = head;
  struct Node *prev = NULL;
  while (current->next != NULL) {
    prev = current;
    current = current->next;
  }
  prev->next = NULL;
  free(current);
  return head;
}

struct Node *deleteAtPos(struct Node *head, int pos) {
  if (pos < 1) {
    printf("Invalid position!\n");
    return head;
  }
  if (pos == 1) return deleteAtBegining(head);

  struct Node *current = head;
  struct Node *prev = NULL;
  int currentPos = 1;

  while (current != NULL && currentPos < pos) {
    prev = current;
    current = current->next;
    currentPos++;
  }

  if (currentPos == pos && current != NULL) {
    prev->next = current->next;
    free(current);
    return head;
  }

  printf("Position out of bounds!\n");
  return head;
}

// general 
int getLenght(struct Node *head) {
  struct Node *current = head;
  int length = 0;
  while (current != NULL) {
    length++;
    current = current->next;
  }
  return length;
}

bool searching(struct Node *head, int target) {
  struct Node *current = head;
  while (current != NULL) {
    if (current->val == target) return true;
    current = current->next;
  }
  return false;
}

void printList(struct Node *head) {
  struct Node *current = head;
  while (current != NULL) {
    printf("%d -> ", current->val);
    current = current->next;
  }
  printf("NULL\n");
}

int main() {
  struct Node *head = NULL;

  // Test insertions
  head = insertAtBegining(head, 20);  // List: 20
  head = insertAtBegining(head, 10);  // List: 10 -> 20
  head = insertAtEnd(head, 30);       // List: 10 -> 20 -> 30
  head = insertAtPos(head, 25, 3);    // List: 10 -> 20 -> 25 -> 30
  printList(head);                    // Expected: 10 -> 20 -> 25 -> 30 -> NULL

  // Test searching
  printf("Searching for 25: %s\n", searching(head, 25) ? "Found" : "Not Found");  // Found
  printf("Searching for 50: %s\n", searching(head, 50) ? "Found" : "Not Found");  // Not Found

  // Test deletions
  head = deleteAtBegining(head);  // List: 20 -> 25 -> 30
  printList(head);                // Expected: 20 -> 25 -> 30 -> NULL

  head = deleteAtEnd(head);       // List: 20 -> 25
  printList(head);                // Expected: 20 -> 25 -> NULL

  head = deleteAtPos(head, 2);    // List: 20
  printList(head);                // Expected: 20 -> NULL

  // Test edge cases
  head = deleteAtEnd(head);       // List becomes empty
  printList(head);                // Expected: NULL

  head = deleteAtBegining(head);  // Try deleting from an empty list
  printList(head);                // Expected: NULL

  return 0;
}
