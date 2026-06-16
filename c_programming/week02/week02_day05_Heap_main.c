#if 0 // 힙 이진트리
#include "day05_Heap.h"
#define SIZE(x) (sizeof(x)/sizeof((x)[0]))

int main(void)
{
  Heap* heap = NULL;
  ElementType arr[] = { 2, 8, 52, 13, 37, 67, 161, 17, 43, 88 };
  heap = initHeap(30);

  initHeapNode(heap, arr, SIZE(arr));
  printHeapNode(heap);

  insertHeapNode(heap, 7);
  printHeapNode(heap);

  printf("Deleted : %d\n", deleteRootNode(heap).data);
  printHeapNode(heap);

  // 메모리 해제
  destroyHeap(heap);
  heap = NULL;

  return 0;
}
#endif