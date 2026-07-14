#pragma once
#include <iostream>
using namespace std;

class Test2
{
public:
  static int x;
  int y;

  void f1() { // 일반 멤버함수는 일반 멤버변수, static 변수 모두 사용 가능
    x = 1; y = 1;
  }

  static void f2() { // static 함수는 static 멤버 변수만 사용 가능
    x = 1; //y = 1;
  }

  void f3() { // 일반 멤버함수는 일반이나 static 함수 모두 호출 가능
    f1(); f2();
  }

  static void f4() { // static 함수는 static 멤버 함수만 호출 가능
    f2(); //f1();
  }
};

