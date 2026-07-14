#pragma once
#include <iostream>
using namespace std;

class Test
{
public:
  static int x; // static 멤버
  int y;  // 일반멤버

  Test() :y(0) {}

  void addXY() {
    x++; y++;
  }
  void printXY() {
    cout << "x:" << x << ", y:" << y << endl;
  }
};

class Product {
public:
  int num;  // 제품 시리얼넘버, 자동할당
  string name;
  int price;
  static int cnt;

  Product(string name, int price) {
    num = ++cnt;
    this->name = name;
    this->price = price;
  }
  void print() {
    cout << "num:" << num << ", name:" << name << ", price:" << price << endl;
  }
};