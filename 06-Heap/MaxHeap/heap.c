#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
  int size;
  int capacity;
  int *arr;
} Heap;

Heap *heapInit(int capacity) {
  Heap *new_heap = (Heap *)malloc(sizeof(Heap));
  if (new_heap == NULL) {
    printf("Memory allocation failed\n");
    return NULL;
  }

  new_heap->size = 0;
  new_heap->capacity = capacity;

  new_heap->arr = (int *)malloc((capacity + 1) * sizeof(int));  // 1-indexed
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

void heapifyUp(Heap *heap, int index) {
  while (index > 1 && heap->arr[index] > heap->arr[index / 2]) {
    swap(&heap->arr[index], &heap->arr[index / 2]);
    index = index / 2;
  }
}

void heapifyDown(Heap *heap, int index) {
  int largest = index;
  int left = 2 * index;
  int right = 2 * index + 1;

  if (left <= heap->size && heap->arr[left] > heap->arr[largest]) {
    largest = left;
  }

  if (right <= heap->size && heap->arr[right] > heap->arr[largest]) {
    largest = right;
  }

  if (largest != index) {
    swap(&heap->arr[index], &heap->arr[largest]);
    heapifyDown(heap, largest);
  }
}

int insert(Heap *heap, const int val) {
  if (!heap || heap->size >= heap->capacity) {
    return -1;
  }

  heap->size++;
  heap->arr[heap->size] = val;
  heapifyUp(heap, heap->size);

  return 0;
}

int extractMax(Heap *heap) {
    if (heap->size == 0) {
        return -1;  // Heap is empty
    }

    int max = heap->arr[1];  // Root value (max in max-heap)
    heap->arr[1] = heap->arr[heap->size];
    heap->size--;
    heapifyDown(heap, 1);
    return max;
}

int peek(Heap *heap) {
  if (!heap || heap->size == 0) {
    return -1;
  }
  return heap->arr[1];
}

Heap *buildHeap(int *arr, int size) {
  Heap *heap = (Heap *)malloc(sizeof(Heap));
  heap->size = size;
  heap->capacity = size;
  heap->arr = (int *)malloc((size + 1) * sizeof(int));  // 1-indexed array

  for (int i = 1; i <= size; i++) {
    heap->arr[i] = arr[i - 1];
  }

  for (int i = heap->size / 2; i >= 1; i--) {
    heapifyDown(heap, i);
  }

  return heap;
}

int main() {
  // Initialize the heap
  Heap *heap = heapInit(10);

  // Test Case 1: Insertions
  printf("Test Case 1: Insertions\n");
  insert(heap, 5);
  insert(heap, 10);
  insert(heap, 3);
  insert(heap, 1);

  printf("Heap after insertions (should print in heap order): ");
  for (int i = 1; i <= heap->size; i++) {
    printf("%d ", heap->arr[i]);
  }
  printf("\n");

  // Test Case 2: Peek (Max Element)
  printf("Test Case 2: Peek (Max Element)\n");
  int maxElement = peek(heap);
  printf("Max element (should be 10): %d\n", maxElement);

  // Test Case 3: Extract Max
  printf("Test Case 3: Extract Max\n");
  int extractedMax = extractMax(heap);
  printf("Extracted Max (should be 10): %d\n", extractedMax);
  printf("Heap after extracting max (should still be valid max-heap): ");
  for (int i = 1; i <= heap->size; i++) {
    printf("%d ", heap->arr[i]);
  }
  printf("\n");

  // Test Case 4: Build Heap from an Array
  printf("Test Case 4: Build Heap from an Array\n");
  int arr[] = {4, 10, 3, 5, 1};
  int size = sizeof(arr) / sizeof(arr[0]);

  Heap *heapFromArray = buildHeap(arr, size);
  printf("Heap built from array (should print in heap order): ");
  for (int i = 1; i <= heapFromArray->size; i++) {
    printf("%d ", heapFromArray->arr[i]);
  }
  printf("\n");

  // Test Case 5: Extract Max from heap built from array
  printf("Test Case 5: Extract Max from heap built from array\n");
  extractedMax = extractMax(heapFromArray);
  printf("Extracted Max (should be 10): %d\n", extractedMax);
  printf("Heap after extracting max from array-built heap: ");
  for (int i = 1; i <= heapFromArray->size; i++) {
    printf("%d ", heapFromArray->arr[i]);
  }
  printf("\n");

  // Test Case 6: Insert after extracting max
  printf("Test Case 6: Insert after extracting max\n");
  insert(heapFromArray, 20);
  printf("Heap after inserting 20 (should maintain heap property): ");
  for (int i = 1; i <= heapFromArray->size; i++) {
    printf("%d ", heapFromArray->arr[i]);
  }
  printf("\n");

  // Clean up memory
  free(heap->arr);
  free(heap);
  free(heapFromArray->arr);
  free(heapFromArray);

  return 0;
}
