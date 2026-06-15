#include "week02_day04_DLL.h"

// 더블 링크드 리스트 (prevnode - nnode - nextnode)
void Delete_NodeDLL(node_DLL* nnode)
{
  if (nnode == NULL) return;
  nnode->next->prev = nnode->prev;
  nnode->prev->next = nnode->next;
  free(nnode);
}
node_DLL* Search_NodeDLL(node_DLL* head, node_DLL* tail, ElementType_DLL target)
{
  if (head == NULL || tail == NULL) return;
  node_DLL* curr = NULL;

  for (curr = head->next; curr != tail; curr = curr->next)
  {
    if (curr->data == target) return curr;
  }
  return NULL;
}
static void Insert_NodeDLL(node_DLL* prevnode, node_DLL* nextnode, node_DLL* nnode)
{
  if (prevnode == NULL || nextnode == NULL || nnode == NULL) return;
  nnode->prev = prevnode;
  nnode->next = nextnode;
  prevnode->next = nnode;
  nextnode->prev = nnode;
}
void InsertAfter_DLL(node_DLL* tnode, node_DLL* nnode)
{
  if (tnode == NULL || nnode == NULL) return;
  Insert_NodeDLL(tnode, tnode->next, nnode);
  //nnode->prev = tnode;
  //nnode->next = tnode->next;
  //tnode->next->prev = nnode;
  //tnode->next = nnode;
}
void InsertBefore_DLL(node_DLL* tnode, node_DLL* nnode)
{
  if (tnode == NULL || nnode == NULL) return;
  Insert_NodeDLL(tnode->prev, tnode, nnode);
  //nnode->prev = tnode->prev;
  //nnode->next = tnode;
  //tnode->prev->next = nnode;
  //tnode->prev = nnode;
}
void init_HT(node_DLL** head, node_DLL** tail)
{
  *head = (node_DLL*)calloc(1, sizeof(node_DLL));
  *tail = (node_DLL*)calloc(1, sizeof(node_DLL));
  if (*head == NULL) exit(2);
  if (*tail == NULL) exit(2);

  (*head)->next = *tail;
  (*tail)->prev = *head;
}
node_DLL* Create_DLLNode(ElementType_DLL data)
{
  node_DLL* nnode = NULL;
  nnode = (node_DLL*)calloc(1, sizeof(node_DLL));
  if (nnode == NULL)
  {
    printf("Leak of Memory!\n");
    exit(2);
  }

  nnode->data = data;
  return nnode;
}
void print_NodeDLL(node_DLL* head, node_DLL* tail)
{
  for (node_DLL* curr = head->next; curr != tail; curr = curr->next)
  {
    printf("%d ", curr->data);
  }
  printf("\n");
}