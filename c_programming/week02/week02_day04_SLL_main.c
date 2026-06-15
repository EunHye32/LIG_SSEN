#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0 // 링크드 리스트 (Append)
#include "week02_day04_SLL.h";
int main(void)
{
  node_SLL* head = NULL;
  node_SLL* tail = NULL;
  node_SLL* nnode;
  nnode = Create_SLLNode(100);
  Append_SLLNode(&head, &tail, nnode);

  printf("%d\n", head->data);

  Append_SLLNode(&head, &tail, Create_SLLNode(200));
  printf("%d\n", head->next->data);

  // 메모리 해제
  node_SLL* curr = head;
  node_SLL* free_node = NULL;
  while (curr != NULL)
  {
    free_node = curr;
    curr = curr->next;
    free(free_node);
  }

  return 0;
}
#endif

#if 0 // 단일 링크드 리스트 (메모리 할당)
#include "day04_SLL.h";
int main(void)
{
  node_SLL* a = Create_SLLNode(10);
  node_SLL* b = Create_SLLNode(20);

  a->next = b;
  printf("%d %d\n", a->data, a->next->data);
  printf("%d\n", b->data);

  free(a); a = 0;
  free(b); b = 0;
  return 0;
}
#endif

#if 0 // 단일 링크드 리스트
#include "day04_SLL.h";
int main(void)
{
  node_SLL a, b, c;
  a.data = 10; b.data = 20; c.data = 30;
  a.next = &b; b.next = &c;
  printf("%d %d %d\n", a.data, a.next->data, a.next->next->data);

  return 0;
}
#endif