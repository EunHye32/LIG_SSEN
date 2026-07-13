#include "Test.h"
void Test::print() {
  cout << "name:" << name << endl;
  cout << "age:" << age << endl;
}
void Test::print(string msg) {
  cout << "name:" << name << endl;
  cout << "age:" << age << endl;
  cout << "msg:" << msg << endl;
}
int add(int a, int b) {
  return a + b;
}
double add(double a, double b) {
  return a + b;
}