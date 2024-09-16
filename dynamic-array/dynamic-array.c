// structure of the Dynamic Array that will hold:
//
// 1. array pointer
// 2. current size (number of elements)
// 3. capacity (maximum number of elements)

// functions:
// 1. initialization
// 2. resizing
// 3. adding an element
// 4. freeing memory

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *array;   // pointer to the array
  int size;     // number of elements in the array
  int capacity; // total capacity of the array

} DynamicArray;

void initArray(DynamicArray *arr, int initialCapacity);
void resize(DynamicArray *arr);
void append(DynamicArray *arr, int val);
void freeMemory(DynamicArray *arr);
void printArray(DynamicArray *arr);

int main() {
  DynamicArray arr;

  initArray(&arr, 2);

  append(&arr, 10);
  append(&arr, 20);
  append(&arr, 30); // resize
  append(&arr, 40);
  append(&arr, 50);

  printArray(&arr);

  freeMemory(&arr);

  return 0;
}

void initArray(DynamicArray *arr, int initialCapacity) {
  arr->array = malloc(initialCapacity * sizeof(int));
  if (arr->array == NULL) {
    printf("Memory allocation failed");
    exit(1);
  }
  arr->size = 0;
  arr->capacity = initialCapacity;
}

void append(DynamicArray *arr, int val) {
  // resize based on the condition
  if (arr->size == arr->capacity) {
    resize(arr);
  }

  // append the val
  arr->array[arr->size] = val;
  arr->size++;
}

void resize(DynamicArray *arr) {
  // double the capacity
  // and realloc the size
  arr->capacity *= 2;
  arr->array = realloc(arr->array, arr->capacity * sizeof(int));
  if (arr->array == NULL) {
    printf("Memory allocation failed during resizing!\n");
    exit(1);
  }
}

void printArray(DynamicArray *arr) {
  printf("Array values: ");
  for (int i = 0; i < arr->size; i++) {
    printf("%d", arr->array[i]);
    if (i < arr->size - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

void freeMemory(DynamicArray *arr) {
  free(arr->array);
  arr->array = NULL;
  arr->size = 0;
  arr->capacity = 0;
}
