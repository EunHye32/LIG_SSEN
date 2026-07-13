#include <iostream>
#include <string>
using namespace std;
class Student
{
private:
  int number;
  char* name;
  int score_k;
  int score_e;
  int score_m;
  int total;
public:
  Student() :number(0), name(nullptr), score_k(0), score_e(0), score_m(0), total(0) {}
  Student(int num, const char* n, int k, int e, int m) :number(num), score_k(k), score_e(e), score_m(m) {
    if (n != NULL) {
      int len = strlen(n) + 1;
      name = new char[len];
      strcpy(name, n);
    }
    total = score_k + score_e + score_m;
  }
  Student(const Student& s) :number(s.number), score_k(s.score_k), score_e(s.score_e), score_m(s.score_m), total(s.total) {
    if (name != nullptr) delete[] name;
    int len = strlen(s.name) + 1;
    strcpy(name, s.name);
  }
  ~Student() {
    delete[] name;
  }
  void setData(int num, const char* n, int k, int e, int m) {
    number = num;
    score_k = k; score_e = e; score_m = m;
    total = k + e + m;

    delete[] name;
    name = new char[strlen(n) + 1];
    strcpy(name, n);
  }
  void print() {
    cout << "number: " << number << ", name: " << name << ", score_k: "
      << score_k << ", score_e: " << score_e << ", score_m: " << score_m << ", total: " << total << endl;
  }
};

