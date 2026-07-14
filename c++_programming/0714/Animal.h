#pragma once
#include <iostream>
using namespace std;

class Animal {
public:
  virtual void speak() {
    std::cout << "Make animal sound." << std::endl;
  }
};

class Dog : public Animal {
public:
  // 부모의 speak() 함수를 덮어씀 (오버라이딩)
  void speak() override {
    std::cout << "bowbow!" << std::endl;
  }
};

class Cat : public Animal {
public:
  // 부모의 speak() 함수를 덮어씀 (오버라이딩)
  void speak() override {
    Animal::speak();  // 재정의 함수 원본 호출 방법
    std::cout << "Meow~" << std::endl;
  }
};

class Poketmon {
public:
  int hp = 100;
  int exp = 0;
  int level = 1;

  ~Poketmon() {}

  virtual void eatting() {
    hp += 10;
    cout << "eatting... HP increased by 10." << endl;
  }
  virtual void sleeping() {
    hp += 20;
    cout << "sleeping... HP increased by 20." << endl;
  }
  virtual void playing() {
    hp -= 10;
    exp += 20;
    cout << "playing... HP decreased by 10, and EXP increased by 20." << endl;
    checkLevelUp();
  }
  virtual void exercising() {
    hp -= 20;
    exp += 30;
    cout << "exercising... HP decreased by 20, and EXP increased by 30." << endl;
    checkLevelUp();
  }
  void status() {
    cout << "[Status] Level: " << level << " | HP: " << hp << " | EXP: " << exp << endl;
  }

protected:
  void checkLevelUp() {
    if (hp <= 0) {
      cout << "The character has died!" << endl;
    }
    if (exp >= 50) {
      level++;
      exp -= 50;
      cout << "Level Up! Current Level:" << level << endl;
    }
  }
};

class Pikachu :public Poketmon {
public:
  void eatting() override {
    hp += 15;
    cout << "Pikachu eats it happily! HP increases by 15." << endl;
  }
  void elec() {
    cout << "Attack electric!" << endl;
  }
};
class Gobook :public Poketmon {
public:
  void sleeping() override {
    hp += 30;
    cout << "Gobook is fast asleep... HP increased by 30." << endl;
  }
  void water() {
    cout << "Attack water!" << endl;
  }
};
class Lee :public Poketmon {
public:
  void playing() override {
    exp += 30;
    cout << "Lee play... exp increased by 30." << endl;
  }
  void nungcool() {
    cout << "Attack nungcool!" << endl;
  }
};