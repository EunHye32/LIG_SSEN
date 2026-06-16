#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElementType;

typedef struct _HeapNode
{
  ElementType data;
}HeapNode;

typedef struct _Heap
{
  HeapNode* nodes;
  int capacity;   // 배열의 크기
  int usedsize;   // 사용된 배열 요소의 수
}Heap;

HeapNode deleteRootNode(Heap* heap);
void insertHeapNode(Heap* heap, ElementType* data);
void initHeapNode(Heap* heap, ElementType* arr, int n);
void printHeapNode(Heap* heap);
Heap* initHeap(int capacity);
void destroyHeap(Heap* heap);

#endif