#pragma once
class Test2
{
private: // 클래스 밖에서 직접 접근 막음 -> 은닉성 제공
  int num; // 밖에서 안보임. 클래스 밖에서 읽기(getter)/쓰기(setter) 제공해야함
  int x, y;
public:
  // 생성자 - 객체 생성될 경우, 단 한 번만 자동으로 호출됨
  Test2();

  // setter: void set 멤버변수(멤버와 동일한 타임){}
  void setNum(int n) {
    num = n;
  }
  // getter
  int getNum() {
    return num;
  }
};