#ifndef __DLL_H_
#define __DLL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElementType_DLL;
typedef struct _node_DLL
{
  ElementType_DLL data;
  struct _node_DLL* prev;
  struct _node_DLL* next;
}node_DLL;

void Delete_NodeDLL(node_DLL* nnode);
node_DLL* Search_NodeDLL(node_DLL* head, node_DLL* tail, ElementType_DLL target);
static void Insert_NodeDLL(node_DLL* prevnode, node_DLL* nextnode, node_DLL* nnode);
void InsertAfter_DLL(node_DLL* tnode, node_DLL* nnode);
void InsertBefore_DLL(node_DLL* tnode, node_DLL* nnode);
void init_HT(node_DLL** head, node_DLL** tail);
node_DLL* Create_DLLNode(ElementType_DLL data);
void print_NodeDLL(node_DLL* head, node_DLL* tail);

#endif