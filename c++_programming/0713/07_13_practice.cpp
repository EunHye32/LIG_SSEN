#include "Test.h"
#include "Test2.h"
#include "Member.h"
#include "Student.h"
#include <iostream>
#include <string>
using namespace std;

#if 0
// 디자인 타임에 객체 이름이 필요할때 사용하는 포인터 -> this
// this : 클래스 작성 시점에는 값이 비어 있음 -> 객체 생성되면 this에 현재 객체의 주소 할당
class Test3 {
public:
  // 멤버 변수. 객체 소속 -> 객체가 생성되지 않으면 절대로 사용 불가
  int x;
  string name;
  
  Test3(int x, string name) {
    this->x = x;  // 멤버변수와 지역변수 구분
    this->name = name;
  }

  Test3* getTest() {
    return this;  // this: 현재 객체의 주소
  }

  // 현재 객체를 반환하는 함수
  Test3 getTest2() {
    return *this;
  }

  // 멤버 함수. 객체 소속
  void print() {
    cout << name << x << endl;
  }
};
#endif // this

#if 0
int main()
{
  Student s[3];
  for (int i = 0; i < 3; i++)
  {
    int k, e, m;
    char name[20];
    cout << "name: "; cin >> name;
    cout << "kor: "; cin >> k;
    cout << "eng: "; cin >> e;
    cout << "math: "; cin >> m;
    s[i].setData(i + 1, name, k, e, m);
    s[i].print();
  }

  return 0;
}
#endif // with Student class

#if 0
int main()
{
  Member m1(1, "aaa");
  Member m2 = m1;
  Member m3(m1);

  m2.setName("bbb");

  m1.print(); m2.print(); m3.print();

  /*
  Point p1(1, 2); // p1 객체 생성
  Point p2 = p1;  // p1을 복사해서 p2 생성
  Point p3(p1);

  p1.print();
  p2.print();
  p3.print();
  */

  /*
  Member m;
  m.print();
  Member m2(2, "bbb");
  m2.print();
  */

  /* delete
  int* p = new int;
  delete p;
  
  int* arr = new int[3];
  delete[] arr;
  */
  return 0;
}
#endif // with Member class (string, new, delete)

#if 0
int main()
{
  // privte으로 선언된 num에 대한 setter/getter 기능 제공
  Test2 t; // 일반 객체
  t.setNum(10);
  cout << t.getNum() << endl;

  // 두가지 초기화 방법
  int x = 10; // C로 초기화
  int y(5);   // C++로 초기화 -> 이니셜라이저

  cout << "x:" << x << ", y:" << y << endl;

  return 0;
}
#endif // with Test2 class + 초기화

#if 0
// call by value(값 복사) : 변수 값 복사해서 전달(값, 주소값)
void swap1(int a, int b) {
  int tmp;
  tmp = a;
  a = b;
  b = tmp;
}
// call by value(주소값 복사)
void swap2(int* a, int* b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}
// call by reference : 참조 변수를 통한 전달(파라미터가 참조변수) -> 제일 빠르고 좋음
void swap3(int &a, int &b) {
  int tmp;
  tmp = a;
  a = b;
  b = tmp;
}
int a; // 전역변수
int main()
{
  int x = 10, y = 20;
  // swap1(x, y);
  // swap2(&x, &y);
  swap3(x, y);
  cout << "x:" << x << ", y:" << y << endl;

  /* 포인터
  int a = 10; // a: int 변수
  int& b = a; // b: 참조변수(참조자 선언). a의 별칭
  int* p = &a; // p: 포인터. a의 주소

  cout << "a:" << a << endl;  // 10
  cout << "b:" << b << endl;  // 10
  cout << "*p:" << *p << endl;  // 10
  */
  return 0;
}
#endif // 함수 호출 방법 : call by value, call by reference

#if 0 
int main()
{
  cout << "Hello World!" << endl;
  Test t;
  // t.x = 1; // private 은 클래스 밖에서 사용불가
  t.name = "asdf";
  t.age = 10;
  t.print();
  t.print("hello Test");

  cout << "add(1,2):" << add(1, 2) << endl;
  cout << "add(1.5,3.2):" << add(1.5, 3.2) << endl;

  return 0;
}
#endif // with Test class

#if 0
int add(int a, int b) {
  return a + b;
}
double add(double a, double b) {
  return a + b;
}
int main()
{
  // 컴파일러가 인자의 타입을 보고 자동으로 적절한 함수를 찾아감
  cout << add(5, 10) << endl;     // 1번 함수 호출 -> 15
  cout << add(3.14, 2.0) << endl; // 2번 함수 호출 -> 5.14
  return 0;
}
#endif // 함수 오버로딩

#if 0
int main()
{
  // 컴파일러도 원본 구분 못함
  int a = 10; // 변수 선언: stack, static 메모리 할당
  int& b = a; // b: 참조 변수 (변수의 별칭. 선언 시 초기화 필수)
  
  return 0;
}
#endif // 참조 변수

#if 0
void add(int, int);
void add(int, int, int);
void add(float, float);
void add(const char*, const char*);

int main()
{
  // 호출시 아규먼트의 타입으로 호출될 함수 선택
  add(1.2f, 3.4f);
  return 0;
}
#endif // 오버로딩 기능

#if 0
int main()
{
  int a, b;
  std::cin >> a >> b; // scanf()처럼 표준 입력
  std::cout << "a:" << a << ", b:" << b << std::endl;

  return 0;
}
#endif // 입출력 cin/cout