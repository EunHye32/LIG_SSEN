#pragma once
#include <iostream>
using namespace std;

class Parent { // 추상 클래스 : 순수 가상함수 1개 이상 포함
public:
  virtual void f1() = 0; // 순수 가상함수
  virtual void f2() = 0;
  void f3() {
    cout << "f3()" << endl;
  }
};

class Child :public Parent {
public:
  // Parent을(를) 통해 상속됨
  void f1() override {
    cout << "f1()" << endl;
  }
  void f2() override {
    cout << "f2()" << endl;
  }
};