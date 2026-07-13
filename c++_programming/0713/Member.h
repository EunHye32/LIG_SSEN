#include <iostream>
#include <string>
using namespace std;
class Member
{
private:
  int num;
  char* name; // 스트링 저장할 메모리 할당 해야함
public:
  // 생성자
  Member() :num(0), name(NULL) {}
  // 파라미터 있는 생성자
  Member(int n, const char* p):num(n) {
    int len = strlen(p) + 1;
    name = new char[len];
    strcpy(name, p);
  }
  Member(const Member& m) :num(m.num) {
    if (m.name != NULL) {
      int len = strlen(m.name) + 1;
      name = new char[len];
      strcpy(name, m.name);
    }
    else {
      name = NULL;
    }
  }
  // 소멸자. 객체 소멸 직전 자동 호출됨. 객체에서 사용한 자원 반환
  ~Member() {
    cout << "소멸자 호출됨" << endl;
    delete[] name;
  }
  void print() {
    cout << "num:" << num;
    if (name != NULL) {
      cout << ", name:" << name << endl;
    }
    else {
      cout << endl;
    }
  }
  void setName(const char* nname) {
    if (nname == NULL) {
      name = NULL;
      return;
    }
    int len = strlen(nname) + 1;
    nname = new char[len];
    strcpy(name, nname);
  }
};

class Point {
public:
  int x, y;
  Point() :x(0), y(0) {}
  Point(int a, int b) :x(a), y(b) {}
  Point(const Point& p) :x(p.x), y(p.y) { // 참조자

  }
  void print() {
    cout << "x:" << x << ", y:" << y << endl;
  }
};