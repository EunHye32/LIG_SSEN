#pragma once
#include <iostream>
using namespace std;

class Parent {
private:
  int x;
protected: // 상속 관계에서는 보이지만 타 클래스에는 안보임
  int y;
public:
  int z;
};

class Child : public Parent {
public:
  void print() {
    //cout << x << y << z << endl;
  }
};