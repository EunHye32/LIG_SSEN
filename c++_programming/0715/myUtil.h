#pragma once
#include <iostream>
using namespace std;

class MyUtil { // 인터페이스
public:
  virtual void add() = 0;
  virtual void get() = 0;
  virtual void edit() = 0;
  virtual void del() = 0;
};

class MyVector : public MyUtil {
  // MyUtil을(를) 통해 상속됨
  void add() override {
    cout << "vector add" << endl;
  }
  void get() override {
    cout << "vector get" << endl;
  }
  void edit() override {
    cout << "vector edit" << endl;
  }
  void del() override {
    cout << "vector del" << endl;
  }
};

class MyList : public MyUtil {
  // MyUtil을(를) 통해 상속됨
  void add() override {
    cout << "List add" << endl;
  }
  void get() override {
    cout << "List get" << endl;
  }
  void edit() override {
    cout << "List edit" << endl;
  }
  void del() override {
    cout << "List del" << endl;
  }
};

class Dao {
private:
  MyUtil* util; // 인터페이스 타입 변수 선언
public:
  Dao(MyUtil* util) :util(util) {}
  
  void addData() {
    util->add();
  }
  void getData() {
    util->get();
  }
  void editData() {
    util->edit();
  }
  void delData() {
    util->del();
  }
};