#include <iostream>
#include "MyLinkedList.h"
using namespace std;

#if 0
int main() {
  MyLinkedList2<int> node;
  node.print();
  node.push_front(10); node.print();
  node.push_back(20); node.print();
  node.push_front(30); node.print();
  node.pop_front(); node.print();
  node.push_back(40); node.print();
  node.clear(); node.print();
  return 0;
}
#endif // 링크드 리스트 2 with MyLinkedList2 class

#if 0
int main()
{
  MyLinkedList node;
  node.print();
  node.push(10); node.print();
  node.push(20); node.print();
  node.push(30); node.print();
  node.pop(); node.print();
  node.push(40); node.print();
  node.clear(); node.print();

  return 0;
}
#endif // 링크드 리스트 with MyLinkedList class