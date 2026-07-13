#pragma once
#include<string>
#include <iostream>
using namespace std;

// 멤버변수, 멤버함수
class Test
{
private:
  int x;
public:
  string name;
  int age;

  // 멤버함수
  void print();
  void print(string msg);
};

// 전역함수
int add(int, int);
double add(double, double);
