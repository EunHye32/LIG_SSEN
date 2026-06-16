#include "day05_Heap.h"
#define SWAP(type, x, y) { type temp = x; x = y; y = temp; }

/*
HeapNode deleteRootNode2(Heap* heap)
{
  if (heap->usedsize == 0) exit(2);

  HeapNode first_node = heap->nodes[1];
  HeapNode last_node = heap->nodes[(heap->usedsize)--];

  int parent = 1, child = 2, heap_size = heap->usedsize;

  while (child <= heap_size)
  {
    if ((child < heap_size) && (heap->nodes[child].data > heap->nodes[child + 1].data))
    {
      child++;
    }
    if (last_node.data <= heap->nodes[child].data) {
      break;
    }

    heap->nodes[parent] = heap->nodes[child];

    parent = child;
    child *= 2;
  }
  heap->nodes[parent] = last_node;

  return first_node;
}
*/

HeapNode deleteRootNode(Heap* heap)
{
  HeapNode root = heap->nodes[1];

  heap->nodes[1] = heap->nodes[heap->usedsize];
  heap->usedsize--;
  
  int curr = 1;
  while (curr * 2 <= heap->usedsize)
  {
    int left = curr * 2;
    int right = curr * 2 + 1;
    int minChild = left;
    
    if (right <= heap->usedsize && heap->nodes[right].data < heap->nodes[left].data)
    {
      minChild = right;
    }
    if (heap->nodes[curr].data <= heap->nodes[minChild].data)
    {
      break;
    }
    SWAP(ElementType, heap->nodes[curr].data, heap->nodes[minChild].data);

    curr = minChild;
  }
  return root;
}

void insertHeapNode(Heap* heap, ElementType data)
{
  heap->usedsize++;
  if (heap->usedsize > heap->capacity) exit(2);
  int curr = heap->usedsize;
  heap->nodes[curr].data = data;

  while (curr > 1 && heap->nodes[curr].data < heap->nodes[curr / 2].data)
  {
    SWAP(ElementType, heap->nodes[curr].data, heap->nodes[curr / 2].data);
    curr /= 2;
  }
}

void initHeapNode(Heap* heap, ElementType* arr, int n)
{
  HeapNode* nodes = heap->nodes;
  for (int i = 0; i < n; ++i)
  {
    nodes[i + 1].data = arr[i];
  }
  heap->usedsize = n;
}

void printHeapNode(Heap* heap)
{
  HeapNode* nodes = heap->nodes;
  int n = heap->usedsize;
  for (int i = 1; i <= n; ++i)
  {
    printf("%2d ", nodes[i].data);
  }
  printf("\n");
}

Heap* initHeap(int capacity)
{
  Heap* temp = (Heap*)calloc(1, sizeof(Heap));
  if (temp == NULL) exit(2);
  temp->nodes = (HeapNode*)calloc(capacity + 1, sizeof(HeapNode));
  if (temp->nodes == NULL)
  {
    free(temp);
    exit(2);
  }
  temp->capacity = capacity;
  temp->usedsize = 1;

  return temp;
}

void destroyHeap(Heap* heap)
{
  free(heap->nodes);
  free(heap);
}