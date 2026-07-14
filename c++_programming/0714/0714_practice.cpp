#include <iostream>
#include "Test.h"
#include "Test2.h"
#include "Student.h"
#include "Parent.h"
#include "Animal.h"

#if 0
int main()
{
  Poketmon* pp = nullptr; // 업캐스팅
  int m;

  cout << "Choose character (1) Pikachu (2) Gobook (3) Lee : "; cin >> m;
  switch (m) {
  case 1:
    pp = new Pikachu(); break;
  case 2:
    pp = new Gobook(); break;
  case 3:
    pp = new Lee; break;
  default:
    return 0;
  }

  while (1) {
    cout << "0. exit(0) 1. eatting 2. sleeping 3. playing 4. exercising 5. status 6. Attack : "; cin >> m;
    if (!m) break;

    switch (m) {
    case 1:
      pp->eatting(); break;
    case 2:
      pp->sleeping(); break;
    case 3:
      pp->playing(); break;
    case 4:
      pp->exercising(); break;
    case 5:
      pp->status(); break;
    case 6:
      if (Pikachu* p = ((Pikachu*)pp)) p->elec();
      else if (Gobook* g = ((Gobook*)pp)) g->water();
      else if (Lee* l = ((Lee*)pp)) l->nungcool();
      break;
    default:
      cout << "choose 0 to 6" << endl;
    }
  }

  if (pp != nullptr) {
    delete pp;
    pp = nullptr;
  }
  return 0;
}
#endif // 포켓몬 with Animal header

#if 0
int main()
{
  Animal a; a.speak();  // 정적 바인딩
  Dog dog; dog.speak();
  Cat cat; cat.speak();

  Animal* p = &dog; // 업캐스팅
  p->speak(); // 정적 바인딩. Animal의 speak() 호출

  return 0;
}
#endif // 오버라이딩 with Animal class

#if 0
int main()
{
  Child c;
  cout << c.y << c.z << endl;
  return 0;
}
#endif // private/protected with Parent class

#if 0
int main()
{
  Student s;
  s.print();

  return 0;
}
#endif // 상속 with Student, ... class

#if 0
int Test2::x = 0;
int main()
{
  Test2::f2(); Test2::f4();
  return 0;
}
#endif // static with Test2 classs

#if 0
int Test::x = 0;
int Product::cnt = 0;
int main()
{
  Product p1[] = { {"aaa", 1000}, {"bbb", 2000}, {"ccc", 3000} };
  for (Product p : p1) p.print();

  cout << "static member x:" << Test::x << endl;
  //cout << "Normal member y:" << Test::y << endl;

  Test t1; t1.addXY(); t1.printXY();
  Test t2; t2.addXY(); t2.printXY();
  Test t3; t3.addXY(); t3.printXY();
  
  return 0;
}
#endif // static with Test, Product class