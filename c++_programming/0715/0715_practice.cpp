#include <iostream>
#include "Parent.h"
#include "myUtil.h"
#include "Vector2.h"
using namespace std;

#if 1
int main()
{

  return 0;
}
#endif

#if 0
int main()
{
  Vector2 pos1(10, 20);
  Vector2 pos2(5, 15);

  // 오버로딩된 '+' 연산자 사용
  // 컴파일러는 이를 pos1.operator+(pos2) 로 변환하여 실행합니다.
  Vector2 pos3 = pos1 + pos2;

  cout << "pos1: "; pos1.print();
  cout << "pos2: "; pos2.print();
  cout << "pos1 + pos2 = "; pos3.print();

  Vector2 pos4 = pos1 - pos2;
  cout << "pos1 - pos2 = "; pos4.print();

  // 오버로딩된 '==' 연산자 사용
  cout << "--- Result ---" << endl;
  if (pos1 == pos2) {
    cout << "Two point was same." << endl;
  }
  else {
    cout << "Two point was different." << endl;
  }
  return 0;
}
#endif // 연산자 오버로딩 with Vector2 class

#if 0
int main()
{
  Dao dao(new MyList);
  dao.addData(); dao.getData(); dao.editData(); dao.delData();

  return 0;
}
#endif // with myUtil class

#if 0
int main()
{
  Child c;
  c.f1(); c.f2(); c.f3();

  return 0;
}
#endif // with Parent/Child class