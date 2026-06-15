#ifndef __SLL_H__
#define __SLL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElementType_SLL;
typedef struct _node_SLL
{
  ElementType_SLL data;
  struct _node_SLL* next;
}node_SLL;

void Append_SLLNode(node_SLL** head, node_SLL** tail, node_SLL* nnode);
node_SLL* Create_SLLNode(ElementType_SLL data);

#endif