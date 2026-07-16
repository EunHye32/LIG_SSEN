#pragma once
#include <iostream>
using namespace std;

class Vector2 {
private:
  int x, y;

public:
  // 생성자
  Vector2(int x = 0, int y = 0) : x(x), y(y) {}

  // 1. '+' 연산자 오버로딩
  // 자기 자신(this)의 멤버와 매개변수(other)의 멤버를 더합니다.
  Vector2 operator+(const Vector2& other) {
    Vector2 temp;
    temp.x = this->x + other.x;
    temp.y = this->y + other.y;
    return temp;
  }

  // 2. '==' 연산자 오버로딩 (두 좌표가 완전히 일치하는지 비교)
  bool operator==(Vector2& other) {
    return (this->x == other.x) && (this->y == other.y);
  }
  bool operator==(const Vector2& other) {
    return (this->x == other.x) && (this->y == other.y);
  }

  // 3. '-' 연산자 오버로딩
  Vector2 operator-(const Vector2& other) {
    Vector2 temp;
    temp.x = this->x - other.x;
    temp.y = this->y - other.y;
    return temp;
  }

  void print() {
    std::cout << "(" << x << ", " << y << ")" << std::endl;
  }
};

