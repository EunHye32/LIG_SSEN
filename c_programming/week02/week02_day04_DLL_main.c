#if 0 // 더블 링크드 리스트
#include "week02_day04_DLL.h"
int main(void)
{
  node_DLL* head = NULL;
  node_DLL* tail = NULL;
  node_DLL* snode = NULL;

  // 노드 초기화 (head와 tail 연결)
  init_HT(&head, &tail);

  // 노드 삽입
  InsertBefore_DLL(tail, Create_DLLNode(100));
  InsertBefore_DLL(tail, Create_DLLNode(200));
  InsertBefore_DLL(tail, Create_DLLNode(300));
  InsertBefore_DLL(tail, Create_DLLNode(400));
  print_NodeDLL(head, tail);

  // 특정 노드 찾기 (ex. 300, 350)
  snode = Search_NodeDLL(head, tail, 300);
  if (snode) printf("snode test (target is 300) : %d\n", snode->data);
  else printf("There's no 300 value\n");

  snode = Search_NodeDLL(head, tail, 350);
  if (snode) printf("snode test (target is 350) : %d\n", snode->data);
  else printf("There's no 350 value\n");

  // 노드 찾고 삭제
  snode = Search_NodeDLL(head, tail, 300);
  Delete_NodeDLL(snode);

  // 메모리 해제
  node_DLL* curr = head;
  node_DLL* free_node = NULL;
  while (curr != NULL)
  {
    free_node = curr;
    curr = curr->next;
    free(free_node);
  }
  head = NULL; tail = NULL;

  return 0;
}
#endif