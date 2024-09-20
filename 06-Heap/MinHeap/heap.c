#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
  int size;
  int capacity;
  int *arr;
} Heap;

// capacity -> how many values we want to store
Heap *heapInit(int capacity) {
  Heap *new_heap = (Heap *)malloc(sizeof(Heap));

  if (new_heap == NULL) {
    printf("Memory allocation failed\n");
    return NULL;
  }
  new_heap->size = 0;
  new_heap->capacity = capacity;

  // We use capacity + 1 because we are using 1-based indexing
  new_heap->arr = (int *)malloc((capacity + 1) * sizeof(int));

  if (new_heap->arr == NULL) {
    printf("Array allocation failed\n");
    free(new_heap);
    return NULL;
  }

  return new_heap;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int peek(Heap *heap) {
  if (heap == NULL || heap->size == 0) {
    return -1;
  }

  // return min value
  return heap->arr[1]; // 1-based index: root is at index 1
}

void heapifyDown(Heap *heap, int index) {
  if (heap == NULL || heap->size <= 1) {
    return;
  }

  int smallest = index;
  int leftChild, rightChild;

  while (index <= heap->size) {
    leftChild = 2 * index;
    rightChild = 2 * index + 1;

    if (leftChild <= heap->size && heap->arr[leftChild] < heap->arr[smallest]) {
      smallest = leftChild;
    }

    if (rightChild <= heap->size &&
        heap->arr[rightChild] < heap->arr[smallest]) {
      smallest = rightChild;
    }

    if (smallest == index) {
      break;
    }

    swap(&heap->arr[index], &heap->arr[smallest]);

    index = smallest;
  }
}

void heapifyUp(Heap *heap, int index) {
  if (heap == NULL || heap->size <= 1) {
    return;
  }

  while (index > 1 && heap->arr[index] < heap->arr[index / 2]) {
    swap(&heap->arr[index], &heap->arr[index / 2]);
    index = index / 2;
  }
}

int insert(Heap *heap, int val) {
  if (heap == NULL) {
    return -1;
  }

  if (heap->size >= heap->capacity) {
    printf("Size cannot be bigger or equal to the capacity\n");
    return -1;
  }

  heap->size++;
  heap->arr[heap->size] = val;

  heapifyUp(heap, heap->size);

  return 0; // success
}

int returnPos(Heap *heap, int val) {
  if (heap == NULL) {
    return -1;
  }

  // 1-based index so start from 1
  for (int i = 1; i <= heap->size; i++) {
    if (heap->arr[i] == val) {
      return i;
    }
  }

  return -1; // not valid
}

int delete(Heap *heap, int val) {
  if (heap == NULL || heap->size == 0) {
    return -1;
  }

  int indexPos = returnPos(heap, val);

  if (indexPos == -1) {
    printf("Value not found\n");
    return -1;
  }

  // Replace the value to be deleted with the last element in the heap
  heap->arr[indexPos] = heap->arr[heap->size];
  heap->size--;

  if (heap->size == 0) {
    return 0;
  }

  int parentIndex = indexPos / 2;

  if (indexPos > 1 && heap->arr[indexPos] < heap->arr[parentIndex]) {
    heapifyUp(heap, indexPos);
  } else {
    heapifyDown(heap, indexPos);
  }

  return 0; // Success
}

int main() {
  Heap *heap = heapInit(10);

  insert(heap, 10);
  insert(heap, 5);
  insert(heap, 20);
  insert(heap, 3);
  insert(heap, 7);

  printf("Min value (peek): %d\n", peek(heap)); // Should return 3

  delete(heap, 3);
  printf("Min value after deleting 3: %d\n", peek(heap)); // Should return 5

  delete(heap, 10);
  printf("Min value after deleting 10: %d\n", peek(heap)); // Should return 5

  insert(heap, 1);
  printf("Min value after inserting 1: %d\n", peek(heap)); // Should return 1

  delete(heap, 5);
  printf("Min value after deleting 5: %d\n", peek(heap)); // Should return 1

  return 0;
}
