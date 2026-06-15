#include "week02_day04_SLL.h";
void Append_SLLNode(node_SLL** head, node_SLL** tail, node_SLL* nnode) // 링크드 리스트 (Append)
{
  if (*head == NULL)
  {
    *head = nnode;
    *tail = nnode;
  }
  else
  {
    (*tail)->next = nnode;
    *tail = nnode;
    //node_SLL* curr = NULL;
    //for (curr = *head; curr->next != NULL; curr = curr->next);
    //curr->next = nnode;
  }
}
node_SLL* Create_SLLNode(ElementType_SLL data)    // 단일 링크드 리스트 (메모리 할당)
{
  node_SLL* nnode = NULL;
  nnode = (node_SLL*)calloc(1, sizeof(node_SLL)); // nnode = (node_SLL*)malloc(sizeof(node_SLL)); // 초기화 필수
  if (nnode == NULL)
  {
    printf("Leak of Memory!\n");
    exit(2);
  }
  
  nnode->data = data;
  return nnode;
}