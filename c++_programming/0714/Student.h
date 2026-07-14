#pragma once
#include <iostream>
using namespace std;

class Person { // 부모 클래스
public:
  int num;
  string name;
  string dept;

  Person() :num(0), name(""), dept("") {
    cout << "Person default maker" << endl;
  }
  Person(int num, string name, string dept) {
    cout << "Person param maker" << endl;
    this->num = num;
    this->name = name;
    this->dept = dept;
  }

  void print() {
    cout << "num:" << num << " / name:" << name << " / dept:" << dept << endl;
  }
};

class Student : public Person { // Person을 상속받는 Student 클래스 정의
public:
  string *subjects;
  Student() {
    cout << "Student default maker" << endl;
  }
  Student(int num, string name, string dept, string val) :Person(num, name, dept) {
    cout << "Student param maker" << endl;
    subjects[0] = val;
  }
  void printSubj() {
    
  }
};
class Prof : public Person {
public:
  string open;
};
class Staff : public Person {
public:
  string job;
};