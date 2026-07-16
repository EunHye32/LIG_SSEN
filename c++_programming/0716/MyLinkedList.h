#include <iostream>
#include <stdexcept>
using namespace std;

class MyLinkedList {
private:
  struct Node {
    int data;
    Node* next;

    Node(const int& value) : data(value), next(nullptr) {}
  };

  Node* head; // 첫 노드 주소
  Node* tail; // 마지막 노드 주소
  int cnt;    // 요소 개수

public:
  MyLinkedList() : head(nullptr), tail(nullptr), cnt(0) {}
  ~MyLinkedList() {
    clear();
  }
  
  void push(int a) {
    Node* newNode = new Node(a);

    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    }
    else {
      tail->next = newNode;
      tail = newNode;
    }

    cnt++;
  }

  int pop() {
    if (empty()) {
      throw out_of_range("List is empty. Cannot pop.");
    }

    Node* temp = head;
    int popData = temp->data;
    head = head->next;
    delete temp;
    cnt--;

    if (head == nullptr) {
      tail = nullptr;
    }

    return popData;
  }
  bool empty() {
    return cnt <= 0;
  }

  // 모든 노드 삭제
  void clear() {
    Node* current = head;
    while (current != nullptr) {
      Node* nextNode = current->next; // 다음 노드 주소 미리 저장
      delete current;                 // 현재 노드 삭제
      current = nextNode;             // 다음 노드로 이동
    }

    head = nullptr;
    tail = nullptr;
    cnt = 0;
  }

  void print() const {
    Node* current = head;
    while (current != nullptr) {
      cout << current->data << " ";
      current = current->next;
    }
    cout << "(Count: " << cnt << ")\n";
  }
};

// 모든 타입 처리할 링크드 리스트
// push_fornt, push_back, pop_front, pop_back, find(값):값 찾아서 리턴, remove(값):값 찾아서 리턴 찾은 노드 주소반환
// remove(값):값 찾아서 삭제, 처리 결과(true, false) 반환
template <typename T>
class MyLinkedList2 {
private:
  struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* head; // 첫 노드 주소
  Node* tail; // 마지막 노드 주소
  int cnt;    // 요소 개수

public:
  MyLinkedList2() : head(nullptr), tail(nullptr), cnt(0) {}
  ~MyLinkedList2() {
    clear();
  }

  void push_front(const T& a) {
    Node* newNode = new Node(a);

    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    }
    else {
      newNode->next = head;
      head = newNode;
    }
    cnt++;
  }

  void push_back(const T& a) {
    Node* newNode = new Node(a);

    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    }
    else {
      tail->next = newNode;
      tail = newNode;
    }
    cnt++;
  }

  void push(const T& a) {
    push_back(a);
  }

  T pop_front() {
    if (empty()) {
      throw out_of_range("List is empty. Cannot pop_front.");
    }

    Node* temp = head;
    T popData = temp->data;
    head = head->next;
    delete temp;
    cnt--;

    if (head == nullptr) {
      tail = nullptr;
    }

    return popData;
  }

  T pop_back() {
    if (empty()) {
      throw out_of_range("List is empty. Cannot pop_back.");
    }

    T popData = tail->data;

    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
    }
    else {
      Node* current = head;
      while (current->next != tail) {
        current = current->next;
      }
      delete tail;
      tail = current;
      tail->next = nullptr;
    }
    cnt--;

    return popData;
  }

  T pop() {
    return pop_front();
  }

  Node* find(const T& value) const {
    Node* current = head;
    while (current != nullptr) {
      if (current->data == value) {
        return current;
      }
      current = current->next;
    }
    return nullptr;
  }

  bool remove(const T& value) {
    if (empty()) {
      return false;
    }

    if (head->data == value) {
      pop_front();
      return true;
    }

    Node* current = head;
    while (current->next != nullptr) {
      if (current->next->data == value) {
        Node* nodeToDelete = current->next;
        current->next = nodeToDelete->next;

        if (nodeToDelete == tail) {
          tail = current;
        }

        delete nodeToDelete;
        cnt--;
        return true;
      }
      current = current->next;
    }
    return false;
  }

  bool empty() const {
    return cnt <= 0;
  }

  void clear() {
    Node* current = head;
    while (current != nullptr) {
      Node* nextNode = current->next;
      delete current;
      current = nextNode;
    }

    head = nullptr;
    tail = nullptr;
    cnt = 0;
  }

  void print() const {
    Node* current = head;
    while (current != nullptr) {
      cout << current->data << " ";
      current = current->next;
    }
    cout << "(Count: " << cnt << ")\n";
  }
};